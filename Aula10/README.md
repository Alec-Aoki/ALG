# Árvores Binárias

- Árvore em que os demais nós além da raíz $r$ podem ser subdivididos em duas outras árvores, $T_e$ (sub-árvore da esquerda) e $T_d$ (sub-árvore da direita), que também são árvores binárias (podendo ser vazias ou não);
  - Um nó possui, no máximo, 2 filhos (**árvore de grau 2**);
- Ordem: a raíz $r$ é o menor elemento da árvore, e seus filhos são os próximos menores elementos;
```
                          1
                  2             3
                4             9   
```
- Vantagens:
  - Encadeada (memória);
  - Ordenada (busca binária);
    - Complexidade: $O(d)$, $d$ a altura/profundidade da árvore.

## Árvores Estritamente Binárias/Próprias

- Seus nós tem somente 0 ou 2 filhos, sempre;
  - Não há nós com 1 filho;
- Os nós interiores (não-folhas) têm sempre 2 filhos;
- Os nó folha têm sempre 0 filhos;
- **Não garante a menor altura possível**.
```
                          1
                  2             3
              4       7
            9   10
```

### Árvores Binárias Completas Cheias (ABCC)

- Árvore Estritamente Binária com todos os nós folhas no mesmo nível;
- **Garante a menor altura**;
```
                          1
                  2             3
                4   7         9   10 
```
- $n = 2^{d+1} - 1$, $n$ a quantidade total de nós da árvore e $d$ a profundidade da árvore;
- $d = \log_{2}(n + 1) - 1$;
- Desvantagem: necessidade de manter todos os níveis cheios.
```
                          1
                  2             3
                4   7         9   10 
              11 N N N       N N N  N
```

## Árvore Binária Completa (ABC)

- Se a profundidade da árvore é $d$, então cada nó folha está no nível $d - 1$ ou $d$;
- O nível $d - 1$ está totalmente preenchido;
- Os nós folha no nível $d$ estão todos mais à esquerda (podia ser direita) possível.
cheios.
```
                          1
                  2             3
                4   7         9   10 
              11
```

## Árvore Binária Perfeitamente Balanceada

- Para cada nó, a quantidade de nós das sub-árvores $T_e$ e $T_d$ diferem em, no máximo, 1.

## Árvore Binária Balanceada

- Para cada nó, a altura das suas sub-árvores diferem em, no máximo, 1.