/// @file tabela_hash.c
/// @brief Implementação de uma tabela de hash onde as colisões são tratadas através de encadeamento separado
/// @author emerson.comar@estudante.uffs.edu.br

#include <stdio.h>
#include <stdlib.h>
#include "tabela_hash.h"

#define MAX_CASAS 10                        ///< Número máximo de casas decimais na qual os números extraídos do arquivo poderão ter

struct tlist{
    int valor;                              ///< Representa o nó que será armazenado no tabela hash
    struct tlist *next;                     ///< Ponteiro para o próximo nó
};

struct hash{
    int quantidade;                         ///< Quantidade de elementos que estarão na tabela hash
    int tamanho_tabela;                     ///< Quantidade buckets que a tabela hash terá
    Tlist **itens;
};

struct lista{
    char casas[MAX_CASAS];                  ///< Array que armazena os dígitos dos elementos extraídos do arquivo
    int quantidade;                         ///< Quantidade de casas decimais que cada valor terá 
};

Hash *criar_tabela(int tamanho_tabela){

    Hash *tabela_hash = (Hash *) malloc(sizeof(Hash));
    if(tabela_hash == NULL){
        return NULL;
    }

    tabela_hash->tamanho_tabela = tamanho_tabela;
    tabela_hash->itens = (Tlist **) malloc(tamanho_tabela * sizeof(Tlist *));
    
    if(tabela_hash->itens == NULL){
        free(tabela_hash);
        return NULL;
    }

    tabela_hash->quantidade = 0;
    for(int i=0; i < tabela_hash->tamanho_tabela; i++){
        tabela_hash->itens[i] = NULL;
    }

    return tabela_hash;
}

/// @brief Liberação da memória alocada referente à lista encadeada
/// @param lista Lista encadeada que será liberada 
void limpar_lista(Tlist *lista){
    Tlist *aux = lista;
    while(aux != NULL){
        Tlist *prox = aux->next;
        free(aux);
        aux = prox;
    }
}

/// @brief Liberação da memória alocada da tabela hash
/// @param tabela_hash Tabela hash que será liberada
void liberar_tabela(Hash *tabela_hash){
    if(tabela_hash != NULL){
        for(int i=0; i < tabela_hash->tamanho_tabela; i++){
            if(tabela_hash->itens[i] != NULL){
                limpar_lista(tabela_hash->itens[i]);
            }
        }
        free(tabela_hash->itens);
        free(tabela_hash);
    }
}

/// @brief Função hash responsável em determinar qual o índice o valor irá ocupar na tabela hash
/// @param chave O valor que deseja inserir na tabela hash
/// @param tamanho_tabela A quantidade de índices que a tabela hash terá
/// @return O valor do índice na qual a chave será armazenada
int chaveDivisao(int chave, int tamanho_tabela){
    return chave % tamanho_tabela; 
}

/// @brief Pesquisa se um determinado valor está presente na tabela hash
/// @param tabela_hash Tabela hash que será pesquisada
/// @param chave Valor que deseja procurar na tabela hash
/// @param posicao Posição em que o valor deverá estar
/// @return Retorna 0 caso encontrado a chave e 1 caso não encontrado
int pesquisa_hash(Hash *tabela_hash, int chave, int posicao){
    for(Tlist *aux = tabela_hash->itens[posicao]; aux != NULL; aux = aux->next){
        if(aux->valor == chave){
            return 0;
        }
    }
    return 1;
}

/**
 * @details
 * Irá percorrer a lista encadeada, criando um node novo e calculando a posição na tabela hash referente.
 * Após, será inserido na tabela. Para evitar duplicata e aumentar a complexidade de busca e inserção, não será 
 * incluídos valores duplicados na tabela hash.
*/

void inserir_hash(Hash *tabela_hash, Tlist *lista_tlist){
    if(tabela_hash == NULL){
        printf("A tabela hash ainda não foi alocada\n");
        return;
    }

    for(Tlist *aux = lista_tlist; aux != NULL; aux = aux->next){
        int chave = aux->valor;
        int posicao;
        posicao = chaveDivisao(chave, tabela_hash->tamanho_tabela);

        Tlist *novo = (Tlist*) malloc(sizeof(Tlist));
        if(novo == NULL){
            printf("Falha ao alocar memória\n");
            liberar_tabela(tabela_hash);
            limpar_lista(lista_tlist);
            exit(1);
        }

        novo->valor = chave;
        novo->next = NULL;

        if(tabela_hash->itens[posicao] == NULL){
            tabela_hash->itens[posicao] = novo;
            printf("Valor %d inserido\n", tabela_hash->itens[posicao]->valor);
        } else {
            Tlist *percorre;
            int insere = 0;
            insere = pesquisa_hash(tabela_hash, chave, posicao);

            if(insere){
                for(percorre = tabela_hash->itens[posicao]; percorre->next != NULL; percorre = percorre->next);
                percorre->next = novo;
                printf("Valor %d inserido\n", percorre->next->valor);
            } else {
                free(novo);
            }
        }

        tabela_hash->quantidade++;
    }

    limpar_lista(lista_tlist);
}

/// @details Percorre os itens da tabela hash que não estejam apontando para NULL e e percorre a lista encadeada, exibindo os valores contidos
void exibir_hash(Hash *tabela_hash){
    if(tabela_hash == NULL){
        printf("A tabela hash ainda não foi alocada\n");
        return;
    }

    for(int i=0; i < tabela_hash->tamanho_tabela; i++){
        if(tabela_hash->itens[i] != NULL){
            printf("[%d] - ", i);
            for(Tlist *aux = tabela_hash->itens[i]; aux != NULL; aux = aux->next){
                printf("%d -> ", aux->valor);
            }
            printf("NULL\n");
        }
    }
}

/// @brief Realiza a operação de potenciasão
/// @param base A base da potência
/// @param expoente Expotente da potência
/// @return O valor calculado da base elevado à potência
int potencia(int base, int expoente){
    int total = 1;
    for(int i=0; i<expoente; i++){
        total *= base;
    }
    return total;
}

/// @brief Irá "converter" as casas decimais no valor numérico correto
/// @details A função utiliza o Princípio Fundamental da Contagem para realizar a conversão
/// @param lista_valores Estrutura de dados que conterá as casas decimais que será transformada no valor numérico
/// @return O valor numérico extraído
int extrair_valor(Lista *lista_valores){
    int valor = 0;
    int expoente = lista_valores->quantidade - 1;
    for(int i = 0; i < lista_valores->quantidade; i++){
        valor += lista_valores->casas[i] * potencia(10, expoente);
        expoente--;
    }

    return valor;
}


/// @brief Cria um novo nó tlist com o valor extraído do arquivo e insere na lista ao final da lista encadeada
/// @param lista_tlist Endereço de memória da primeira posição da lista encadeada
/// @param valor Valor extraído do arquivo na qual será o valor do nó criado
void insere_tlist(Tlist **lista_tlist, int valor){
    Tlist *novo = (Tlist*) malloc(sizeof(Tlist));
    if(novo == NULL){
        printf("Erro ao alocar memória !!\n");
        exit(1);
    }

    novo->valor = valor;
    novo->next = NULL;

    if(*lista_tlist == NULL){
        *lista_tlist = novo;
    } else{
        Tlist *aux;
        for(aux = *lista_tlist; aux->next != NULL; aux = aux->next);
        aux->next = novo;
    }
}

/**
 * @details
 * - Lê cada caracteredo arquivo até o final do arquivo, representado pelo EOF
 * - Caso o valor seja diferente de `;` o valor será armazenado em uma posição no array
 * e o contador `quantidade` será incrementado
 * - Ao encontrar o valor `;` a função `extrair_valor` será chamada e, após, 
 * o valor será inserido na lista encadeada.
 * 
 * @note
 * A função assume que:
 * - O arquivo estará corretamente formatado com apenas `;` e valores numéricos.
 * - Os números não tenham mais do que 10 casas decimais.
 * 
 * @warning A memória alocada precisa ser liberada antes da finalização.
*/
Tlist *criar_tlist(FILE *arquivo) {
    Lista lista_valores;                     
    int valor_extraido = 0;                 
    char caractere;                         
    Tlist *lista_tlist = NULL;              

    lista_valores.quantidade = 0;

    while ((caractere = fgetc(arquivo)) != EOF){
        if( caractere != ';'){
            if (lista_valores.quantidade <= MAX_CASAS){
                lista_valores.casas[lista_valores.quantidade] = caractere - '0';
                lista_valores.quantidade++;
            }
        } else {
            valor_extraido = extrair_valor(&lista_valores);
            lista_valores.quantidade = 0;
            insere_tlist(&lista_tlist, valor_extraido);
        }
    }

    if(lista_valores.quantidade > 0){
        valor_extraido = extrair_valor(&lista_valores);
        lista_valores.quantidade = 0;
        insere_tlist(&lista_tlist, valor_extraido);
    }

    return lista_tlist;
}