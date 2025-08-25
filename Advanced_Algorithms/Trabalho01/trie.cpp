#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include "trie.h"
using namespace std;

/* Nó da árvore trie */
struct no_{
    char letra = '0'; // Chave
    bool fimPalavra = false; // Flag
    vector<NO*> nosFilhos; // Vetor de ponteiros para nós filhos
};

struct trie_{
    NO* noRaiz = NULL;
};

/* Aloca espaço para a struct trie e inicializa ela */
TRIE* trie_criar(void){
    TRIE *novaTrie = new TRIE();
    if(novaTrie == NULL) return NULL; // Erro

    NO* noRaiz = new NO();
    if(noRaiz == NULL) return NULL; // Erro

    noRaiz->letra = '0';
    noRaiz->fimPalavra = false;

    novaTrie->noRaiz = noRaiz;

    return novaTrie;
}

/* Insere uma palavra na trie (recursivo) */
void trie_inserir_priv(NO *noRaiz, string palavra){
    if(noRaiz == NULL || palavra.empty()) return;

    // Caso o nó raíz tenha filhos, procura a letra neles
    for(NO* no : noRaiz->nosFilhos){
        // Comparando a letra do nó com o a primeira letra da palavra
        if(no->letra == palavra.front()){
            // Removendo primeira letra da palavra
            palavra = palavra.substr(1);
            // Inserindo no nó encontrado
            trie_inserir_priv(no, palavra);
            return;
        }
    }
    // Else:
    // Caso a letra não seja encontrada nos filhos do nó raiz,
    // cria um nó novo com a letra e a insere como filho da raíz
    NO* noNovo = new NO();
    noNovo->letra = palavra.front();
    noNovo->fimPalavra = false;
    noRaiz->nosFilhos.push_back(noNovo);
    
    // Se for a última letra, marca a flag e retorna
    if(palavra.length() == 1){
        noNovo->fimPalavra = true;
        return;
    } 

    // Senão, continua adicionando as letras como nós filhos
    palavra = palavra.substr(1);
    trie_inserir_priv(noNovo, palavra); // Inserindo o resto das letras
    
    return;
}

void trie_inserir(TRIE *arv, string palavra){
    if(arv == NULL || palavra.empty()) return;

    trie_inserir_priv(arv->noRaiz, palavra);
}

void trie_check_linha_priv(NO* noRaiz, string linha, string palavraAtual, set<string>& resultado){
    if(noRaiz == NULL || linha.empty()) return;

    for(NO* no : noRaiz->nosFilhos){
        if(no->letra == linha.front()){
            string novaPalavra = palavraAtual + no->letra;

            if(no->fimPalavra) resultado.insert(novaPalavra);

            if(linha.length() > 1) trie_check_linha_priv(no, linha.substr(1), novaPalavra, resultado);

            return;
        }
    }
}

set<string> trie_check_linha(TRIE* arv, string linha){
    if(arv == NULL || linha.empty()){
        set<string> vetorVazio;
        return vetorVazio;
    }

    set<string> resultado;
    
    for(int startPos = 0; startPos < linha.length(); startPos++) {
        string substring = linha.substr(startPos);
        trie_check_linha_priv(arv->noRaiz, substring, "", resultado);
    }

    return resultado;
}

/* *********************************************************** */

// Helper function to print words from the current node
void imprimir_palavras_priv(NO* noAtual, string palavra) {
    if (noAtual == NULL) return;

    // Only add letter if it's not the root (root has '0')
    if (noAtual->letra != '0') {
        palavra += noAtual->letra;
    }

    // If it's the end of a word, print it
    if (noAtual->fimPalavra) {
        cout << palavra << endl;
    }

    // Recursively print the words from each child
    for (NO* noFilho : noAtual->nosFilhos) {
        imprimir_palavras_priv(noFilho, palavra);
    }
}

// Function to print all words in the trie
void trie_imprimir(TRIE* arv) {
    if (arv == NULL || arv->noRaiz == NULL) return;

    // Start DFS from the root
    imprimir_palavras_priv(arv->noRaiz, "");
}