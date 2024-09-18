library ieee;
use ieee.STD_LOGIC_1164.all;

entity array_or is
	port (
		E: in STD_LOGIC_VECTOR (3 DOWNTO 0);
		S: out STD_LOGIC
	);
end array_or;

architecture behavior of array_or is
begin

	S <= E(0) or E(1) or E(2) or E(3);

end behavior;
