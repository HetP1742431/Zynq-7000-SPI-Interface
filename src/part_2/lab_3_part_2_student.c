#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "xparameters.h"
#include "xil_printf.h"
#include "xuartps.h"
#include "PmodOLED.h"
#include "OLEDControllerCustom.h"
#include "xgpio.h"

#define SQUARE_WIDTH 10
#define SQUARE_Y (OledRowMax - 10)
#define SQUARE_SPEED 5
#define FALLING_OBJ_SIZE 5  // Size of the falling object (formerly circle)
#define BTN0 XPAR_GPIO_0_DEVICE_ID  // Adjust to your hardware for BTN0
#define BTN3 XPAR_GPIO_1_DEVICE_ID  // Adjust to your hardware for BTN3

typedef struct {
    int x, y;
    int active;  // 1 if the falling object is currently active, 0 otherwise
} FallingObject;

PmodOLED oledDevice;
XGpio btn0Gpio, btn3Gpio;
int squareX;
FallingObject fallingObj;
int score;
int gameStarted;

void initializeSystem() {
    OLED_Begin(&oledDevice, XPAR_PMODOLED_0_AXI_LITE_GPIO_BASEADDR, XPAR_PMODOLED_0_AXI_LITE_SPI_BASEADDR, 0, 0);
    OLED_ClearBuffer(&oledDevice);

    XGpio_Initialize(&btn0Gpio, BTN0);
    XGpio_SetDataDirection(&btn0Gpio, 1, 0xFFFFFFFF);
    XGpio_Initialize(&btn3Gpio, BTN3);
    XGpio_SetDataDirection(&btn3Gpio, 1, 0xFFFFFFFF);

    resetGame();

    xil_printf("Simple Catch Game\n");
    xil_printf("Use BTN0 to move the square left and BTN3 to move it right.\n");
    xil_printf("Press any key on the keyboard to start the game.\n");
}

void resetGame() {
    squareX = OledColMax / 2 - SQUARE_WIDTH / 2;
    fallingObj.x = rand() % (OledColMax - FALLING_OBJ_SIZE);
    fallingObj.y = 0;
    fallingObj.active = 1;
    score = 0;
    gameStarted = 0;
}

void gameTask(void *pvParameters) {
    initializeSystem();

    while (1) {
        handleInput();
        if (gameStarted) {
            updateGame();
        }
        drawGame();
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void handleInput() {
    int btn0State = XGpio_DiscreteRead(&btn0Gpio, 1);
    int btn3State = XGpio_DiscreteRead(&btn3Gpio, 1);

    if (!btn0State) {
        squareX -= SQUARE_SPEED;
    }
    if (!btn3State) {
        squareX += SQUARE_SPEED;
    }

    // Keep the square within the screen bounds
    if (squareX < 0) squareX = 0;
    if (squareX > OledColMax - SQUARE_WIDTH) squareX = OledColMax - SQUARE_WIDTH;

    // Check for keyboard input to start the game
    if (!gameStarted && XUartPs_IsReceiveData(XPAR_XUARTPS_0_BASEADDR)) {
        gameStarted = 1;
    }
}

void updateGame() {
    if (!fallingObj.active) {
        fallingObj.x = rand() % (OledColMax - FALLING_OBJ_SIZE);
        fallingObj.y = 0;
        fallingObj.active = 1;
    }

    fallingObj.y += 2;  // Falling object moves down

    // Check for collision with the square
    if (fallingObj.y + FALLING_OBJ_SIZE >= SQUARE_Y && fallingObj.x + FALLING_OBJ_SIZE >= squareX && fallingObj.x <= squareX + SQUARE_WIDTH) {
        score++;
        fallingObj.active = 0;  // Reset the falling object
    } else if (fallingObj.y >= OledRowMax) {
        fallingObj.active = 0;  // Reset the falling object if missed
    }
}

void drawGame() {
    OLED_ClearBuffer(&oledDevice);
    // Draw square
    OLED_MoveTo(&oledDevice, squareX, SQUARE_Y);
    OLED_DrawRect(&oledDevice, squareX + SQUARE_WIDTH, SQUARE_Y + SQUARE_WIDTH);

    // Draw falling object if active
    if (fallingObj.active) {
        OLED_MoveTo(&oledDevice, fallingObj.x, fallingObj.y);
        OLED_DrawRect(&oledDevice, fallingObj.x + FALLING_OBJ_SIZE, fallingObj.y + FALLING_OBJ_SIZE);
    }

    OLED_Update(&oledDevice);
    xil_printf("\rScore: %d", score);  // Display the score in the terminal
}

int main(void) {
    xTaskCreate(gameTask, "Game Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();
    while (1);
    return 0;
}
