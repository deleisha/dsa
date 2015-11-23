#include "llist.h"
#include <iostream>
#include <cassert>

typedef struct my_list {
    int value;
    sl_list_t nd;
} test_list;

int main(int argc, char *argv[])
{
    SL_LIST_HD(hdr);

    test_list element[] = {
        { .value = 10, .nd = { .nxt = NULL }},
        { .value = 20, .nd = { .nxt = NULL }},
        { .value = 30, .nd = { .nxt = NULL }}
    };

    //test adding node
    insert(&(element[0].nd), &hdr);
    append(&(element[1].nd), &hdr);
    append(&(element[2].nd), &hdr);

    //test traversing
    int i = 0;
    for( sl_list_t *n = hdr.nxt; n; n = n->nxt) {
        test_list *nd = SL_LIST_ENTRY(n, test_list, nd);
        assert( nd == &(element[i]));
        ++i;
    }

    assert( 3 == sllist_len(hdr.nxt));

    //test delete node operations
    delete_nd( &(element[2].nd), &hdr);
    assert( 2 == sllist_len(hdr.nxt));

    insert(&(element[2].nd), &hdr);
    assert( 3 == sllist_len(hdr.nxt));

    delete_nd( &(element[0].nd), &hdr);
    assert( 2 == sllist_len(hdr.nxt));

    std::cout << "Test: " << argv[0] << ": +++++++ passed +++++++" << std::endl;
}
