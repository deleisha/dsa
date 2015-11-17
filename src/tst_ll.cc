#include "llist.h"
#include <iostream>

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

    insert(&(first.nd), &hdr);
    insert(&(second.nd), &hdr);

    test_list *nd = SL_LIST_ENTRY(hdr.nxt, test_list, nd);
    std::cout << "list value = " << nd->value << std::endl;
}
