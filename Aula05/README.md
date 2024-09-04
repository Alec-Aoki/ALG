# FILAS E DEQUES
## Filas
-> política "FIFO" -> First In First Out <br />
-> o primeiro elemento a entrar será o primeiro a ser retirado <br />
```

a
a b
a b c
b c
c

```
- **sequencial**: elementos contíguos na memória, espaço alocado constante
    - implementação **circular**
        - o ponteiro início aponta para o primeiro elemento da fila
            - remover elemento: anular o espaço apontado por início e mover o ponteiro para o próximo espaço
        - o ponteiro fim aponta para espaço seguinte ao último elemento da fila
            - adicionar elemento: adicionar o elemento no espaço apontado e mover o ponteiro uma posição pra frente
        - contador de quantidade de elementos
    - todas as operações são O(1)

- encadeada: alocação dinâmica, uso de nós e os ponteiros início e fim
    - todas as operações são O(1), com exceção do apagar, que é O(n)

### Operações Principais
- struct fila
```c
struct fila_{
    ITEM *item[TAM_MAX]; //sequencial
    int inicio;
    int fim;
    int total;
};

typedef struct fila_ FILA;
```
- criar uma fila vazia
```c
FILA *fila_criar(void){
    FILA *fila = (FILA *)malloc(sizeof(FILA));
    if(fila != NULL){
        fila->inicio = 0;
        fila->fim = 0;
        fila->total = 0;
    }

    return fila;
}
```
- inserir um elemento (no fim) da fila
```c
bool fila_inserir(FILA *fila, ITEM *item){
    if(fila == NULL || item == NULL) return false;
    if(fila_cheia(fila)) return false;

    fila->item[fila->fim] = item;
    (fila->fim)++;
    if(fila->fim == fila->total) fila->fim = 0; //fila->fim = (fila->fim+1)%TAM_MAX;
    (fila->total)++;

    return true;
}
```
- remover um elemento da fila (o primeiro inserido)
```c
ITEM *fila_remover(FILA *fila){
    if(fila == NULL) return NULL;
    if(fila_vazia(fila)) return NULL;

    ITEM *itemAux = fila->item[fila->inicio];
    fila->item[fila->inicio] = NULL;
    (fila->inicio)++;

    return itemAux;
}
```

### Operações Auxiliares
- verificar qual elemento está no início da fila
```c
ITEM *fila_frente(FILA *fila){
    if(fila == NULL) return NULL;
    if(fila_cheia(fila)) return NULL;

    return fila->item[(fila->fim)-1];
}
```
- verifica o tamanho da fila
```c
int fila_tamanho(FILA *fila){
    if(fila == NULL) return -1;

    return fila->total;
}
```
- verifica se a fila está cheia
```c
bool fila_cheia(FILA *fila){
    if(fila != NULL){
        if(fila->total == TAM) return true;
    }
    
    return false;
}
```
- verifica se a fila está vazia
```c
bool fila_vazia(FILA *fila){
    if(fila->total == 0) return true;

    return false;
}
```

## Deques
-> Double Ended QUEue <br />
-> permitem remover e adicionar das duas pontas <br />
- implementação **sequencial**: circular
    - struct e operações similares à fila sequencial
    - remover do fim
    ```c
    ITEM* deque_remover_fim(DEQUE* deque){
        if(deque == NULL) return NULL;
        if(deque_vazia(deque)) return NULL;

        if(deque->fim == 0){
            deque->fim = MAX_TAMANHO-1;
        }
        else{
            (deque->fim)--;
        }

        ITEM *itemAux = deque->item[deque->fim];
        deque->item[deque->fim] = NULL;

        return itemAux;
    }
    ```
    - inserir no início
    ```c
    bool deque_inserir_inicio(DEQUE* deque, ITEM* item){
        if(deque == NULL || item == NULL) return false;
        if(deque_cheia(deque)) return false;

        if(deque->inicio == 0 && deque->item[deque->inicio] != NULL){
            deque->inicio = MAX_TAMANHO-1;
        }
        else if (deque->inicio != 0){
            (deque->inicio)--;
        }

        deque->item[deque->inicio] = item;
        (deque->total)++;

        return true;
    }
    ```
    - O(1)
- implementação **dinâmica**: duplamente encadeada
    - O(1)

### Operações Principais
```c
struct no_{
    ITEM *pontItem;
    NO* noAnterior;
    NO* noSeguinte;
};

typedef struct no_ NO;

struct deque_{
    NO* noInicio;
    NO* noFim;
    int total;
};

typedef struct deque_ DEQUE;
```

- inserir no início
```c
```

- remover do início
```c
```

- inserir no fim
```c
```

- remover do fim
```c
```

### Operações Auxiliares
- retornar elemento no início

- retornar elemento no fim

- retornar quantidade total de elementos

- verificar se está vazio

- verificar se está cheio