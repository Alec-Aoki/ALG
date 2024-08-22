# PILHA (TAD) (II)

## TAD Pilha (Dinâmica)
-> OBS: a interface NÃO muda!!!

### Struct Sequencial
-> utiliza um vetor estático
```c
struct pilha{
    ITEM *item[TAM]; //vetor de ponteiros para itens, ESTÁTICO
    int topo; //guarda o índice do topo da pilha
};
```

### Struct Dinâmica
-> utiliza **NÓS**
```c
typedef no_ NO;
typedef pilha_ PILHA;

struct no_{
    ITEM *item;
    NO *proximoNo; 
    //empilhando ponteiros numa pilha, o nó do topo aponta para "baixo", ou seja, o nó anterior a ele na pilha (apesar de ser o próximo nó na cadeia de nós)
};

struct pilha_{
    NO *noTopo;
    int topo;
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

- **DESEMPILHAR (incompleto)**
```c
ITEM pilha_desempilhar(PILHA *pilha){
    if(pilha_vazia(pilha)) return NULL;

    (pilha->topo)--;

    return itemTemp;
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