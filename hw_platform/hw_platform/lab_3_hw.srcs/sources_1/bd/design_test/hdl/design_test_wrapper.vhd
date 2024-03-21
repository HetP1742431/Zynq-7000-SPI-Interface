--Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2019.1 (win64) Build 2552052 Fri May 24 14:49:42 MDT 2019
--Date        : Mon Feb 26 11:33:10 2024
--Host        : TECH-C98I8JRGUQ running 64-bit major release  (build 9200)
--Command     : generate_target design_test_wrapper.bd
--Design      : design_test_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity design_test_wrapper is
  port (
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_cas_n : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    btns_4bits_tri_i : in STD_LOGIC_VECTOR ( 3 downto 0 );
    jc_pin10_io : inout STD_LOGIC;
    jc_pin1_io : inout STD_LOGIC;
    jc_pin2_io : inout STD_LOGIC;
    jc_pin3_io : inout STD_LOGIC;
    jc_pin4_io : inout STD_LOGIC;
    jc_pin7_io : inout STD_LOGIC;
    jc_pin8_io : inout STD_LOGIC;
    jc_pin9_io : inout STD_LOGIC;
    keypad_tri_io : inout STD_LOGIC_VECTOR ( 7 downto 0 );
    sws_4bits_tri_i : in STD_LOGIC_VECTOR ( 3 downto 0 )
  );
end design_test_wrapper;

architecture STRUCTURE of design_test_wrapper is
  component design_test is
  port (
    DDR_cas_n : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    keypad_tri_i : in STD_LOGIC_VECTOR ( 7 downto 0 );
    keypad_tri_o : out STD_LOGIC_VECTOR ( 7 downto 0 );
    keypad_tri_t : out STD_LOGIC_VECTOR ( 7 downto 0 );
    jc_pin1_o : out STD_LOGIC;
    jc_pin7_i : in STD_LOGIC;
    jc_pin2_o : out STD_LOGIC;
    jc_pin8_i : in STD_LOGIC;
    jc_pin3_o : out STD_LOGIC;
    jc_pin9_i : in STD_LOGIC;
    jc_pin10_o : out STD_LOGIC;
    jc_pin4_o : out STD_LOGIC;
    jc_pin3_i : in STD_LOGIC;
    jc_pin4_i : in STD_LOGIC;
    jc_pin1_i : in STD_LOGIC;
    jc_pin2_i : in STD_LOGIC;
    jc_pin10_t : out STD_LOGIC;
    jc_pin8_t : out STD_LOGIC;
    jc_pin9_t : out STD_LOGIC;
    jc_pin4_t : out STD_LOGIC;
    jc_pin9_o : out STD_LOGIC;
    jc_pin10_i : in STD_LOGIC;
    jc_pin7_t : out STD_LOGIC;
    jc_pin1_t : out STD_LOGIC;
    jc_pin2_t : out STD_LOGIC;
    jc_pin7_o : out STD_LOGIC;
    jc_pin3_t : out STD_LOGIC;
    jc_pin8_o : out STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    btns_4bits_tri_i : in STD_LOGIC_VECTOR ( 3 downto 0 );
    sws_4bits_tri_i : in STD_LOGIC_VECTOR ( 3 downto 0 )
  );
  end component design_test;
  component IOBUF is
  port (
    I : in STD_LOGIC;
    O : out STD_LOGIC;
    T : in STD_LOGIC;
    IO : inout STD_LOGIC
  );
  end component IOBUF;
  signal jc_pin10_i : STD_LOGIC;
  signal jc_pin10_o : STD_LOGIC;
  signal jc_pin10_t : STD_LOGIC;
  signal jc_pin1_i : STD_LOGIC;
  signal jc_pin1_o : STD_LOGIC;
  signal jc_pin1_t : STD_LOGIC;
  signal jc_pin2_i : STD_LOGIC;
  signal jc_pin2_o : STD_LOGIC;
  signal jc_pin2_t : STD_LOGIC;
  signal jc_pin3_i : STD_LOGIC;
  signal jc_pin3_o : STD_LOGIC;
  signal jc_pin3_t : STD_LOGIC;
  signal jc_pin4_i : STD_LOGIC;
  signal jc_pin4_o : STD_LOGIC;
  signal jc_pin4_t : STD_LOGIC;
  signal jc_pin7_i : STD_LOGIC;
  signal jc_pin7_o : STD_LOGIC;
  signal jc_pin7_t : STD_LOGIC;
  signal jc_pin8_i : STD_LOGIC;
  signal jc_pin8_o : STD_LOGIC;
  signal jc_pin8_t : STD_LOGIC;
  signal jc_pin9_i : STD_LOGIC;
  signal jc_pin9_o : STD_LOGIC;
  signal jc_pin9_t : STD_LOGIC;
  signal keypad_tri_i_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal keypad_tri_i_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal keypad_tri_i_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal keypad_tri_i_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal keypad_tri_i_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal keypad_tri_i_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal keypad_tri_i_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal keypad_tri_i_7 : STD_LOGIC_VECTOR ( 7 to 7 );
  signal keypad_tri_io_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal keypad_tri_io_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal keypad_tri_io_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal keypad_tri_io_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal keypad_tri_io_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal keypad_tri_io_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal keypad_tri_io_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal keypad_tri_io_7 : STD_LOGIC_VECTOR ( 7 to 7 );
  signal keypad_tri_o_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal keypad_tri_o_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal keypad_tri_o_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal keypad_tri_o_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal keypad_tri_o_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal keypad_tri_o_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal keypad_tri_o_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal keypad_tri_o_7 : STD_LOGIC_VECTOR ( 7 to 7 );
  signal keypad_tri_t_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal keypad_tri_t_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal keypad_tri_t_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal keypad_tri_t_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal keypad_tri_t_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal keypad_tri_t_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal keypad_tri_t_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal keypad_tri_t_7 : STD_LOGIC_VECTOR ( 7 to 7 );
begin
design_test_i: component design_test
     port map (
      DDR_addr(14 downto 0) => DDR_addr(14 downto 0),
      DDR_ba(2 downto 0) => DDR_ba(2 downto 0),
      DDR_cas_n => DDR_cas_n,
      DDR_ck_n => DDR_ck_n,
      DDR_ck_p => DDR_ck_p,
      DDR_cke => DDR_cke,
      DDR_cs_n => DDR_cs_n,
      DDR_dm(3 downto 0) => DDR_dm(3 downto 0),
      DDR_dq(31 downto 0) => DDR_dq(31 downto 0),
      DDR_dqs_n(3 downto 0) => DDR_dqs_n(3 downto 0),
      DDR_dqs_p(3 downto 0) => DDR_dqs_p(3 downto 0),
      DDR_odt => DDR_odt,
      DDR_ras_n => DDR_ras_n,
      DDR_reset_n => DDR_reset_n,
      DDR_we_n => DDR_we_n,
      FIXED_IO_ddr_vrn => FIXED_IO_ddr_vrn,
      FIXED_IO_ddr_vrp => FIXED_IO_ddr_vrp,
      FIXED_IO_mio(53 downto 0) => FIXED_IO_mio(53 downto 0),
      FIXED_IO_ps_clk => FIXED_IO_ps_clk,
      FIXED_IO_ps_porb => FIXED_IO_ps_porb,
      FIXED_IO_ps_srstb => FIXED_IO_ps_srstb,
      btns_4bits_tri_i(3 downto 0) => btns_4bits_tri_i(3 downto 0),
      jc_pin10_i => jc_pin10_i,
      jc_pin10_o => jc_pin10_o,
      jc_pin10_t => jc_pin10_t,
      jc_pin1_i => jc_pin1_i,
      jc_pin1_o => jc_pin1_o,
      jc_pin1_t => jc_pin1_t,
      jc_pin2_i => jc_pin2_i,
      jc_pin2_o => jc_pin2_o,
      jc_pin2_t => jc_pin2_t,
      jc_pin3_i => jc_pin3_i,
      jc_pin3_o => jc_pin3_o,
      jc_pin3_t => jc_pin3_t,
      jc_pin4_i => jc_pin4_i,
      jc_pin4_o => jc_pin4_o,
      jc_pin4_t => jc_pin4_t,
      jc_pin7_i => jc_pin7_i,
      jc_pin7_o => jc_pin7_o,
      jc_pin7_t => jc_pin7_t,
      jc_pin8_i => jc_pin8_i,
      jc_pin8_o => jc_pin8_o,
      jc_pin8_t => jc_pin8_t,
      jc_pin9_i => jc_pin9_i,
      jc_pin9_o => jc_pin9_o,
      jc_pin9_t => jc_pin9_t,
      keypad_tri_i(7) => keypad_tri_i_7(7),
      keypad_tri_i(6) => keypad_tri_i_6(6),
      keypad_tri_i(5) => keypad_tri_i_5(5),
      keypad_tri_i(4) => keypad_tri_i_4(4),
      keypad_tri_i(3) => keypad_tri_i_3(3),
      keypad_tri_i(2) => keypad_tri_i_2(2),
      keypad_tri_i(1) => keypad_tri_i_1(1),
      keypad_tri_i(0) => keypad_tri_i_0(0),
      keypad_tri_o(7) => keypad_tri_o_7(7),
      keypad_tri_o(6) => keypad_tri_o_6(6),
      keypad_tri_o(5) => keypad_tri_o_5(5),
      keypad_tri_o(4) => keypad_tri_o_4(4),
      keypad_tri_o(3) => keypad_tri_o_3(3),
      keypad_tri_o(2) => keypad_tri_o_2(2),
      keypad_tri_o(1) => keypad_tri_o_1(1),
      keypad_tri_o(0) => keypad_tri_o_0(0),
      keypad_tri_t(7) => keypad_tri_t_7(7),
      keypad_tri_t(6) => keypad_tri_t_6(6),
      keypad_tri_t(5) => keypad_tri_t_5(5),
      keypad_tri_t(4) => keypad_tri_t_4(4),
      keypad_tri_t(3) => keypad_tri_t_3(3),
      keypad_tri_t(2) => keypad_tri_t_2(2),
      keypad_tri_t(1) => keypad_tri_t_1(1),
      keypad_tri_t(0) => keypad_tri_t_0(0),
      sws_4bits_tri_i(3 downto 0) => sws_4bits_tri_i(3 downto 0)
    );
jc_pin10_iobuf: component IOBUF
     port map (
      I => jc_pin10_o,
      IO => jc_pin10_io,
      O => jc_pin10_i,
      T => jc_pin10_t
    );
jc_pin1_iobuf: component IOBUF
     port map (
      I => jc_pin1_o,
      IO => jc_pin1_io,
      O => jc_pin1_i,
      T => jc_pin1_t
    );
jc_pin2_iobuf: component IOBUF
     port map (
      I => jc_pin2_o,
      IO => jc_pin2_io,
      O => jc_pin2_i,
      T => jc_pin2_t
    );
jc_pin3_iobuf: component IOBUF
     port map (
      I => jc_pin3_o,
      IO => jc_pin3_io,
      O => jc_pin3_i,
      T => jc_pin3_t
    );
jc_pin4_iobuf: component IOBUF
     port map (
      I => jc_pin4_o,
      IO => jc_pin4_io,
      O => jc_pin4_i,
      T => jc_pin4_t
    );
jc_pin7_iobuf: component IOBUF
     port map (
      I => jc_pin7_o,
      IO => jc_pin7_io,
      O => jc_pin7_i,
      T => jc_pin7_t
    );
jc_pin8_iobuf: component IOBUF
     port map (
      I => jc_pin8_o,
      IO => jc_pin8_io,
      O => jc_pin8_i,
      T => jc_pin8_t
    );
jc_pin9_iobuf: component IOBUF
     port map (
      I => jc_pin9_o,
      IO => jc_pin9_io,
      O => jc_pin9_i,
      T => jc_pin9_t
    );
keypad_tri_iobuf_0: component IOBUF
     port map (
      I => keypad_tri_o_0(0),
      IO => keypad_tri_io(0),
      O => keypad_tri_i_0(0),
      T => keypad_tri_t_0(0)
    );
keypad_tri_iobuf_1: component IOBUF
     port map (
      I => keypad_tri_o_1(1),
      IO => keypad_tri_io(1),
      O => keypad_tri_i_1(1),
      T => keypad_tri_t_1(1)
    );
keypad_tri_iobuf_2: component IOBUF
     port map (
      I => keypad_tri_o_2(2),
      IO => keypad_tri_io(2),
      O => keypad_tri_i_2(2),
      T => keypad_tri_t_2(2)
    );
keypad_tri_iobuf_3: component IOBUF
     port map (
      I => keypad_tri_o_3(3),
      IO => keypad_tri_io(3),
      O => keypad_tri_i_3(3),
      T => keypad_tri_t_3(3)
    );
keypad_tri_iobuf_4: component IOBUF
     port map (
      I => keypad_tri_o_4(4),
      IO => keypad_tri_io(4),
      O => keypad_tri_i_4(4),
      T => keypad_tri_t_4(4)
    );
keypad_tri_iobuf_5: component IOBUF
     port map (
      I => keypad_tri_o_5(5),
      IO => keypad_tri_io(5),
      O => keypad_tri_i_5(5),
      T => keypad_tri_t_5(5)
    );
keypad_tri_iobuf_6: component IOBUF
     port map (
      I => keypad_tri_o_6(6),
      IO => keypad_tri_io(6),
      O => keypad_tri_i_6(6),
      T => keypad_tri_t_6(6)
    );
keypad_tri_iobuf_7: component IOBUF
     port map (
      I => keypad_tri_o_7(7),
      IO => keypad_tri_io(7),
      O => keypad_tri_i_7(7),
      T => keypad_tri_t_7(7)
    );
end STRUCTURE;
