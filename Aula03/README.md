# PILHA (TAD)
## Conceitos Introdutórios
-> objetos **EMPILHADOS** uns em cima dos outros <br />
-> com **ordem** de colocação e retirada! <br />
-> exemplo: uma pilha de pratos :) <br />

### Aplicações
- botão "back" de um navegador
- opção "undo" em um editor de texto
- memória stack (chamada de funções)

### Definição
-> **Last-In/First-Out** (LIFO) <br />
-> o primeiro elemento a ser inserido será sempre o último a ser removido <br />
-> inserções e remoções são feitas na extremidade da pilha (topo) <br />
-> exemplo: um algoritmo para converter um número decimal em binário <br />
```
    até o quociente ser 0:
        -> dividir o número por 2
        -> guardar o resto numa pilha
        -> número = quociente
    para imprimir o número binário:
        -> desempilhar a pilha
            -> já vai estar na ordem certa!
```

### Organização vs Alocação (da Memória)
- Alocação Estática: em tempo de compilação
- Alocação Dinâmica: em tempo de execução

- Organização Sequencial: endereços seguidos
- Organização Encadeada: endereços apontados (por ponteiros)

1. SEQUENCIAL e ESTÁTICA: uso de arrays
2. ENCADEADA e ESTÁTICA: ordenação topológica (arrays encadeados)
3. **SEQUENCIAL e DINÂMICA**: array dinamicamente alocado
4. **ENCADEADA e DINÂMICA**: uso de ponteiros <br />

-> como estamos usando TAD, não podemos alocar estaticamente!

## TAD Pilha (Sequencial)


### Implementação Sequencial
-> + simples <br />
-> **vetor** alocado **dinamicamente**, com tamanho fixo <br />
-> uso de uma variável auxiliar "topo/tamanho", que guarda o índice do topo (espaço livre para receber um elemento) <br />

### Struct
```c
    struct pilha{
        ITEM *item[TAM]; //vetor de ponteiros para itens
        int topo; //guarda o índice do topo da pilha
    };
```

### Operações Principais
- **EMPILHAR**
```c
    bool pilha_empilhar(PILHA *pilha, ITEM *item); //insere x no topo de P

    bool pilha_empilhar(PILHA *pilha, ITEM *item){
        if((pilha == NULL) || (pilha_cheia(pilha)) || (item == NULL)) return false;
        //OBS: ao invés da função pilha_cheia();, podemos usar pilha->topo == TAM

        p->item[p->topo] = item;
        p->topo += 1;

        return true;
    }
```

- **DESEMPILHAR**
```c
    ITEM pilha_desempilhar(PILHA *pilha); //remove o elemento no topo de P e o retorna

    ITEM pilha_desempilhar(PILHA *pilha){
        if(pilha_vazia(pilha)) return NULL; //a função pilha_vazia(); já checa se pilha não é NULL

        ITEM itemTemp = pilha->item[pilha->topo-1];

        pilha->item[pilha->topo-1] = NULL; //apagando o item da pilha

        pilha->topo -= 1; //atualizando o topo

        //quem vai apagar o item vai ser o cliente!

        return itemTemp;
    }
```

### Operações Auxiliares
- criar uma pilha vazia
```c
    PILHA *pilha_criar(void); //pilha vazia, não precisa retornar tamanho

    PILHA *pilha_criar(void){
        PILHA *ponteiroPilha;
        ponteiroPilha = (PILHA *)malloc(sizeof(PILHA));

        if(ponteiroPilha != NULL){
            ponteiroPilha->topo = 0; //pilha vazia
        }
        
        return ponteiroPilha;
    }
```

- apagar uma pilha da memória
```c
    void pilha_apagar(PILHA **pilha);
```

- verificar o elemento no topo da pilha
```c
    ITEM pilha_topo(PILHA *pilha);
```

- tamanho
```c
    int pilha_tamanho(PILHA *pilha);

    int pilha_tamanho(PILHA *pilha){
        if(pilha != NULL) return pilha->topo;

        return -1; //pilha == NULL, erro
    }
```

- verificar se a pilha está vazia
```c
    bool pilha_vazia(PILHA *pilha);

    bool pilha_vazia(PILHA *pilha){
        if((pilha == NULL) || (pilha->topo == 0)) return true;
        //else:
        return false;
    }
```

- verificar se a pilha está cheia (+ útil na implementação sequencial)
```c
    bool pilha_cheia(PILHA *pilha);
```

### Operações Extras
- printar os elementos da pilha
```c
    void pilha_print(PILHA *pilha);
```

- inverter os elementos da pilha
```c
    void pilha_inverter(PILHA *pilha);
```