| Estado | Função | Entradas | Saídas | Transição |
|--------|---------|-----------|---------|------------|
| INICIO | Define o modo de inserção de cartas baseado em Random_Cards | - Random_Cards (1=aleatório, 0=manual)<br>- Start | - Reset Win, Tie, Lose para 0<br>- Reset dos displays de contagem e carta jogada | → CARTA USER 1 |
| CARTA USER 1 | Recebe a primeira carta do usuário e exibe no display | - modo_aleatorio<br>- clk | - Atualiza display de carta jogada<br>- Atualiza soma_user | → CARTA USER 2 |
| CARTA USER 2 | Recebe a segunda carta do usuário e aplica regras do Ás | - modo_aleatorio<br>- clk | - Atualiza display de carta jogada<br>- Atualiza soma_user<br>- Se soma_user = 21, Win = 1 | Se soma_user = 21 → USER GANHOU<br>Caso contrário → ESPERAR USER |
| ESPERAR USER | Aguarda ação do usuário (nova carta ou finalizar) | - Hit<br>- Stay | - Display de contagem inalterado | Se Hit = 1 → HIT<br>Se Stay = 1 → STAY |
| HIT | Usuário solicita nova carta | - modo_aleatorio | - Atualiza display de carta jogada<br>- Atualiza soma_user<br>- Se soma_user > 21, Lose = 1<br>- Se soma_user = 21, Win = 1 | Se soma_user > 21 → USER PERDEU<br>Se soma_user = 21 → USER GANHOU<br>Caso contrário → ESPERAR USER |
| STAY | Usuário encerra jogada; dealer inicia | - clk | - Display de contagem inalterado | → CARTA 1 DEALER |
| CARTA 1 DEALER | Dealer recebe primeira carta | - modo_aleatorio | - Atualiza display de carta jogada<br>- Atualiza soma_dealer | → CARTA 2 DEALER |
| CARTA 2 DEALER | Dealer recebe segunda carta | - modo_aleatorio | - Atualiza display de carta jogada<br>- Atualiza soma_dealer | Se soma_dealer >= 17 → COMPARAR CARTAS<br>Se soma_dealer < 17 → NOVA CARTA DEALER |
| NOVA CARTA DEALER | Dealer solicita nova carta se soma < 17 | - modo_aleatorio | - Atualiza display de carta jogada<br>- Atualiza soma_dealer | Se soma_dealer < 17 → NOVA CARTA DEALER<br>Se soma_dealer >= 17 → COMPARAR CARTAS |
| COMPARAR CARTAS | Compara pontuação final do usuário e dealer | - soma_user<br>- soma_dealer | - Se soma_user > soma_dealer ou soma_dealer > 21, Win = 1<br>- Se soma_dealer > soma_user, Lose = 1<br>- Se soma_user = soma_dealer, Tie = 1 | Se Win = 1 → USER GANHOU<br>Se Lose = 1 → USER PERDEU<br>Se Tie = 1 → TIE |
| USER GANHOU | Estado final de vitória do usuário | - Start | - Win = 1<br>- Tie = 0<br>- Lose = 0 | Se Start = 1 → INICIO |
| USER PERDEU | Estado final de derrota do usuário | - Start | - Lose = 1<br>- Win = 0<br>- Tie = 0 | Se Start = 1 → INICIO |
| TIE | Estado final de empate | - Start | - Tie = 1<br>- Win = 0<br>- Lose = 0 | Se Start = 1 → INICIO |