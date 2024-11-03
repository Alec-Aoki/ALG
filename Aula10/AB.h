#ifndef AB_H
  #define AB_H

  #define PRE_ORDEM 0
  #define EM_ORDEM 1
  #define POS_ORDEM 2
  #define ESQ 0
  #define DIR 1

  typedef struct ab_ AB;

  AB *ab_criar(void);
  void ab_apagar(AB **arv);
  bool ab_inserir(AB *arv, int elemento);
  int ab_remover(AB *arv);
  void ab_imprimir(AB *arvore, int ordem);
  int ab_busca(AB *arvore, int chave);
  AB *ab_copiar(AB *arvore);
  bool ab_cheia(AB *arvore);

#endif