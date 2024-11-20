library ieee;
use ieee.std_logic_1164.all;

entity Semaforo is
    port(
        CLK : in std_logic;
        RST : in std_logic;
        LedVermelho : out std_logic;
        LedAmarelo : out std_logic;
        LedVerde : out std_logic
    );
end entity Semaforo;

architecture behavior_semaforo of Semaforo is
    type estados is (VERMELHO, VERDE, AMARELO);
    signal atual, proximo : estados := VERMELHO;
    signal contador : INTEGER range 0 to 15 := 0;
begin
    process(CLK, RST)
    begin
        if RST = '1' then
            atual <= VERMELHO;
            contador <= 0;
        elsif rising_edge(CLK) then
            atual <= proximo;
            if contador < 15 then
                contador <= contador + 1;
            else
                contador <= 0;
            end if;
        end if;
    end process;

    process(atual, contador)
    begin
        case atual is
            when VERMELHO =>
                LedVermelho <= '1';
                LedAmarelo <= '0';
                LedVerde <= '0';
                if contador = 10 then
                    proximo <= VERDE;
                else
                    proximo <= VERMELHO;
                end if;
            
            when VERDE =>
                    LedVermelho <= '0';
                    LedAmarelo <= '0';
                    LedVerde <= '1';
                    if contador = 15 then
                        proximo <= AMARELO;
                    else
                        proximo <= VERDE;
                    end if;

                    
            when AMARELO =>
                    LedVermelho <= '0';
                    LedAmarelo <= '1'; 
                    LedVerde <= '0';
                    if contador = 5 then
                        proximo <= VERMELHO;
                    else
                        proximo <= AMARELO;
                    end if;
            

            when others =>
                    proximo <= VERMELHO;
        end case;
    end process;

end behavior_semaforo;