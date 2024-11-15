/// @file tabela_hash.h
/// @brief Declaração das funções e estruturas utilizadas para manipular a tabela hash
/// @author emerson.comar@estudante.uffs.edu.br
#ifndef TABELA_HASH_H
#define TABELA_HASH_H

/// @struct tlist
/// @brief Estrutura para representar o nó dos valores lidos do arquivo
typedef struct tlist Tlist;

/// @struct hash
/// @brief Estrutura para representar a tabela hash
typedef struct hash Hash;

/// @struct lista
/// @brief Estutura temporária que será utilizada na extração dos números dos arquivos
typedef struct lista Lista;

/// @brief Aloca uma tabela hash com o tamanho especificado
/// @param tamanho_tabela Quantidade de index que a tabela hash terá
/// @return A tabela alocada, ou NULL caso falhar
Hash *criar_tabela(int tamanho_tabela);


/// @brief Libera a memória alocada para a tabela hash
/// @param tabela_hash A tabela hash que será desalocada
void liberar_tabela(Hash *tabela_hash);

/// @brief Transfere os valores da lista encadeada para a tabela hash
/// @param tabela_hash A tabela hash que irá anexar os dados
/// @param lista_tlist A lista que contém os dados que serão transpostos
void inserir_hash(Hash *tabela_hash, Tlist *lista_tlist);


/// @brief Exibe os índices que não estão apontados para nulo
/// @param tabela_hash Estutura na qual os índices serão listados
void exibir_hash(Hash *tabela_hash);


/// @brief Irá extrair os valores numéricos presentes no arquivo e montar uma lista encadeada do tipo Tlist contendo estes valores extraídos.
/// @param arquivo o arquivo na qual os valores numéricos serão extraídos
/// @return Lista encadeada com os valores extraídos dos arquivos
Tlist *criar_tlist(FILE *arquivo);

#endif