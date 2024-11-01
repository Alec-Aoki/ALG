#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../bibliotecas/conjunto.h"

void test_conjunto_criar() {
    printf("Testing conjunto_criar():\n");
    
    // Test valid TAD_LISTA creation
    CONJUNTO *conj_lista = conjunto_criar(TAD_LISTA);
    if (conj_lista == NULL) {
        printf("FAIL: Failed to create list-based conjunto\n");
    } else {
        printf("PASS: Successfully created list-based conjunto\n");
        conjunto_apagar(&conj_lista);
    }

    // Test valid TAD_ARVORE creation
    CONJUNTO *conj_arvore = conjunto_criar(TAD_ARVORE);
    if (conj_arvore == NULL) {
        printf("FAIL: Failed to create heap-based conjunto\n");
    } else {
        printf("PASS: Successfully created heap-based conjunto\n");
        conjunto_apagar(&conj_arvore);
    }

    // Test invalid TAD
    CONJUNTO *conj_invalid = conjunto_criar(2);
    if (conj_invalid != NULL) {
        printf("FAIL: Should not create conjunto with invalid TAD\n");
        conjunto_apagar(&conj_invalid);
    } else {
        printf("PASS: Correctly prevented creation with invalid TAD\n");
    }
}

void test_conjunto_inserir_e_pertence() {
    printf("\nTesting conjunto_inserir() and conjunto_pertence():\n");
    
    // Test list-based conjunto
    CONJUNTO *conj_lista = conjunto_criar(TAD_LISTA);
    conjunto_inserir(conj_lista, 10);
    conjunto_inserir(conj_lista, 20);
    conjunto_inserir(conj_lista, 30);

    if (!conjunto_pertence(conj_lista, 10)) {
        printf("FAIL: Element 10 not found in list-based conjunto\n");
    }
    if (!conjunto_pertence(conj_lista, 20)) {
        printf("FAIL: Element 20 not found in list-based conjunto\n");
    }
    if (conjunto_pertence(conj_lista, 40)) {
        printf("FAIL: Non-existent element 40 reported as present\n");
    }
    conjunto_apagar(&conj_lista);

    // Test heap-based conjunto
    CONJUNTO *conj_arvore = conjunto_criar(TAD_ARVORE);
    conjunto_inserir(conj_arvore, 10);
    conjunto_inserir(conj_arvore, 20);
    conjunto_inserir(conj_arvore, 30);

    if (!conjunto_pertence(conj_arvore, 10)) {
        printf("FAIL: Element 10 not found in heap-based conjunto\n");
    }
    if (!conjunto_pertence(conj_arvore, 20)) {
        printf("FAIL: Element 20 not found in heap-based conjunto\n");
    }
    if (conjunto_pertence(conj_arvore, 40)) {
        printf("FAIL: Non-existent element 40 reported as present\n");
    }
    conjunto_apagar(&conj_arvore);
}

void test_conjunto_uniao() {
    printf("\nTesting conjunto_uniao():\n");
    
    // Test list-based conjunto union
    CONJUNTO *conj_lista_a = conjunto_criar(TAD_LISTA);
    conjunto_inserir(conj_lista_a, 10);
    conjunto_inserir(conj_lista_a, 20);

    CONJUNTO *conj_lista_b = conjunto_criar(TAD_LISTA);
    conjunto_inserir(conj_lista_b, 20);
    conjunto_inserir(conj_lista_b, 30);

    CONJUNTO *uniao_lista = conjunto_uniao(conj_lista_a, conj_lista_b);
    
    printf("União de conjuntos (lista):\n");
    conjunto_imprimir(uniao_lista);

    conjunto_apagar(&conj_lista_a);
    conjunto_apagar(&conj_lista_b);
    conjunto_apagar(&uniao_lista);
}

void test_conjunto_interseccao() {
    printf("\nTesting conjunto_interseccao():\n");
    
    // Test list-based conjunto intersection
    CONJUNTO *conj_lista_a = conjunto_criar(TAD_LISTA);
    conjunto_inserir(conj_lista_a, 10);
    conjunto_inserir(conj_lista_a, 20);

    CONJUNTO *conj_lista_b = conjunto_criar(TAD_LISTA);
    conjunto_inserir(conj_lista_b, 20);
    conjunto_inserir(conj_lista_b, 30);

    CONJUNTO *interseccao_lista = conjunto_interseccao(conj_lista_a, conj_lista_b);
    
    printf("Intersecção de conjuntos (lista):\n");
    conjunto_imprimir(interseccao_lista);

    conjunto_apagar(&conj_lista_a);
    conjunto_apagar(&conj_lista_b);
    conjunto_apagar(&interseccao_lista);
}

int main() {
    test_conjunto_criar();
    test_conjunto_inserir_e_pertence();
    test_conjunto_uniao();
    test_conjunto_interseccao();
    
    return 0;
}