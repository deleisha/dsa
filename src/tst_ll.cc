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

    insert(&(first.nd), &hdr);



    std::cout << "list header created" << std::endl;
}
