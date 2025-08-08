# Árvores Rubro-Negras
- Versão Left Leaning;
- ABB;
- Arestas coloridas;
  - Vermelha;
  - Preta;
- Regras;
  - Aresta vermelha sempre vai pro filho esquerdo;
  - Todo nó possui, no máximo, uma aresta vermelha;
    - Pode ter zero arestas vermelhas;
    - Arestas incidentes (que levam ao nó) e descendentes (que saem dele) **contam**;
  - Balanceamento preto perfeito;
    - **Distância Preta**: todas as folhas estão à mesma distância da raíz (aresta vermelha não conta);
- Altura no pior caso: $2 \log(n)$;

## Operações
- **Inserção**;
  - Igual à ABB;
  - **Todo nó é inserido em uma aresta vermelha**;
  - Nó pai sem aresta vermelha incidente;
    - Pode necessitar de uma **rotação para esquerda** e inversão de cores;
  - Nó pai com aresta vermelha incidente (veio de uma aresta vermeha);
    - Pode necessitar de **rotações para a direita** e inversão de cores;
  - As rotações são iguais à AVL;
  - Inversão de cores:
    - Duas arestas filhas vermelhas se tornam pretas, enquanto a aresta incidente preta se torna vermelha;
  - OBS: a cor da aresta incidente da raíz vai ser sempre preta;
    - Se ela mudar pra vermelha, mudar de volta pra preta.
```C
/*Código para inverter as cores das arestas*/

#define PRETA 0
#define VERMELHA 1

typedef struct no_{
  int chave;
  int cor;
  NO *noDir;
  NO *noEsq;
} NO;

void no_inverter_cor(NO *no){
  if(no == NULL) return;

  no->noDir->cor = PRETA;
  no->noEsq->cor = PRETA;
  no->cor = VERMELHA;

  return;
}
```

- **Remoção**;
  - OBS: por padrão, a aresta que leva a um nó nulo é preto;
  - Sempre ocorre no nó folha com aresta vermelha;
  - Aplicar conceitos de remoção da ABB quando o nó **não** for folha;
    - Substituir chave;
  - Propagar aresta vermelha da raíz até a folha (se preciso);
    - Busca pela esquerda: ```moveRedLeft```;
    - Busca pela direita: ```moveRedRight```;
  - Realizar rotações e inversões na volta da recursão;
  - Se ```h->esq``` e ```h->esq->esq``` for preta (```h``` é o ponteiro):
    - **moveRedLeft**: 2 casos;
      - Se ```h->dir->esq``` for preta: inveter ```h```;
      - Se ```h->dir->esq``` for vermelha: inveter ```h```, rotDir ```h->Dir```, rotEsq ```h```, inverte ```pai de h```;
      - Voltar na recursão corrigindo a árvore que nem na remoção;
  - Se ```h->dir``` e ```h->dir->esq``` for preta (NÃO TERMINADO);
    - **moveRedRight**: 2 casos;
      - Se ```h->dir->esq``` for preta: inveter ```h```;
      - Se ```h->dir->esq``` for vermelha: inveter ```h```, rotDir ```h->Dir```, rotEsq ```h```, inverte ```pai de h```;
      - Voltar na recursão corrigindo a árvore que nem na remoção;