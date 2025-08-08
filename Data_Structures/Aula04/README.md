# PILHA (TAD) (II)

## TAD Pilha (Dinâmica)
-> OBS: a interface NÃO muda!!!

### Struct Sequencial
-> utiliza um vetor estático
-> sabemos o tamanho da pilha *a priori*
```c
struct pilha{
    ITEM *item[TAM]; //vetor de ponteiros para itens, ESTÁTICO
    int topo; //guarda o índice do topo da pilha
};
```

### Struct Dinâmica
-> utiliza **NÓS**
-> **não precisamos saber o tamanho da pilha!**
```c
typedef no_ NO;
typedef pilha_ PILHA;

struct no_{
    ITEM *item;
    NO *proximoNo; 
    //empilhando ponteiros numa pilha, o nó do topo aponta para "baixo", ou seja, o nó anterior a ele na pilha (apesar de ser o próximo nó na cadeia de nós)
};

struct pilha_{
    NO *noTopo; //aponta para o nó no topo da pilha
    int topo; //quantidade de nós na pilha
};
```

### Operações Principais
- **EMPILHAR**
```c
bool pilha_empilhar(PILHA *pilha, ITEM *item){
    if((pilha == NULL) || (item == NULL)) return false;

    if(!pilha_cheia(pilha)){ //funciona para o caso da pilha vazia também!!!
        NO *noItem = (NO *)malloc(sizeof(NO));
        if(noItem == NULL) return false;

        noItem->item = item;
        noItem->proximoNo = pilha->noTopo;

        pilha->noTopo = noItem;
        (pilha->topo)++;

        return true;
    }

    return false;
}
```

- **DESEMPILHAR**
```c
ITEM *pilha_desempilhar(PILHA *pilha){
    if(pilha_vazia(pilha)) return NULL;

    ITEM *itemAux = (pilha->noTopo)->item;

    NO *noAux = pilha->noTopo;

    pilha->noTopo = noAux->proximoNo;

    noAux->proximoNo = NULL;
    noAux->item = NULL;
    free(noAux);
    
    (pilha->topo)--;
    return itemAux;
}
```

### Operações Auxiliares
- criar uma pilha vazia
```c
PILHA *pilha_criar(void){
    PILHA *ponteiroPilha;
    ponteiroPilha = (PILHA *)malloc(sizeof(PILHA));

    if(ponteiroPilha != NULL){
        ponteiroPilha->noTopo = NULL; // (*ponteiroPilha).noTopo = NULL;
        ponteiroPilha->topo = 0;
    }
        
    return ponteiroPilha;
}
```
- verificar se a pilha está cheia
```c
bool pilha_cheia(PILHA *pilha){
    if(pilha == NULL) return false;

    NO *noVerificacao = (NO *)malloc(sizeof(NO));
    if (noVerificacao != NULL){
        free(noVerificacao);
        return false; //não há mais espaço para alocar nós
    }
    //else
    return true;
}
```
- apagar a pilha (e os nós)
```c
void pilha_apagar(PILHA **pilha){
    if(*pilha == NULL) return;

    while((*pilha)->topo > 0){
        /*desempilhar e apagar o item*/
        /*poderia ter sido feito chamando a função desempilhar*/
        NO *noAux = (*pilha)->noTopo;

        (*pilha)->noTopo = noAux->proximoNo;

        item_apagar(noAux->item);
        noAux->proximoNo = NULL;
        noAux->item = NULL;
        free(noAux);
        
        ((*pilha)->topo)--;
    }

    free(*pilha);
    *pilha = NULL;
    return;
}
```