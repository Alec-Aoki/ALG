# FILAS E DEQUES
## Filas (Sequenciais)
-> política "FIFO" -> First In First Out <br />
-> implementação **circular**

### Operações Principais
- struct fila
```c
struct fila_{
    ITEM *item[TAM_MAX];
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
    return fila->total;
}
```
- verifica se a fila está cheia
```c
bool fila_cheia(FILA *fila){
    if(fila->total == TAM) return true;
    
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
