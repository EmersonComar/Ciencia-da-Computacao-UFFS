#include <stdlib.h>
#include <string.h>
#include "tabelahash.h"

struct hash{
    int qtd, TABLE_SIZE;
    struct aluno **itens;
};

Hash *criaHash(int TABLE_SIZE) {
    Hash *ha = (Hash *)malloc(sizeof(Hash));

    if (ha == NULL){
        return NULL;
    }

    ha->TABLE_SIZE = TABLE_SIZE;
    ha->itens = (Hash **)malloc(TABLE_SIZE * sizeof(struct aluno*));

    if(ha->itens == NULL){
        free(ha);
        return NULL;
    }

    ha->qtd = 0;
    for(int i=0; i < ha->TABLE_SIZE; i++){
        ha->itens[i] = NULL;
    }

    return ha;
}

void liberaHash(Hash *ha){
    if(ha != NULL){
        for(int i = 0; i < ha->TABLE_SIZE; i++){
            if(ha->itens[i] != NULL){
                free(ha->itens[i]);
            }
        }
        free(ha->itens);
        free(ha);
    }
}

/*
 * Método da divisão

 * Consiste em calcular o "resto da divisão" do 
 * valor interio que representa o elemento pelo tamanho da tabela, "TABLE_SIZE"
 * Função simples e direta
 * 
 * OBS.: A operação "E bit-a-bit" com o valor 0x7FFFFFFF elimina o bit de sinal do valor
 * da chave. Evita o risco de ocorrer um overflow e obtermos um número negativo

*/

int chaveDivisao(int chave, int TABLE_SIZE){
    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

/*
 * Método da Multiplicação 
 * 
 * Usa um valor "A", "0 < A < 1", para multiplicar o valor da "chave" que
 * representa o elemento. Em seguida, a "parte fracionária" resultante é multiplicada
 * pelo tamanho da tabela para calcular a posição do elemento
 * 
*/

int chaveMultiplicacao(int chave, int TABLE_SIZE){
    float A = 0.6180339887;
    float val = chave * A;
    val = val - (int) val;
    return (int) (TABLE_SIZE * val);
}

/*
 * Metodo da Dobra
 * 
 * Utiliza um esquma de dobrar e somar os dígitos do valor para calcular a sua posição
 * 
 * Considera o "valor inteiro" que representa o elemento como uma sequência de dígitos
 * escritos num pedaço de papel. Enquanto esse valor for maior que o tamanho da tabela, o papel
 * é dobrado e os dígitos sobrepostos são somados, desconsiderando-se as dezenas
 * 
 * Pode ser usado com valores binários. 
 * Utiliza a operação de "ou exclusivo"
 * A dobra é realizada de "k em K bits", o que resulta em um valor de posição entre "0 e 2^k+1"
 * 
 * Exemplo:
 * Posição do valor 71 (0001000111 em binário)
 * k = 5
 * 
 * posição = 00010 "ou exclusivo" 00111
 * posição = 00101
 * posição = 5
*/

int chaveDobra(int chave, int TABLE_SIZE){
    int num_bits = 10;
    int parte1 = chave >> num_bits;
    int parte2 = chave & (TABLE_SIZE - 1);
    return (parte1 ^ parte2);
}

/*
 * Tratando uma string como chave
 * 
 * Calcular um valor numéro a partir dos valores ASCII dos caracteres
 *
 * Devemos considerar a posição da letra
 * 
 * Cuidado
 * Não devemos apenas somar os caracteres, pois palavras com letras trocadas
 * irão produzir o mesmo valor
*/

int valorString(char *str){
    int i, valor = 7;
    int tam = strlen(str);
    for(i=0; i < tam; i++){

        //alguns estudos indicam que múltiplicar por 31 é uma boa
        valor = 31 * valor + (int) str[i];
    }
    return valor;
}

/*
 * Inserção e Busca na tabela hash
 * 
 * Sem tratamento de colisão
 * 
 * Inserção
 *  - Calcular a posição da chave no array
 *  - Alocar espaço para os dados
 *  - Armazenar os dados na posição calculada
*/

int insereHash_SemColisao(Hash *ha, struct aluno al){
    
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE){
        return 0;
    }
    int chave = al.matricula;
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    
    struct aluno *novo; 
    novo = (struct aluno*) malloc(sizeof(struct aluno));
    if(novo == NULL){
        return 0;
    }

    ha->itens[pos] = novo;
    ha->qtd++;
    return 1;
}

/*
 * Busca
 *  - Calcular a posição da chave no array
 *  - Verificar se há dados na posição calculada
 *  - Retornar os dados
*/

int buscaHash_SemColisao(Hash *ha, int mat, struct aluno *al){
    if (ha == NULL){
        return 0;
    }

    int pos = chaveDivisao(mat, ha->TABLE_SIZE);
    if(ha->itens[pos] == NULL){
        return 0;
    }
    *al = *(ha->itens[pos]);
    return 1;
}


/*
 * Problema
 * 
 * A função de hashing está sujeita ao
 * problema de gerar posições iguais para
 * chaves diferentes
 * 
 * Por setratar de uma função determinística,
 * ela pode ser manupulada de forma indesejada
 * 
 * Conhecendo a função de hashing, pode-se
 * escolher as chaves de entrada de modo que
 * todas colidam, diminuindo o desempenho da
 * tabela na busca para O(n)
 * 
 * 
 * 
 * 
 * Hashing universal
 * 
 * É uma estratégia que busca minimizar 
 * esse problema de colisões
 * 
 * Basicamente, devemos escolher aleatóriamente
 * (em tempo de execução) a função de hashing que
 * será utilizada
 * 
 * Para tanto, construimos um conjunto (ou família)
 * de funções de hashing
 * 
 * 
 * 
 * 
 * Exemplo de família de funções
 * 
 * Escolha um número primo 'p' de tal modo
 * que o valor de qualquer chave 'k' a ser
 * inserida na tabela seja 'menor' do que 'p'
 * e 'maior ou igual a zero', '0 <= k < p'
 * 
 * 'p' é maior do que o tamanho da tabela TABLE_SIZE
 * 
 * Escolha, aleatoriamente, dois números inteiros 'a' e 'b':
 * 0 < a <= p
 * 0 <= b <= p
 * 
 * Função de hashing universal
 * 
 * h(k)_{a,b} = ((ak + b) % p) % TABLE_SIZE
 *
*/


int sondagemLinear(int pos, int i, int TABLE_SIZE){
    return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}


/*
 * pos = posição obtida pela função de hashing 
 * i = tentantiva atual
 * 
*/

int sondagemQuadratica(int pos, int i, int TABLE_SIZE){
    pos = pos + 2*i + 5*i*i;
    return (pos & 0x7FFFFFFF) % TABLE_SIZE;
}



/*
 * Inserção e busca na tabela hash 
 *
 * Com tratamento de colisão
 * 
 * 
 * Inserção
 *  - Calcular a posiçao da chave no array
 *  - Recalcular a posição enquanto houver
 * colisão (limitar o número de tentativas)
 *  - Alocar espaço para os dados
 *  - Armazenar os dados na posição calculada
*/

int insereHash_EnderAberto(Hash *ha, struct aluno al){

    if(ha == NULL || ha->qtd == ha->TABLE_SIZE){
        return 0;
    }

    int chave = al.matricula;
    int i, pos, newPos;
    
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    for(i=0; i < ha->TABLE_SIZE; i++){
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        if(ha->itens[newPos] == NULL){
            struct aluno *novo = (struct aluno*) malloc(sizeof(struct aluno));

            if(novo == NULL){
                return 0;
            }

            *novo = al;
            ha->itens[newPos] = novo;
            ha->qtd++;
            return 1;
        }
    }
    return 0;
}

/*
 * Busca
 * - Calcular a posição da chave no array
 * - Verificar se há dados na posição calculada
 * e se esses dados combinam com a chave
 * - Recalcular a posição enquanto os dados
 * forem diferentes da chave
 * - Retornar os dados
*/


int buscaHash_EnderAberto(Hash *ha, int mat, struct aluno *al){

    if(ha == NULL){
        return 0;
    }

    int i, pos, newPos;
    pos = chaveDivisao(mat, ha->TABLE_SIZE);
    for(i=0; i < ha->TABLE_SIZE; i++){
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        if(ha->itens[newPos] == NULL){
            return 0;
        }

        if(ha->itens[newPos]->matricula == mat){
            *al = *(ha->itens[newPos]);
            return 1;
        }
    }
    return 0;
}