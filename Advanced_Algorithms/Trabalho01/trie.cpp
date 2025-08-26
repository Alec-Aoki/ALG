#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <memory>
#include "trie.h"
using namespace std;

void trie_inserir_priv(NO *noRaiz, string palavra);
void trie_check_linha_priv(NO* noRaiz, string linha, string palavraAtual, set<string>& resultado);

/* Nó da árvore trie */
struct no_{
    char letra = '0'; // Chave
    bool fimPalavra = false; // Flag
    vector<unique_ptr<NO>> nosFilhos; // Vetor de ponteiros para nós filhos
};

struct trie_{
    unique_ptr<NO> noRaiz = nullptr;
};

/* **** Funções Públicas **** */

/* Aloca espaço para a struct trie e inicializa ela */
TRIE* trie_criar(void){
    TRIE *novaTrie = new TRIE();
    if(novaTrie == NULL) return NULL; // Erro

    novaTrie->noRaiz = make_unique<NO>();
    if(novaTrie->noRaiz == nullptr) { // Erro
        delete novaTrie;
        return NULL;
    }

    novaTrie->noRaiz->letra = '0';
    novaTrie->noRaiz->fimPalavra = false;

    return novaTrie;
}

/* Insere uma palavra na trie */
void trie_inserir(TRIE *arv, string palavra){
    if(arv == NULL || palavra.empty()) return;

    trie_inserir_priv(arv->noRaiz.get(), palavra);
}

/* Busca palavras em uma linha (recursivo) */
set<string> trie_check_linha(TRIE* arv, string linha){
    if(arv == NULL || linha.empty()){
        set<string> vetorVazio;
        return vetorVazio;
    }

    set<string> resultado;
    
    for(int i = 0; i < linha.length(); i++) {
        string str = linha.substr(i);
        trie_check_linha_priv(arv->noRaiz.get(), str, "", resultado);
    }

    return resultado;
}

/* **** Funções Privadas **** */

/* Insere uma palavra na trie (recursivo) */
void trie_inserir_priv(NO *noRaiz, string palavra){
    if(noRaiz == NULL || palavra.empty()) return;

    // Caso o nó raíz tenha filhos, procura a letra neles
    for(unique_ptr<NO>& no : noRaiz->nosFilhos){
        // Comparando a letra do nó com o a primeira letra da palavra
        if(no->letra == palavra.front()){
            // Removendo primeira letra da palavra
            palavra = palavra.substr(1);

            // Inserindo no nó encontrado
            trie_inserir_priv(no.get(), palavra);
            return;
        }
    }
    // Else:
    // Caso a letra não seja encontrada nos filhos do nó raiz,
    // cria um nó novo com a letra e a insere como filho da raíz
    unique_ptr<NO> noNovo = make_unique<NO>();
    noNovo->letra = palavra.front();
    noNovo->fimPalavra = false;

    // Guarda o ponteiro antes de mover
    NO* ptrNoNovo = noNovo.get();
    noRaiz->nosFilhos.push_back(move(noNovo));
    
    // Se for a última letra, marca a flag e retorna
    if(palavra.length() == 1){
        ptrNoNovo->fimPalavra = true;
        return;
    } 

    // Senão, continua adicionando as letras como nós filhos
    palavra = palavra.substr(1);
    trie_inserir_priv(ptrNoNovo, palavra); // Inserindo o resto das letras
    
    return;
}

/* Busca palavras em uma linha (recursivo) */
void trie_check_linha_priv(NO* noRaiz, string linha, string palavraAtual, set<string>& resultado){
   if(noRaiz == NULL || linha.empty()) return;

   // Percorre os nós filhos procurando pela primeira letra da linha
   for(unique_ptr<NO>& no : noRaiz->nosFilhos){
       // Se encontrar um nó com a letra desejada
       if(no->letra == linha.front()){
           // Constrói a nova palavra adicionando a letra encontrada
           string novaPalavra = palavraAtual + no->letra;

           // Se este nó marca o fim de uma palavra válida, adiciona ao resultado
           if(no->fimPalavra) resultado.insert(novaPalavra);

           // Se ainda há mais letras na linha, continua a busca recursivamente
           if(linha.length() > 1) trie_check_linha_priv(no.get(), linha.substr(1), novaPalavra, resultado);

           return;
       }
   }
}

/* Desaloca tudo */
void trie_destruir(TRIE* arv){
    if(arv == NULL) return;
    
    delete arv;
}