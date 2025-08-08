#ifndef LISTA_H
	#define LISTA_H

	#include "item.h"
	                       
	typedef struct lista_ LISTA;

	LISTA *lista_criar(bool ordenacao);
	bool lista_inserir(LISTA *lista, ITEM *item);
	ITEM *lista_remover(LISTA *lista, int chave);
	bool lista_apagar(LISTA **lista);
	ITEM *lista_busca(LISTA *lista, int chave);
	int lista_tamanho(LISTA *lista);
	bool lista_vazia(LISTA *lista);
	bool lista_cheia(LISTA *lista);
	void lista_imprimir(LISTA *lista, bool comQuebraDeLinha);

	/*funções extras*/
	ITEM *lista_remover_inicio(LISTA *lista);
	ITEM *lista_remover_fim(LISTA *lista);
#endif
