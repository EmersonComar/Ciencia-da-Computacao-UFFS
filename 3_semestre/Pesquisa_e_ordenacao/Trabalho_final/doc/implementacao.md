# Código de Huffman

## Implementando do Código de Huffman

Optando em documentar o processo de implementação, a organização do projeto facilitará a realização. A seguir, irei descrever todos os passos que utilizei para a realização do **Trabalho final de POD 2024**

## Etapas do processo de implementação

1. Ler o texto do arquivo `amostra.txt`
1. Gerar uma tabela de frequencia
1. Gerar uma fila de prioridade em relação à frequencia
1. Gerar a árvore de Huffman
1. Gerar a tabela de códigos
1. Codificar o texto
1. Decodificar o texto

### Ler o texto do arquivo amostra

A leitura do arquivo feita da seguinte forma: 

1. Abrir arquivo em modo leitura
1. Determinar o tamanho do conteúdo 
1. Alocar memória dinamicamente para armazenar a string
1. Ler os dados do arquivo para a memória alocada

### Gerando tabela de frequencia