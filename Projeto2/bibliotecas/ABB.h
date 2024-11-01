#ifndef ABB_H
  #define ABB_H

  typedef struct abb_ ABB;

  ABB *abb_criar(void);
  void abb_apagar(ABB **arvore);
  bool abb_inserir(ABB *arvore, int elemento);
  int abb_remover(ABB *arvore, int chave);
  void abb_imprimir(ABB *arvore, bool ordenada);
  int abb_busca(ABB *arvore, int chave);

#endif