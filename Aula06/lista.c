#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "item.h"
#include "lista.h"

#define ERRO -1;

struct lista_{
    ITEM *item[100];
    int inicio;
    int fim;
    bool ordenada;
};