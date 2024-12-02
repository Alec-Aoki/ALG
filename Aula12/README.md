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
  - Balanceamento negro perfeito;
    - **Distância Negra**: todas as folhas estão à mesma distância da raíz (aresta vermelha não conta);
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
  - OBS: a cor da aresta incidente da raíz vai ser sempre negra;
    - Se ela mudar pra vermelha, mudar de volta pra negra.
```C
/*Código para inverter as cores das arestas*/

#define NEGRA 0
#define VERMELHA 1

typedef struct no_{
  int chave;
  int cor;
  NO *noDir;
  NO *noEsq;
} NO;

void no_inverter_cor(NO *no){
  if(no == NULL) return;

  no->noDir->cor = NEGRA;
  no->noEsq->cor = NEGRA;
  no->cor = VERMELHA;

  return;
}
```