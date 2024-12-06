# Algumas funções de dispersão padrão para cada tipo de dados

## Dados inteiros

### função módulo

```C
unsigned int hashInt(int chave, unsigned int tamanho_tabela){
    return chave % tamanho_tabela
}
```

### Multiplicação com fator

Utilizada para gerar melhor dispersão em tabelas de tamanho não-primo:

```C
unsigned int hashIntMul(int chave, unsigned int tamanho_tabela){
    const float A = 0.6180339887; // ((raiz de 5) - 1) / 2
    unsigned int hash = (unsigned int)(tamanho_tabela * (chave * A - (int)(chave * A)));
    return hash;
}
```

---
## Strings

### DJB2

Criada por Dan Bernstein

```C
unsigned int bjb2(const char *str, unsigned int tableSize){
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c // hash * 33 + c
    }

    return hash % tableSize;
}
```

### SDBM

```C
unsigned int sdbm(const char *str, unsigned int tableSize){
    unsigned int hash = 0;
    int c;
    while ((c = *str++)){
        hash = c + (hash << 6) + (hash << 10) - hash;
    }
    return hash % tableSize;
}
```

### MurmurHash

 Função externa que necessita da biblioteca **MurmurHash3.h**

 ```C
 #include "MurmurHash3.h"

 unsigned int murmurhash(const char *str, unsigned int tableSize){
    unsigned int hash;
    MurmurHash3_x86_32(str, strlen(str), 0, &hash);
    return hash % tableSize;
 }
 ```

 ## Estruturas 

 ### Combinação simples

 ```C
 struct key {
    int id;
    char name[50];
 }

 unsigned int hashStruct(struct key key, unsigned int tableSize){
    unsigned int hashId = key.id % tableSize;
    unsigned int hashName = djb2(key.name, tableSize);
    return (hashId + hashName) % tableSize;
 }
 ```