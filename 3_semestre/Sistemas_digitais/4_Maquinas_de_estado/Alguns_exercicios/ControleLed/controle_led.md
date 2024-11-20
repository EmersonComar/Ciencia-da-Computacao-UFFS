
### Partes
- **Estados**: DESLIGADO, LIGADO
- **Transições**: DESLIGADO para LIGADO e LIGADO para DESLIGADO
- **Entradas**: Ligar, Desligar, Resete, clock
- **Saídas**: Led

### Tabela de transição de estados

| Estado atual | Entrada | Próximo estado | Saída |
| ------------ | ------- | -------------- | ----- |
| DESLIGADO | Ligar = 1 | LIGADO | Led = 1 |
| LIGADO | Desligar = 1 | DESLIGADO | Led = 0 |
| LIGADO | Ligar = 1 | LIGADO | Led = 1 |
| DESLIGADO | Desligar = 1 | DESLIGADO | Led = 0 |

### Diagrama de estados
```plantuml
@startuml
[*] --> DESLIGADO : Ligar = 0
DESLIGADO : Led = 0
DESLIGADO --> LIGADO : Ligar = 1
DESLIGADO --> DESLIGADO : Ligar = 0
LIGADO : Led = 1
LIGADO --> DESLIGADO : Desligar = 1
LIGADO --> LIGADO : Desligar = 0
@enduml
```