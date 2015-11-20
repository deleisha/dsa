#include "llist.h"
#include <iostream>
#include <cassert>

typedef struct my_list {
    int value;
    sl_list_t nd;
} test_list;

//static test_list l[3] = { .value = 10};

int main()
{
    SL_LIST_HD(hdr);

    test_list first = { .value = 10, .nd = { .nxt = NULL }};
    test_list second = { .value = 20, .nd = { .nxt = NULL }};

    sllist_insert(&(first.nd), 1, &hdr);
    sllist_insert(&(second.nd), 1,  &hdr);


    for( sl_list_t *n = hdr.nxt; n; n = n->nxt) {
        test_list *nd = SL_LIST_ENTRY(n, test_list, nd);
        std::cout << nd->value << std::endl;
    }

    assert( 2 == sllist_len(hdr.nxt));
}
