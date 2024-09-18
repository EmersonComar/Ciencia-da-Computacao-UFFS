library ieee;
use ieee.STD_LOGIC_1164.all;

entity fluxo is
	port (
		A: in STD_LOGIC;
		B: in STD_LOGIC;
		S: out STD_LOGIC
	);
end fluxo;

architecture comport_fluxo of fluxo is
begin
	s <= '1' when B < A
		else '0';
end comport_fluxo;
