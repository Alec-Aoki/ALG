# Melhorias em Operações das Listas
## Listas Encadeadas com Nó Cabeça (Não Ordenada)
- operação mais complexa da lista simplesmente encadeada: **remoção**
    - ela é a mesma para todos os nós da lista, exceto para o primeiro
    - nó cabeça = nó que vem antes do nó de início -> remove essa exceção!!
    - basta trocar lista->inicio por noCabeca->noSeguinte

    ```c
    typedef struct lista_{
        NO *cabeca;
        NO *fim;
        int tamanho;
        bool ordenada = false;
    } LISTA;

    LISTA *lista_criar(bool ordenacao){
        LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
        if(lista == NULL) exit(1);

        NO *noCabeca = (NO *)malloc(sizeof(NO));
        if(noCabeca == NULL) exit(1);

        noCabeca->noSeguinte = NULL;
        lista->inicio = noCabeca->noSeguinte;
        lista->fim = noCabeca->noSeguinte;
        lista->tamanho = 0;
        lista->ordenada = ordenacao;

        return lista;
    }

    ITEM *lista_remover(LISTA *lista){
        if(lista == NULL) exit(1);

        NO *pontNo = lista->noCabeca;
        
        while(pontNo->noSeguinte != NULL){
            if(item_getChave(pontNo->noSeguinte->item) != chave) pontNo = pontNo->noSeguinte;
            else{
                break;
            }
        }

        NO *pontNoAnterior = pontNo;
        pontNo = pontNo->noSeguinte;
        
        ITEM *pontItem = pontNo->item;
        pontNoAnterior->noSeguinte = pontNo->noSeguinte;
        if(pontNo == lista->fim) lista->fim = pontNoAnterior;

        pontNo->noSeguinte = NULL;
        pontNo->item = NULL;
        free(pontNo);
        pontNo = NULL;
        
        lista->tamanho--;

        return pontItem;
    }
    ```

## Listas Encadeadas Circulares (Não Ordenada)
- beneficia a operação de **busca**
- não usa um ponteiro de início, já que o ponteiro de fim aponta para o início (inicio = fim->noSeguinte)
- utiliza um nó sentinela (similar ao cabeça)
    - noSentinela = lista->fim->noSeguinte
    - inserimos nossa chave no noSentinela
    - percorremos a lista sem checar se chegamos no fim
    - ao encontrarmos a chave, saimos do loop e verificamos se para onde estamos apontado é o nó Sentinela
        - se for, a chave não está presente na lista
        - se não for, a chave está presente na lista
- a busca continua $O(n)$, mas realizamos menos comparações
```c
typedef struct lista_{
    NO *sentinela;
    NO *fim;
    int tamanho;
    bool ordenada = false;
} LISTA;

ITEM *lista_busca(LISTA *lista, int chave){
    if(lista == NULL) exit(1);

    item_setChave(&(lista->sentinela->item), chave);
    NO *pontNo = lista->sentinela;

    do{
        pontNo = pontNo->noSeguinte;
    }while(item_getChave(pontNo) != chave);

    if(pontNo == lista->sentinela) return NULL;
    else{
        return pontNo->item;
    }
}
```

## Listas Encadeadas Ordenadas
- o ponteiro de fim não é necessário pois a inserção irá ocorrer em qualquer lugar da lista
- o emprego do nó cabeça **é valido**
- Inserir Ordenado $O(n)$ x Inserir no Fim e Ordernar Logo Depois $O(n log(n))$
    - inserir ordenado é mais barato!
```c
typedef struct lista_{
    NO *cabeca;
    int tamanho;
    bool ordenada = true;
} LISTA;

bool lista_inserir_ordenada(LISTA *lista, ITEM *item){
    if(lista == NULL) exit(1);
    if(lista_cheia(lista)) return false;

    NO *pontNo = lista->cabeca;
    int chave = item_getChave(item);

    while(pontNo->noSeguinte != NULL){
        if(chave > item_getChave(pontNo->noSeguinte->item)) pontNo = pontNo->noSeguinte;
    }

    NO *noNovo = (NO *)malloc(sizeof(NO));
    if(noNovo == NULL) exit(1);
    noNovo->item = item;
    noNovo->noSeguinte = pontNo->noSeguinte;
    pontNo->noSeguinte = noNovo;

    //if(noNovo->noSeguinte == NULL) lista->fim = noNovo;

    lista->tamanho++;

    return true;
}
```