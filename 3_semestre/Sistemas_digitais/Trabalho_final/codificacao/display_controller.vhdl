library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity Display_Controller is
    Port (
        sum_display : in STD_LOGIC_VECTOR(7 downto 0);
        -- Saídas para o primeiro display (unidades)
        a1, b1, c1, d1, e1, f1, g1, p1 : out STD_LOGIC;
        -- Saídas para o segundo display (dezenas)
        a2, b2, c2, d2, e2, f2, g2, p2 : out STD_LOGIC
    );
end Display_Controller;

architecture Behavioral of Display_Controller is
    -- Sinais intermediários para armazenar valores decimais
    signal binary_value : integer range 0 to 255;
    signal tens, ones : integer range 0 to 9;
    signal tens_bcd, ones_bcd : STD_LOGIC_VECTOR(3 downto 0);

begin
    -- Converte o valor binário para inteiro
    binary_value <= to_integer(unsigned(sum_display));
    
    -- Calcula dezenas e unidades
    tens <= binary_value / 10;
    ones <= binary_value mod 10;
    
    -- Converte os valores para BCD
    tens_bcd <= std_logic_vector(to_unsigned(tens, 4));
    ones_bcd <= std_logic_vector(to_unsigned(ones, 4));
    
    -- Processo para decodificar o dígito das unidades
    process(ones_bcd)
    begin
        case ones_bcd is
            when "0000" => -- 0
                a1 <= '1'; b1 <= '1'; c1 <= '1'; d1 <= '1'; e1 <= '1'; f1 <= '1'; g1 <= '0';
            when "0001" => -- 1
                a1 <= '0'; b1 <= '1'; c1 <= '1'; d1 <= '0'; e1 <= '0'; f1 <= '0'; g1 <= '0';
            when "0010" => -- 2
                a1 <= '1'; b1 <= '1'; c1 <= '0'; d1 <= '1'; e1 <= '1'; f1 <= '0'; g1 <= '1';
            when "0011" => -- 3
                a1 <= '1'; b1 <= '1'; c1 <= '1'; d1 <= '1'; e1 <= '0'; f1 <= '0'; g1 <= '1';
            when "0100" => -- 4
                a1 <= '0'; b1 <= '1'; c1 <= '1'; d1 <= '0'; e1 <= '0'; f1 <= '1'; g1 <= '1';
            when "0101" => -- 5
                a1 <= '1'; b1 <= '0'; c1 <= '1'; d1 <= '1'; e1 <= '0'; f1 <= '1'; g1 <= '1';
            when "0110" => -- 6
                a1 <= '1'; b1 <= '0'; c1 <= '1'; d1 <= '1'; e1 <= '1'; f1 <= '1'; g1 <= '1';
            when "0111" => -- 7
                a1 <= '1'; b1 <= '1'; c1 <= '1'; d1 <= '0'; e1 <= '0'; f1 <= '0'; g1 <= '0';
            when "1000" => -- 8
                a1 <= '1'; b1 <= '1'; c1 <= '1'; d1 <= '1'; e1 <= '1'; f1 <= '1'; g1 <= '1';
            when "1001" => -- 9
                a1 <= '1'; b1 <= '1'; c1 <= '1'; d1 <= '1'; e1 <= '0'; f1 <= '1'; g1 <= '1';
            when others => -- Desativa todos os segmentos
                a1 <= '0'; b1 <= '0'; c1 <= '0'; d1 <= '0'; e1 <= '0'; f1 <= '0'; g1 <= '0';
        end case;
    end process;
    
    -- Processo para decodificar o dígito das dezenas
    process(tens_bcd)
    begin
        case tens_bcd is
            when "0000" => -- 0
                a2 <= '1'; b2 <= '1'; c2 <= '1'; d2 <= '1'; e2 <= '1'; f2 <= '1'; g2 <= '0';
            when "0001" => -- 1
                a2 <= '0'; b2 <= '1'; c2 <= '1'; d2 <= '0'; e2 <= '0'; f2 <= '0'; g2 <= '0';
            when "0010" => -- 2
                a2 <= '1'; b2 <= '1'; c2 <= '0'; d2 <= '1'; e2 <= '1'; f2 <= '0'; g2 <= '1';
            when "0011" => -- 3
                a2 <= '1'; b2 <= '1'; c2 <= '1'; d2 <= '1'; e2 <= '0'; f2 <= '0'; g2 <= '1';
            when "0100" => -- 4
                a2 <= '0'; b2 <= '1'; c2 <= '1'; d2 <= '0'; e2 <= '0'; f2 <= '1'; g2 <= '1';
            when "0101" => -- 5
                a2 <= '1'; b2 <= '0'; c2 <= '1'; d2 <= '1'; e2 <= '0'; f2 <= '1'; g2 <= '1';
            when "0110" => -- 6
                a2 <= '1'; b2 <= '0'; c2 <= '1'; d2 <= '1'; e2 <= '1'; f2 <= '1'; g2 <= '1';
            when "0111" => -- 7
                a2 <= '1'; b2 <= '1'; c2 <= '1'; d2 <= '0'; e2 <= '0'; f2 <= '0'; g2 <= '0';
            when "1000" => -- 8
                a2 <= '1'; b2 <= '1'; c2 <= '1'; d2 <= '1'; e2 <= '1'; f2 <= '1'; g2 <= '1';
            when "1001" => -- 9
                a2 <= '1'; b2 <= '1'; c2 <= '1'; d2 <= '1'; e2 <= '0'; f2 <= '1'; g2 <= '1';
            when others => -- Desativa todos os segmentos
                a2 <= '0'; b2 <= '0'; c2 <= '0'; d2 <= '0'; e2 <= '0'; f2 <= '0'; g2 <= '0';
        end case;
    end process;
    
end Behavioral;