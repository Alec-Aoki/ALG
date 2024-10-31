#ifndef CONJUNTO_H
  #define CONJUNTO_H

  #define LISTA 0
  #define ARVORE 1

  typedef struct conjunto_ CONJUNTO;

  CONJUNTO *conjunto_criar(int TAD);
  bool conjunto_apagar(CONJUNTO **conj, int TAD);
  bool conjunto_inserir(CONJUNTO *conj, int TAD, int elemento);
  int conjunto_remover(CONJUNTO *conj, int TAD, int elemento);
  void conjunto_imprimir(CONJUNTO *conj, int TAD);
  bool conjunto_pertence(CONJUNTO *conj, int TAD, int elemento);
  CONJUNTO *conjunto_uniao(CONJUNTO *conjA, CONJUNTO *conjB, int TAD);
  CONJUNTO *conjunto_interseccao(CONJUNTO *conjA, CONJUNTO *conjB, int TAD);

#endif