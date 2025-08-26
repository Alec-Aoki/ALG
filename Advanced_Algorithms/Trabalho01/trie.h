#ifndef TRIE_H
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <memory>
using namespace std;

typedef struct trie_ TRIE;
typedef struct no_ NO;

TRIE* trie_criar(void);
void trie_inserir(TRIE *arv, string palavra);
set<string> trie_check_linha(TRIE* arv, string linha);
void trie_destruir(TRIE* arv);

#endif