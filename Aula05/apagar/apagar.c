#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "fila.h"

#ifndef _STRUCTS_
    #define _STRUCTS_

    typedef struct no_ {
    ITEM* item;
    struct no_* proximo;
    }noObj;

    typedef noObj NO;

    typedef struct fila_ {
    NO* inicio;
    NO* fim;
    int tamanho;
    }filaObj;

    typedef filaObj FILA;
#endif