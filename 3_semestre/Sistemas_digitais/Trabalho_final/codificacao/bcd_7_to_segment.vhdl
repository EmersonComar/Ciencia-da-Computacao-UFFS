library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Entidade do decodificador
entity BCD_to_7Segment is
    Port (
        BCD : in STD_LOGIC_VECTOR(3 downto 0); -- Entrada BCD de 4 bits
        a, b, c, d, e, f, g, p : out STD_LOGIC -- Saídas individuais para cada segmento
    );
end BCD_to_7Segment;

-- Arquitetura do decodificador
architecture Behavioral of BCD_to_7Segment is
begin
    -- Decodificação dos segmentos com base na entrada BCD
    process(BCD)
    begin
        case BCD is
            when "0000" => -- 0
                a <= '1'; b <= '1'; c <= '1'; d <= '1'; e <= '1'; f <= '1'; g <= '0';
            when "0001" => -- 1
                a <= '0'; b <= '1'; c <= '1'; d <= '0'; e <= '0'; f <= '0'; g <= '0';
            when "0010" => -- 2
                a <= '1'; b <= '1'; c <= '0'; d <= '1'; e <= '1'; f <= '0'; g <= '1';
            when "0011" => -- 3
                a <= '1'; b <= '1'; c <= '1'; d <= '1'; e <= '0'; f <= '0'; g <= '1';
            when "0100" => -- 4
                a <= '0'; b <= '1'; c <= '1'; d <= '0'; e <= '0'; f <= '1'; g <= '1';
            when "0101" => -- 5
                a <= '1'; b <= '0'; c <= '1'; d <= '1'; e <= '0'; f <= '1'; g <= '1';
            when "0110" => -- 6
                a <= '1'; b <= '0'; c <= '1'; d <= '1'; e <= '1'; f <= '1'; g <= '1';
            when "0111" => -- 7
                a <= '1'; b <= '1'; c <= '1'; d <= '0'; e <= '0'; f <= '0'; g <= '0';
            when "1000" => -- 8
                a <= '1'; b <= '1'; c <= '1'; d <= '1'; e <= '1'; f <= '1'; g <= '1';
            when "1001" => -- 9
                a <= '1'; b <= '1'; c <= '1'; d <= '1'; e <= '0'; f <= '1'; g <= '1';
            when "1010" => -- 10 (A)
                a <= '1'; b <= '1'; c <= '1'; d <= '0'; e <= '1'; f <= '1'; g <= '1';
            when "1011" => -- 11 (b)
                a <= '0'; b <= '0'; c <= '1'; d <= '1'; e <= '1'; f <= '1'; g <= '1';
            when "1100" => -- 12 (C)
                a <= '1'; b <= '0'; c <= '0'; d <= '1'; e <= '1'; f <= '1'; g <= '0';
            when "1101" => -- 13 (d)
                a <= '0'; b <= '1'; c <= '1'; d <= '1'; e <= '1'; f <= '0'; g <= '1';
            when others => -- Desativa todos os segmentos
                a <= '0'; b <= '0'; c <= '0'; d <= '0'; e <= '0'; f <= '0'; g <= '0';
        end case;
    end process;
end Behavioral;
