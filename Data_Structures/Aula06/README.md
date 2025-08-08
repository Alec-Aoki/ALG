# LISTAS
-> pilhas, filas e deques são listas com comportamentos específicos <br />
-> lista **linear** = sequência de componentes do mesmo tipo <br />
-> propriedade estrutural: posição relativa tal que $x_{i-1}$ precede $x_i$, que precede $x_{i+1}$ <br />
-> em outras palavras: tem alguém antes e alguém depois (se $n \g 1$, $n$ o tamanho da lista) <br />
-> como escolher o tipo de lista? <br />
-> considerar o tamanho, frequência de uso, frequência das operações e eficiência
    -> sequencial e linear: listas pequenas, de tamanho máximo conhecido e com poucas remoções e inserções

## Ordenação
- a lista pode diferir no **tipo de ordenação**
    - ordenada: inserção no local correto seguindo a ordenação por chaves; facilita buscas (binária ou sequencial otimizada), mas inserir e remover é mais custoso
    - não ordenada: inserção livre, podendo ser nas extremidades ou no meio; facilita inserção e remoção, mas buscar é mais custoso (sequencial)

## TAD Lista (Linear e Sequencial)
-> itens armazenados em posições contíguas na memória <br />
-> pode ser percorrida em qualquer direção <br />
-> custo de inserção constante (basta indexar), $O(1)$ <br />

```c
struct lista_{
    ITEM *item[TAM_MAX]; //vetor de ponteiros que apontam para itens
    int inicio;
    int fim; //indica próxima posição livre para inserir o item
    //int tamanho;
    bool ordenada;
};

struct item_{
    int chave;
    void *dado;
};
```

```c
//lista.h
#ifndef LISTA_H
    #define LISTA_H

    typedef struct lista_ LISTA;

    LISTA *lista_criar(bool ordenacao);
    bool lista_inserir(LISTA *lista, ITEM *item);
    ITEM *item_remover(LISTA *lista, ITEM *item);
    ITEM *lista_busca(LISTA *lista, ITEM *item);
    bool lista_apagar(LISTA **lista);
#endif
```

### Operações Principais
- criar lista
```c
LISTA *lista_criar(bool ordenacao){
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    
    if(lista != NULL){
        lista->inicio = 0;
        lista->fim = 0;
        //lista->tamanho = 0;
        lista->ordenada = ordenacao; //OBS: ordenação em ordem crescente!
    }

    return lista;
}
```

- inserir item
```c
bool lista_inserir(LISTA *lista, ITEM *item){
    if(lista == NULL) return false;
    if(lista_cheia(lista)) return false;

    if(!(lista->ordenada)){
        return lista_inserir_fim(lista, item);
    }

    else{
        int posicao = lista_busca_ordenada(lista, item_get_chave(item));
        
        return lista_inserir_posicao(lista, item, posicao);
    }
}
```

```c
bool lista_inserir_fim(LISTA *lista, ITEM *item){
    if(lista == NULL) return false;
    if(lista_cheia(lista)) return false;

    lista->item[lista->fim] = item;
    lista->fim++;
    //lista->tamanho++;

    return true;
}
```

```c
bool lista_inserir_posicao(LISTA *lista, ITEM *item, int posicao){
    //mais complexo e custoso
    if(lista == NULL) return false;
    if(lista_cheia(lista)) return false;

    /*shiftando todos os elementos da lista para a direita, abrindo espaço pro novo item*/
    for(int i = (lista->fim)-1; i >= posicao; i--){
        lista->item[i+1] = lista->item[i];
    }

    lista->item[posicao] = item;
    lista->fim++;
    //lista->tamanho++;

    return true;
}
```

- remover item 
```c
ITEM *lista_remover(LISTA *lista, int chave){
    if(lista == NULL) return NULL;
    if(lista_vazia(lista)) return NULL;

    int itemAux = lista_busca(lista, chave);
    int posicaoItem = item_get_chave(itemAux);

    lista->fim--; //lista->fim agora guarda o index do elemento no fim da lista

    if(itemAux != NULL){
        for(int i=posicaoItem; i<lista->fim; i++){
            lista->item[i] = lista->item[i+1];
        }
    }

    //lista->tamanho--;

    return itemAux;
}
```

- **busca**/recuperação de um item (dada uma chave)
```c
ITEM *lista_busca(LISTA *lista, int chave){
    if(lista == NULL) return NULL;
    if(lista_vazia(lista)) return NULL;

    int posicaoItem = -1;
    if(lista->ordenada){
        posicaoItem = lista_busca_ordenada(lista, chave);
    }
    else{
        posicaoItem = lista_busca_sequencial(lista, chave);
    }

    if(posicaoItem >= 0){
        return lista->item[posicaoItem];
    }
    else{
        return NULL;
    }
}
```

```c
int lista_busca_sequencial(LISTA *lista, int chave){
    if(lista == NULL) return -1;
    if(lista_vazia(lista)) return -1;

    for(int i=0; i<lista->fim; i++){
        if(item_get_chave(lista->item[i]) == chave) return i;
    }

    return -1;
}
```

```c
int lista_busca_ordenada(LISTA *lista, int chave){
    if(lista == NULL) return -1;
    if(lista_vazia(lista)) return -1; 

    /* busca sequencial otimizada:
    int i=0;

    while(item_get_chave(lista->item[i]) < chave){
        i++;
        if(i >= lista->fim) break;
        if(item_get_chave(lista->item[i]) == chave) return i;
    }
    */

    return busca_binaria(lista, lista->inicio, lista->fim-1, chave);
}
```

```c
int busca_binaria(LISTA *lista, int inicio, int fim, int chave){
    if(fim == -1) return 0;

    while(inicio < fim){
        int meio=(inicio+fim)/2;
        
        if(chave <= item_get_chave(lista->lista[meio])) fim = meio;
        else{
            inicio = meio+1;
        }
    }

    if(item_get_chave(lista->lista[inicio]) >= chave) return inicio;
    else{
        return fim+1;
    }
}
```