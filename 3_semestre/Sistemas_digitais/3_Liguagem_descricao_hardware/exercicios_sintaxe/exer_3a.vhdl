library ieee;
use ieee.STD_LOGIC_1164.all;

entity ext3a is
	port (
		-- Entradas
		A: in STD_LOGIC;
		B: in STD_LOGIC;
		C: in STD_LOGIC;
		
		-- Saídas
		D: out STD_LOGIC;
		E: out STD_LOGIC;
		F: out STD_LOGIC
	);
end ext3a;

architecture behavioral of ext3a is
signal nor_AnB, nand_nBnC, and_nBnC:  STD_LOGIC;
begin
	
	nor_AnB <= A nor not B;
	nand_nBnC <= not B nand not C;
	and_nBnC <= not B and not C;
	
	D <= nor_Anb xor not nand_nBnC;
	E <= nand_nBnC and not B;
	F <= nand_nBnC xor and_nBnC;

end behavioral;
