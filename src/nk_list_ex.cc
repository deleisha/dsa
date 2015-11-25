#include "llist.h"
#include <iostream>
#include <cassert>

typedef struct my_list {
    int value;
    sl_list_t nd;
} my_list;

//shabby way of creating node
static my_list nodes[] = {
     {10, 0}
    ,{20, 0}
    ,{30, 0}
    ,{40, 0}
    ,{50, 0}
    ,{60, 0}
    ,{70, 0}
    ,{80, 0}
    ,{90, 0}
    ,{100, 0}
};

#define ARRAY_SIZE(array) sizeof(array)/sizeof(array[0])

my_list* nth_from_end(sl_list_t *list, const int n)
{
    sl_list_t *rptr = NULL;
    sl_list_t *itr = list;
    assert( n > 0);
    for( int i = 0; i < n; ++i) {
        if (!itr) {
            std::cerr << "Either empty or list lesser than " << n
                << " passed" << std::endl;
            return NULL;
        }
        assert(itr != NULL);
        itr = itr->nxt;

    }
    for(rptr = list; itr; itr = itr->nxt)
    {
        rptr = rptr->nxt;
    }
    return SL_LIST_ENTRY(rptr, my_list, nd);
}

int main(int argc, char *argv[])
{
    SL_LIST_HD(hdr);
    for (int i = 0; i < ARRAY_SIZE(nodes); ++i) {
        insert(&(nodes[ARRAY_SIZE(nodes) - (i + 1)].nd) , &hdr);
    }

    sl_list_t *ptr = NULL;
    SL_FOR_EACH(ptr, hdr.nxt) {
        my_list  *p = SL_LIST_ENTRY(ptr, my_list, nd);
        std::cout << p->value << std::endl;
    }

    my_list *t = nth_from_end(hdr.nxt, 5);
    std::cout << t->value << std::endl;

    t = nth_from_end(hdr.nxt, 1);
    std::cout << t->value << std::endl;

    t = nth_from_end(hdr.nxt, 15);
    assert( t == NULL);
}
