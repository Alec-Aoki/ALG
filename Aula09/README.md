# Introdução a Árvores
- Listas: organização linear de dados (relação sequencial entre elementos);
- Árvores: organização não-linear de ados (relação **HIERÁRQUICA** entre elementos);
  - Beneficiam operações de *busca* (não precisamos percorrer todas as informações, como uma lista);
  - Maior representatividade de informações;
  - Facilidade na manipulação de dados;
  - **Tornam possível realizar uma busca seletiva em uma estrutura encadeada**;
    - Mantém a facilidade de inserção e remoção de uma estrutura encadeada;
    - Mantém a facilidade de busca em uma estrutura sequencial;
- Exemplo: árvores genealógicas, índices de um livro etc.

## Árvores
- Definição formal: um conjunto finito de elementos (chamados de nós ou vértices) composto pela união de subconjuntos disjuntos (sem sobreposição, chamados subárvores);
  - O elemento no topo da árvore é chamado de *raiz*;
  - $ T = \{ T_1, T_2, T_3, ..., T_v \} $, com $r$ a raíz da árvore e $T_v$ uma subárvore com raíz em $v$;
  - Definição recursiva;
- Modos de representação (gráficas):
  - Conjuntos aninhados;
    - Diagrama de Venn/representação de conjuntos;
    - $ T = \{ D, \{E, F\}, \{G, \{H\}\} \} $;
  - Indentação;
  - **Grafos**;
  ```
                            D
                E                       G
                F               H       J      M
                                I      K L
  ```
- Terminlogia:
  - **Graus**:
    - Grau *do nó*: quantidade de subárvores;
      - Grau 0: nó *folha*, não possui subárvores;
    - Grau *da árvore*: se cada nó possui um grau máximo, e esse grau é o mesmo para todos os nós, então esse é o grau da árvore;
      - Exemplo: uma árvore binária é uma árvore de grau 2;
  - **Relações hierárquicas**:
    - Nó filho: cada raiz $r_i$ da subárvore $T_i$ é filha da raíz $r$;
    - Nó neto: análogo à anterior;
    - Nó pai: o nó raíz $r$ da árvore $T$ é o pai de todas as raízes $r_i$ das subárvores $T_i$;
    - Nó avô: análogo à anterior;
    - Nó irmão: duas raízes $r_i$ e $r_j$ das subárvores $T_i$ e $T_j$ da árvore $T$ são irmãs (nós no mesmo nível hierárquico);
  - **Caminho**:
    - Sequência não vazia de nós em que o nó $r_i$ é pai do nó $r_{i+1}$;
    - $ P = \{ r_1, r_2, ..., r_k \} $;
  - **Comprimento**:
    - Comprimento de um caminho;
    - $ C_P = k-1 $, $k$ a quantidade de nós em um caminho $P$;
  - **Altura**:
    - De um nó: comprimento do caminho mais longo do nó até uma folha;
      - Folhas têm altura zero;
    - Pode haver mais de um caminho!;
    - Da árvore: altura da raíz de $r$ de $T$;
  - **Profundidade**:
    - Comprimento do **único** caminho da raíz $r$ até o nó $r_i$;
  - **Nível**:
    - Conjunto de nós na mesma profundidade;
    - A raíz está no nível zero;
  - **Ascendência e descendência**:
    - O nó $r_i$ é ancestral de $r_j$ de existe um caminho de $r_i$ a $r_j$ com comprimento diferente de zero;
    - Lógica análoga para o descendente.