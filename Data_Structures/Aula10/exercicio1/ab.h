#ifndef AB_H
  #define AB_H
 
  #include  "item.h"
  #define ERRO -32000
  #define FILHO_ESQ 0
  #define FILHO_DIR 1

 typedef struct arv_bin AB;
 
 AB *ab_criar(void);
 bool ab_inserir (AB *T, ITEM *item, int lado, int chave);
 void ab_imprimir (AB *T);
 void ab_apagar_arvore(AB **T);
 int ab_estritamente_binaria (AB *T); /*0 = estrt binaria, 1 = nao estrt binaria*/

#endif