library ieee;
use ieee.std_logic_1164.all;

entity algoritmica is
	port(
		A: in STD_LOGIC;
		B: in STD_LOGIC;
		S: out STD_LOGIC
	);
end algoritmica;

architecture comport_algor of algoritmica is
begin
	process(A,B)
	begin
		if(B < A) then
			S <= '1';
		else
			s <= '0';
		end if;
	end process;
end comport_algor;
