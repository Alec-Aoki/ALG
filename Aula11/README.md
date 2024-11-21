# Árvores AVL
- ABB em que as alturas das duas sub-árvores de um mesmo nó não diferem mais que 1;
  - **Fator de Balanceamento** do nó: diferença entre as alturas das suas sub-árvores;
    - Na AVL, só pode ser 0 (alturas iguais), 1 (árvores esquerda maior que a direita )ou -1 (árvore direita maior que a esquerda);
- Na árvore ABB, não garantimos o balanceamento (pior caso $$O(n)$$) ao inserir e remover elementos. **A árvore AVL garante o balanceamento**;
- Para manter uma AVL balanceada após uma inserção ou remoção, a transformamos de modo que:
  - A árvore continue sendo uma ABB (percurso em-ordem não muda);
  - A árvore transformada está balanceada.

## Rotação (Transformação)
- Pode ser feita para a direita ou para a esquerda, a depender do desbalanceamento;
- Uma única rotação pode não ser suficiente para balancear a árvore;
```
                  ROTAÇÃO DIREITA

            A                     B
        B      [T3]        [T1]         A
    [T1] [T2]               C       [T2]  [T3]
  C

A -> nó mais jovem a se tornar desbalanceado
T1, T2, T3 -> sub-árvores de qualquer tamanho válido
C -> nó inserido que gerou o desbalanceamento
```
```
                  ROTAÇÃO ESQUERDA

            A                         B
      [T1]      B                A        [T3]
            [T2] [T3]        [T1] [T2]     C
                   C
```