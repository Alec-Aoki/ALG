#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Pilha.h"
#include "item.h"

int main(void){
    char string[101];

    scanf(" %s", string);

    printf("%f\n", rpn(string));

    return 0;
}