library ieee;
use ieee.std_logic_1164.all;

entity ControleLed is
    port(
        CLK : in std_logic;
        RST : in std_logic;
        Ligar : in std_logic;
        Desligar : in std_logic;
        LED : out std_logic
    );
end entity ControleLed;

architecture behavior_ControleLed of ControleLed is
    type estados is (LIGADO, DESLIGADO);
    signal atual, prox : estados := DESLIGADO;
begin
    process(CLK, RST)
    begin
        if RST = '1' then
            atual <= DESLIGADO;
        elsif rising_edge(CLK) then
            atual <= prox;
        end if;
    end process;

    process(atual, Ligar, Desligar)
    begin
        case atual is
            when DESLIGADO =>
                if Ligar = '1' then
                    prox <= LIGADO;
                else
                    prox <= DESLIGADO;
                end if;

            when LIGADO =>
                if Desligar = '1' then
                    prox <= DESLIGADO;
                else
                    prox <= LIGADO;
                end if;
            when others =>
                    prox <= DESLIGADO;
        end case;
    end process;

    LED <= '1' when atual = LIGADO else '0';

end behavior_ControleLed;