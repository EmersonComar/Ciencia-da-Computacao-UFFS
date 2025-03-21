#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

#define ASCII 256

  char *ler_texto(FILE *amostra){
    fseek(amostra, 0, SEEK_END);
    long tamanho_texto = ftell(amostra);
    rewind(amostra);

      char *texto = (char *) malloc((tamanho_texto + 1) * sizeof(  char));
    if (texto == NULL){
        return NULL;
    }

    long bytes_lidos = fread(texto, sizeof(  char), tamanho_texto, amostra);
    texto[bytes_lidos] = '\0';

    return texto;

}


  int *criar_tabela_frequencia(  char *texto){
      int *tabela = (  int *) malloc(ASCII * sizeof(  int));

    for(size_t i = 0; i<ASCII; i++){
        tabela[i] = 0;
    }

    for(size_t i=0; i<strlen(texto); i++){
        tabela[(unsigned char)texto[i]]++;
    }

    return tabela;
}


Fila_prioridade *ciar_fila_prioridade(){
    Fila_prioridade *novo = (Fila_prioridade*) malloc(sizeof(Fila_prioridade));
    if(novo == NULL){
        fprintf(stderr, "Erro ao criar fila de prioridade\n");
        exit(1);
    }

    novo->quantidade = 0;
    novo->elementos = NULL;

    return novo;
}

Node *criar_node(  char caractere,   int frequencia){
    Node *novo = (Node*) malloc(sizeof(Node));
    if(novo == NULL){
        fprintf(stderr, "Erro ao criar fila de prioridade\n");
        exit(1);
    }

    novo->caractere = caractere;
    novo->frequencia = frequencia;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->prox = NULL;

    return novo;
}

void adicionar_node_fila(Fila_prioridade *fila, Node *novo){
    if(fila->elementos == NULL){
        fila->elementos = novo;
    } else if(novo->frequencia < fila->elementos->frequencia){
        novo->prox = fila->elementos;
        fila->elementos = novo;
    }else{
        Node *aux = fila->elementos;
        while(aux->prox != NULL && novo->frequencia >= aux->prox->frequencia)
        aux = aux->prox;
        novo->prox = aux->prox;
        aux->prox = novo;
    }
}

void adicionar_node_arvore(Fila_prioridade *fila, Node *novo){
    if(fila->elementos == NULL){
        fila->elementos = novo;
    } else if(novo->frequencia < fila->elementos->frequencia){
        novo->prox = fila->elementos;
        fila->elementos = novo;
    }else{
        Node *aux = fila->elementos;
        while(aux->prox != NULL && novo->frequencia > aux->prox->frequencia)
        aux = aux->prox;
        novo->prox = aux->prox;
        aux->prox = novo;
    }
}

void preencher_fila_prioridade(Fila_prioridade *fila,   int *tabela_frequencia){
    for(int i = 0; i < ASCII; i++){
        if(tabela_frequencia[i] != 0){
            Node *novo = criar_node(i, tabela_frequencia[i]);
            adicionar_node_fila(fila, novo);
            fila->quantidade++;
        }
    }
}

void gerar_arvore_huffman(Fila_prioridade *fila){
    if(fila == NULL)
        return;

    int i = 1;
    while(fila->quantidade > 1){
        Node *novo = criar_node('\0', 0);
        Node *aux = fila->elementos;


        novo->frequencia = aux->frequencia + aux->prox->frequencia;
        novo->esq = aux;
        novo->dir = aux->prox;

        
        if(fila->quantidade > 2){
            fila->elementos = aux->prox->prox;
            adicionar_node_arvore(fila, novo);
        }else{
            fila->elementos = novo;
        }
        fila->quantidade--;
        i++;
        
    }
}

int altura_arvore(Node *node){
    int dir, esq;

    if(node == NULL) 
        return 0;

    esq = altura_arvore(node->esq) + 1;
    dir = altura_arvore(node->dir) + 1;

    if( esq > dir)
        return esq;
    else
        return dir;
}

  char **alocar_dicionario(Node *node){
    int colunas = altura_arvore(node) + 1;

      char **dicionario = (  char **) malloc(ASCII * sizeof(  char *));
    if(dicionario == NULL){
        fprintf(stderr, "Erro ao alocar memória para o dicionário\n");
        exit(1);
    }

    for(int i = 0; i<ASCII; i++){
        dicionario[i] = NULL;
    }

    for(int i=0; i<ASCII; i++){
        dicionario[i] = (  char *) malloc(colunas * sizeof(  char));
        if(dicionario[i] == NULL){
            fprintf(stderr, "Erro ao alocar memória para o dicionário\n");
            exit(1);
        }

        dicionario[i][0] = '\0';
    }

    return dicionario;
}

void preencher_dicionario_r(Node *node,   char **dicionario, char *codigo, int colunas){

    if(node == NULL)
        return;

    if(node->esq == NULL && node->dir == NULL){
        strcpy(dicionario[(unsigned char)node->caractere], codigo);
    }else{
        char esquerda[colunas], direita[colunas];

        snprintf(esquerda, colunas, "%s0", codigo);
        snprintf(direita, colunas, "%s1", codigo);

        preencher_dicionario_r(node->esq, dicionario, esquerda, colunas);
        preencher_dicionario_r(node->dir, dicionario, direita, colunas);
    }
}

void preencher_dicionario(Fila_prioridade *fila,   char **dicionario){
    int colunas = altura_arvore(fila->elementos);
    preencher_dicionario_r(fila->elementos, dicionario, "\0", colunas);
}


int tamanho_str(  char **dicionario,   char *texto){
    int tam = 0;
    int i = 0;
    while(texto[i] != '\0'){
        tam = tam + strlen(dicionario[texto[i]]);
        i++;
    }

    return tam + 1;
}


  char *codificar(  char **dicionario,   char *texto){
    int tamanho = tamanho_str(dicionario, texto);
      char *codigo = (  char *) calloc(tamanho, sizeof(  char));
    int i = 0;
    while(texto[i] != '\0'){
        strcat(codigo, dicionario[(unsigned char)texto[i]]);
        i++;
    }

    return codigo;
}


char *decodificar(Fila_prioridade *fila,   char *texto){
    int i = 0;
    Node *aux = fila->elementos;
    char str_temp[2];
    char *decodificado = calloc(strlen(texto), sizeof(char));

    while (texto[i] != '\0'){
        if (texto[i] == '0')
            aux = aux->esq;
        else
            aux = aux->dir;
        
        if(aux->esq == NULL && aux->dir == NULL){
            str_temp[0] = aux->caractere;
            str_temp[1] = '\0';
            strcat(decodificado, str_temp);
            aux = fila->elementos;
        }

        i++;
    }

    return decodificado;
}



void compactar(  char *texto){
    FILE *codificado = fopen("codificado.txt", "wb");
    int i = 0;
    int contador = 7;
      char mascara, byte = 0;
    
    if(codificado == NULL){
        fprintf(stderr, "Erro ao abrir arquivo codificado\n");
        exit(1);
    }

    while (texto[i] != '\0'){
        mascara = 1;
        if(texto[i] == '1'){
            mascara = mascara << contador;
            byte = byte | mascara;
        }
        contador--;

        if(contador < 0){
            fwrite(&byte, sizeof(  char), 1, codificado);
            byte = 0;
            contador = 7;
        }

        i++;
    }

    if(contador != 7){
        fwrite(&byte, sizeof(  char), 1, codificado);
    }

    fclose(codificado);
}


  int validar_bit(  char byte, int i){
      char mascara = (1 << i);
    return byte & mascara;
}

  char *descompactar(Fila_prioridade *fila){
    FILE *codificado = fopen("codificado.txt", "rb");
    Node *aux = fila->elementos;
      char byte;
    int i;
    
    int capacidade = ASCII;
      char *decodificado = (  char*) malloc(capacidade * sizeof(  char));
    int tamanho = 0;
    
    if(codificado == NULL){
        fprintf(stderr, "Erro ao abrir arquivo codificado.txt");
        exit(1);
    }

    while(fread(&byte, sizeof(  char), 1, codificado)){
        for(i = 7; i>= 0; i--){
            if(validar_bit(byte, i))
                aux = aux->dir;
            else
                aux = aux->esq;
            

            if(aux->dir == NULL && aux->esq == NULL){
                if(tamanho + 1>= capacidade){
                    capacidade *= 2;

                    decodificado = realloc(decodificado, capacidade * sizeof(  char));
                    if(decodificado == NULL){
                        fprintf(stderr, "Erro na alocação de memória\n");
                        fclose(codificado);
                        exit(1);
                    }
                }

                decodificado[tamanho++] = aux->caractere;
                aux = fila->elementos;
            }
        }
    }

    fclose(codificado);
    decodificado[tamanho] = '\0';
    return decodificado;
}


void exibir_dicionario(  char **dicionario){
    for(int i=0; i<ASCII; i++){
        if(strlen(dicionario[i]) > 0)
            printf("%c: %s\n", i, dicionario[i]);
    }
}


void limpar_strings(  char *texto){
    free(texto);
}

void limpar_tabela_frequencia(  int *tabela_frequencia){
    free(tabela_frequencia);
}

void limpar_fila_prioridade_r(Node *node){
    if(node == NULL) return;

    limpar_fila_prioridade_r(node->esq);
    limpar_fila_prioridade_r(node->dir);

    free(node);

}

void limpar_fila_prioridade(Fila_prioridade *fila){
    if(fila == NULL) return;
    
    limpar_fila_prioridade_r(fila->elementos);
    free(fila);
}

void limpar_dicionario(  char **dicionario){
    for(int i = 0; i < ASCII; i++){
        free(dicionario[i]);
    }
    free(dicionario);
}