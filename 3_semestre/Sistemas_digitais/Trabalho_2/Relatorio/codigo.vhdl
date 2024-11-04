library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;


entity PortaGaragem is
    Port (
        clk : in std_logic;        -- clock
        reset : in std_logic;      -- reset
        B : in std_logic;          -- controle remoto
        S : in std_logic;          -- sensor de segurança
        SA : out std_logic;        -- indicador de porta aberta
        SF : out std_logic;        -- indicador de porta fechada
        A : out std_logic;         -- sinal abrir porta
        F : out std_logic          -- sinal fechar porta
    );
end PortaGaragem;

architecture behavior_PortaGaragem of PortaGaragem is
    type Tipo_estado is (ABERTO, FECHADO, FECHANDO1, FECHANDO2, FECHANDO3, ABRINDO1, ABRINDO2, ABRINDO3);
    signal atual, prox : Tipo_estado := FECHADO; -- inicializa um estado
begin
    -- Processo síncrono para controlar as mudanças de estado na borda de subida do clock
    process (clk, reset)
    begin
        if reset = '1' then
            atual <= FECHADO; -- Resetar para estado inicial
        elsif rising_edge(clk) then
            atual <= prox; -- Atualiza o estado na borda de subida do clock
        end if;
    end process;

    -- Processo combinacional para definir as transições de estado
    process (atual, B, S)
    begin
        -- Atualiza as saídas SA e SF conforme o estado da porta
        SA <= '0';
        SF <= '0';

        case atual is
            when FECHADO =>
                A <= '0';
                F <= '0';
                SF <= '1'; -- Porta está fechada
                SA <= '0';
                if B = '1' then
                    prox <= ABRINDO1;
                end if;
            when FECHANDO1 =>
                A <= '0';
                F <= '1';
                SF <= '0'; -- Porta está fechada
                SA <= '0';
                if S = '1' then
                    prox <= ABRINDO3;
                else
                    prox <= FECHANDO2;
                end if;
            when FECHANDO2 =>
                A <= '0';
                F <= '1';
                SF <= '0'; -- Porta está fechada
                SA <= '0';
                if S = '1' then
                    prox <= ABRINDO2;
                else
                    prox <= FECHANDO3;
                end if;
            when FECHANDO3 =>
                A <= '0';
                F <= '1';
                SF <= '0'; -- Porta está fechada
                SA <= '0';
                if S = '1' then
                    prox <= ABRINDO1;
                else
                    prox <= FECHADO;
                end if;
            when ABRINDO1 =>
                A <= '1';
                F <= '0';
                SF <= '0'; -- Porta está fechada
                SA <= '0';
                if S = '1' then
                    prox <= FECHANDO3;
                else
                    prox <= ABRINDO2;
                end if;
            when ABRINDO2 =>
                A <= '1';
                F <= '0';
                SF <= '0'; -- Porta está fechada
                SA <= '0';
                if S = '1' then
                    prox <= FECHANDO2;
                else
                    prox <= ABRINDO3;
                end if;
            when ABRINDO3 =>
                A <= '1';
                F <= '0';
                SF <= '0'; -- Porta está fechada
                SA <= '0';
                if S = '1' then
                    prox <= FECHANDO3;
                else
                    prox <= ABERTO;
                end if;
            when ABERTO =>
                A <= '0';
                F <= '0';
                SA <= '1'; -- Porta está aberta
                SF <= '0';
                if B = '1' then
                    prox <= FECHANDO1;
                end if;
        end case;
    end process;
end behavior_PortaGaragem;
