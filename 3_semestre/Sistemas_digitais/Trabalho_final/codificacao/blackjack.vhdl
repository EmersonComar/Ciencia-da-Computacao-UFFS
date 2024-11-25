library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity blackjack is
    Port ( 
        clk         : in  STD_LOGIC;
        rst         : in  STD_LOGIC;
        start       : in  STD_LOGIC;
        hit_btn     : in  STD_LOGIC;
        stay_btn    : in  STD_LOGIC;
        random_cards: in  STD_LOGIC;  
        cards       : in  STD_LOGIC_VECTOR(3 downto 0);
        
        win_out     : out STD_LOGIC;
        lose_out    : out STD_LOGIC;
        tie_out     : out STD_LOGIC;
        card_display: out STD_LOGIC_VECTOR(3 downto 0);
        sum_display : out STD_LOGIC_VECTOR(7 downto 0);

        -- debug do estado atual
        INICIO : out STD_LOGIC;
        CARTA_USER_1 : out STD_LOGIC;
        CARTA_USER_2 : out STD_LOGIC;
        ESPERAR_USER: out STD_LOGIC;
        HIT : out STD_LOGIC;
        STAY : out STD_LOGIC;
        CARTA_1_DEALER : out STD_LOGIC;
        CARTA_2_DEALER : out STD_LOGIC;
        NOVA_CARTA_DEALER : out STD_LOGIC;
        COMPARAR_CARTAS : out STD_LOGIC;
        USER_GANHOU : out STD_LOGIC;
        USER_PERDEU : out STD_LOGIC;
        TIE : out STD_LOGIC
    );
end blackjack;

architecture Behavioral of blackjack is
    type state_type is (
        STATE_INICIO,
        STATE_CARTA_USER_1, 
        STATE_CARTA_USER_2, 
        STATE_ESPERAR_USER,
        STATE_HIT,
        STATE_STAY,
        STATE_CARTA_1_DEALER, 
        STATE_CARTA_2_DEALER,
        STATE_NOVA_CARTA_DEALER, 
        STATE_COMPARAR_CARTAS,
        STATE_USER_GANHOU, 
        STATE_USER_PERDEU, 
        STATE_TIE
    );
    
    signal current_state, next_state : state_type;
    signal soma_user    : unsigned(7 downto 0) := (others => '0');
    signal soma_dealer  : unsigned(7 downto 0) := (others => '0');
    signal carta_atual  : unsigned(3 downto 0);
    signal ases_user    : unsigned(3 downto 0) := (others => '0');
    signal ases_dealer  : unsigned(3 downto 0) := (others => '0');
    
    function get_card_value(card: unsigned; current_sum: unsigned; num_aces: unsigned) return unsigned is
        variable card_value: unsigned(7 downto 0);
    begin
        if card = 1 then
            if current_sum <= 10 then
                card_value := to_unsigned(11, 8);
            else
                card_value := to_unsigned(1, 8);
            end if;
        elsif card >= 10 and card <= 13 then
            card_value := to_unsigned(10, 8);
        elsif card > 13 then
            card_value := to_unsigned(0, 8);
        else
            card_value := resize(card, 8);
        end if;
        return card_value;
    end function;
    
    function adjust_aces(sum: unsigned; num_aces: unsigned) return unsigned is
        variable adjusted_sum: unsigned(7 downto 0);
    begin
        adjusted_sum := sum;
        for i in 0 to to_integer(num_aces)-1 loop
            if adjusted_sum > 21 then
                adjusted_sum := adjusted_sum - 10;
            end if;
        end loop;
        return adjusted_sum;
    end function;
    
begin
    -- Processo combinacional para atualizar displays
    process(current_state, carta_atual, soma_dealer, soma_user)
    begin
        -- Atualização imediata dos displays
        card_display <= std_logic_vector(carta_atual);
        if current_state = STATE_CARTA_1_DEALER or 
           current_state = STATE_CARTA_2_DEALER or 
           current_state = STATE_NOVA_CARTA_DEALER then
            sum_display <= std_logic_vector(soma_dealer);
        else
            sum_display <= std_logic_vector(soma_user);
        end if;
    end process;

    -- Processo de registrador de estado
    process(clk, rst)
    begin
        if rst = '1' then
            current_state <= STATE_INICIO;
            soma_user <= (others => '0');
            soma_dealer <= (others => '0');
            ases_user <= (others => '0');
            ases_dealer <= (others => '0');
        elsif rising_edge(clk) then
            current_state <= next_state;
            
            -- Atualização das somas e contagem de ases
            case current_state is
                when STATE_INICIO =>
                    soma_user <= (others => '0');
                    soma_dealer <= (others => '0');
                    ases_user <= (others => '0');
                    ases_dealer <= (others => '0');
                    
                when STATE_CARTA_USER_1 | STATE_CARTA_USER_2 | STATE_HIT =>
                    if carta_atual = 1 then
                        ases_user <= ases_user + 1;
                    end if;
                    soma_user <= adjust_aces(soma_user + get_card_value(carta_atual, soma_user, ases_user), ases_user);
                    
                when STATE_CARTA_1_DEALER | STATE_CARTA_2_DEALER | STATE_NOVA_CARTA_DEALER | STATE_COMPARAR_CARTAS =>
                    if carta_atual = 1 then
                        ases_dealer <= ases_dealer + 1;
                    end if;
                    soma_dealer <= adjust_aces(soma_dealer + get_card_value(carta_atual, soma_dealer, ases_dealer), ases_dealer);
                    
                when others =>
                    null;
            end case;
        end if;
    end process;
    
    process(current_state, start, hit_btn, stay_btn, random_cards, cards, soma_user, soma_dealer)
    begin
        -- Valores padrão
        next_state <= current_state;
        win_out <= '0';
        lose_out <= '0';
        tie_out <= '0';
        
        -- Atualização da carta atual baseada no estado
        if random_cards = '1' then
            case current_state is
                when STATE_CARTA_USER_1 => carta_atual <= "0001";
                when STATE_CARTA_USER_2 => carta_atual <= "0010";
                when STATE_HIT => carta_atual <= "0011";
                when STATE_CARTA_1_DEALER => carta_atual <= "0100";
                when STATE_CARTA_2_DEALER => carta_atual <= "0101";
                when STATE_NOVA_CARTA_DEALER => carta_atual <= "0110";
                when others => carta_atual <= "0000";
            end case;
        else
            carta_atual <= unsigned(cards);
        end if;
        
        case current_state is
            when STATE_INICIO =>
                if start = '1' then
                    next_state <= STATE_CARTA_USER_1;
                end if;
                
            when STATE_CARTA_USER_1 =>
                next_state <= STATE_CARTA_USER_2;
                
            when STATE_CARTA_USER_2 =>
                    next_state <= STATE_ESPERAR_USER;
                
            when STATE_ESPERAR_USER =>
                if hit_btn = '1' then
                    next_state <= STATE_HIT;
                elsif stay_btn = '1' then
                    next_state <= STATE_STAY;
                end if;
                if soma_user = 21 then
                    next_state <= STATE_USER_GANHOU;
                elsif soma_user > 21 then
                    next_state <= STATE_USER_PERDEU;
                end if;
                
            when STATE_HIT =>
                    next_state <= STATE_ESPERAR_USER;
                
            when STATE_STAY =>
                next_state <= STATE_CARTA_1_DEALER;
                
            when STATE_CARTA_1_DEALER =>
                next_state <= STATE_CARTA_2_DEALER;
                
            when STATE_CARTA_2_DEALER =>
                if soma_dealer >= 17 then
                    next_state <= STATE_COMPARAR_CARTAS;
                else
                    next_state <= STATE_NOVA_CARTA_DEALER;
                end if;
                
            when STATE_NOVA_CARTA_DEALER =>
                if soma_dealer >= 17 then
                    next_state <= STATE_COMPARAR_CARTAS;
                end if;
                
            when STATE_COMPARAR_CARTAS =>
                -- Condições atualizadas para comparação correta
                if soma_dealer > 21 then
                    -- Dealer estourou, usuário ganha
                    next_state <= STATE_USER_GANHOU;
                elsif soma_user = soma_dealer then
                    -- Empate
                    next_state <= STATE_TIE;
                elsif soma_user > soma_dealer then
                    -- Usuário tem pontuação maior
                    next_state <= STATE_USER_GANHOU;
                else
                    -- Dealer tem pontuação maior
                    next_state <= STATE_USER_PERDEU;
                end if;
                
            when STATE_USER_GANHOU =>
                win_out <= '1';
                if start = '1' then
                    next_state <= STATE_INICIO;
                end if;
                
            when STATE_USER_PERDEU =>
                lose_out <= '1';
                if start = '1' then
                    next_state <= STATE_INICIO;
                end if;
                
            when STATE_TIE =>
                tie_out <= '1';
                if start = '1' then
                    next_state <= STATE_INICIO;
                end if;
        end case;
    end process;

    -- Processo para localizar o estado atual
    process(current_state)
    begin
        -- Desativar todas as saídas inicialmente
        INICIO <= '0';
        CARTA_USER_1 <= '0';
        CARTA_USER_2 <= '0';
        ESPERAR_USER <= '0';
        HIT <= '0';
        STAY <= '0';
        CARTA_1_DEALER <= '0';
        CARTA_2_DEALER <= '0';
        NOVA_CARTA_DEALER <= '0';
        COMPARAR_CARTAS <= '0';
        USER_GANHOU <= '0';
        USER_PERDEU <= '0';
        TIE <= '0';

        case current_state is
            when STATE_INICIO =>
                INICIO <= '1';
            when STATE_CARTA_USER_1 =>
                CARTA_USER_1 <= '1';
            when STATE_CARTA_USER_2 =>
                CARTA_USER_2 <= '1';
            when STATE_ESPERAR_USER =>
                ESPERAR_USER <= '1';
            when STATE_HIT =>
                HIT <= '1';
            when STATE_STAY =>
                STAY <= '1';
            when STATE_CARTA_1_DEALER =>
                CARTA_1_DEALER <= '1';
            when STATE_CARTA_2_DEALER =>
                CARTA_2_DEALER <= '1';
            when STATE_NOVA_CARTA_DEALER =>
                NOVA_CARTA_DEALER <= '1';
            when STATE_COMPARAR_CARTAS =>
                COMPARAR_CARTAS <= '1';
            when STATE_USER_GANHOU =>
                USER_GANHOU <= '1';
            when STATE_USER_PERDEU =>
                USER_PERDEU <= '1';
            when STATE_TIE =>
                TIE <= '1';
            when others =>
                null;
        end case;
    end process;
    
end Behavioral;