#ifndef ITEM_H
    #define ITEM_H

    typedef struct item_ ITEM;

    ITEM *item_criar(void *dado, int index);
    bool item_apagar(ITEM **item);
    void *item_getDado(ITEM *item);
#endif