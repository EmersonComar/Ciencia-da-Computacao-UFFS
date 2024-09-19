library ieee;
use ieee.std_logic_1164.all;

entity decoder_3to8 is
	port (
		A : in std_logic_vector (2 downto 0); -- Decoder Input
		Y : out std_logic_vector (7 downto 0) -- Decoder Output
	);
end entity decoder_3to8;

architecture behavior of decoder_3to8 is
begin
	process(A)
	begin
		case A is
			when "000" => Y <= "00000001";
			when "001" => Y <= "00000010";
			when "010" => Y <= "00000100";
			when "011" => Y <= "00001000";
			when "100" => Y <= "00010000";
			when "101" => Y <= "00100000";
			when "110" => Y <= "01000000";
			when "111" => Y <= "10000000";
			when others => NULL;
		end case;
	end process;
end behavior;
