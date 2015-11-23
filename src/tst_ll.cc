#include "llist.h"
#include <iostream>
#include <cassert>

typedef struct my_list {
    int value;
    sl_list_t nd;
} test_list;

int main()
{
    SL_LIST_HD(hdr);

    test_list first = { .value = 10, .nd = { .nxt = NULL }};
    test_list second = { .value = 20, .nd = { .nxt = NULL }};
    test_list third = { .value = 30, .nd = { .nxt = NULL }};

    insert(&(first.nd), &hdr);
    insert(&(second.nd), &hdr);
    append(&(third.nd), &hdr);

    for( sl_list_t *n = hdr.nxt; n; n = n->nxt) {
        test_list *nd = SL_LIST_ENTRY(n, test_list, nd);
        std::cout << nd->value << std::endl;
    }

    assert( 3 == sllist_len(hdr.nxt));

    //test delete node operations
    delete_nd( &(third.nd), &hdr);
    assert( 2 == sllist_len(hdr.nxt));

    for( sl_list_t *n = hdr.nxt; n; n = n->nxt) {
        test_list *nd = SL_LIST_ENTRY(n, test_list, nd);
        std::cout << nd->value << std::endl;
    }


}
