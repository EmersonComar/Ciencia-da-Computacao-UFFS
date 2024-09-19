library ieee;
use ieee.STD_LOGIC_1164.all;

entity full_adder is
	port (
		A_F: in STD_LOGIC;
		B_F: in STD_LOGIC;
		CARRY_IN: in STD_LOGIC;
		CARRY_OUT: out STD_LOGIC;
		SUM: out STD_LOGIC
	);
end entity full_adder;

architecture behavior_full of full_adder is
	component half_adder is
		port (
			A: in STD_LOGIC;
			B: in STD_LOGIC;
			SUM: out STD_LOGIC;
			CARRY: out STD_LOGIC
		);
	end component;

signal carry_1, carry_2, sum_int: STD_LOGIC;

begin
	
	half1: half_adder
		port map(
			A => A_F,
			B => B_F,
			CARRY => carry_1,
			SUM => sum_int
		);
	half2: half_adder
		port map(
			A => sum_int,
			B => CARRY_IN,
			CARRY => carry_2,
			SUM => SUM
		);
	
	CARRY_OUT <= carry_1 or carry_2;
	
end behavior_full;

library ieee;
use ieee.std_logic_1164.all;

--------------------------
-- Entity half_adder
--------------------------
entity half_adder is
	port (
		A: in STD_LOGIC;
		B: in STD_LOGIC;
		SUM: out STD_LOGIC;
		CARRY: out STD_LOGIC
	);
end entity half_adder;

--------------------------
-- Abstração de fluxo
--------------------------
architecture behavior_fluxo of half_adder is
begin

	SUM <= A xor B;
	CARRY <= A and B;

end behavior_fluxo;

--------------------------
-- Abstração algorítmica
--------------------------
--architecture behavior_algoritmica of half_adder is
--begin
--	process(A, B)
--	begin
--		if(A = '1' and B = '1') then
--			SUM <= '0';
--			CARRY <= '1';
--		elsif ( A > B or B > A ) then
--			SUM <= '1';
--			CARRY <= '0';
--		else
--			SUM <= '0';
--			CARRY <= '0';
--		end if;
--	end process;

--end behavior_algoritmica;
