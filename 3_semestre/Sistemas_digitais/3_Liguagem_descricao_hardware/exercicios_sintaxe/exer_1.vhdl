library ieee;
use ieee.STD_LOGIC_1164.all;

entity port_or is
	port (
		A: in STD_LOGIC;
		B: in STD_LOGIC;
		C: in STD_LOGIC;
		D: in STD_LOGIC;
		S: out STD_LOGIC
	);
end port_or;

architecture behavior of port_or is
begin

	S <= A or B or C or D;
	
end behavior;
