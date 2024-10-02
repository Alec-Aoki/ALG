# Melhorias em Operações das Listas
## Listas Encadeadas com Nó Cabeça
- operação mais complexa da lista simplesmente encadeada: **remoção**
    - ela é a mesma para todos os nós da lista, exceto para o primeiro
    - nó cabeça = nó que vem antes do nó de início -> remove essa exceção!!
    - basta trocar lista->inicio por noCabeca->noSeguinte

    ```c
    typedef struct lista_{
        NO *cabeca;
        NO *fim;
        int tamanho;
        bool ordenada;
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

## Listas Encadeadas Circulares


## Listas Encadeadas Ordenadas