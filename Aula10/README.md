# Árvores Binárias

- Árvore em que os demais nós além da raíz $r$ podem ser subdivididos em duas outras árvores, $T_e$ (sub-árvore da esquerda) e $T_d$ (sub-árvore da direita), que também são árvores binárias (podendo ser vazias ou não);
  - Um nó possui, no máximo, 2 filhos (**árvore de grau 2**);
- Ordem: a raíz $r$ é o menor elemento da árvore, e seus filhos são os próximos menores elementos;
```
                          1
                  2             3
                4   7         9   
```
- Vantagens:
  - Encadeada (memória);
  - Ordenada (busca binária).

## Árvores Estritamente Binárias / Próprias

- Seus nós tem somente 0 ou 2 filhos, sempre;
  - Não há nós com 1 filho;
- Os nós interiores (não-folhas) têm sempre 2 filhos;
- Os nó folha têm sempre 0 filhos;