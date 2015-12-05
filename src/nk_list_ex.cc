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

bool is_circular(sl_list_t *list)
{
    sl_list_t *slow_ptr = list;
    sl_list_t *fast_ptr = list;
    for(; slow_ptr && fast_ptr && fast_ptr->nxt && fast_ptr->nxt->nxt;
           )
    {
        slow_ptr = slow_ptr->nxt;
        fast_ptr = fast_ptr->nxt->nxt;
        if ( slow_ptr == fast_ptr ) return true;
    }
    return false;
}

sl_list_t* find_loop_start(sl_list_t *list)
{
    sl_list_t *slow_ptr = list;
    sl_list_t *fast_ptr = list;
    bool is_circular = false;

    for(; slow_ptr && fast_ptr && fast_ptr->nxt && fast_ptr->nxt->nxt;)
    {
        slow_ptr = slow_ptr->nxt;
        fast_ptr = fast_ptr->nxt->nxt;
        if ( slow_ptr == fast_ptr ) {
            is_circular = true;
            break;
        }
    }

    if (is_circular) {
        for( fast_ptr = list; slow_ptr != fast_ptr; slow_ptr = slow_ptr->nxt, fast_ptr = fast_ptr->nxt) {
            ;
        }

        return slow_ptr;
    }
    return NULL;
}
int find_loop_len(sl_list_t *list)
{
    sl_list_t *slow_ptr = list;
    sl_list_t *fast_ptr = list;
    bool is_circular = false;

    for(; slow_ptr && fast_ptr && fast_ptr->nxt && fast_ptr->nxt->nxt;)
    {
        slow_ptr = slow_ptr->nxt;
        fast_ptr = fast_ptr->nxt->nxt;
        if ( slow_ptr == fast_ptr ) {
            is_circular = true;
            break;
        }
    }
    int cnt = 0;
    if (is_circular) {
        for( ;slow_ptr != fast_ptr; fast_ptr = fast_ptr->nxt)
        {
            ++cnt;
        }
    }
    return cnt;
}


void test_nth_from_end(sl_list_t hdr)
{
    my_list *t = nth_from_end(hdr.nxt, 5);
    std::cout << t->value << std::endl;

    t = nth_from_end(hdr.nxt, 1);
    std::cout << t->value << std::endl;

    t = nth_from_end(hdr.nxt, 15);
    assert( t == NULL);
}

#define ENABLE_DEBG 0
int main(int argc, char *argv[])
{
    SL_LIST_HD(hdr);
    for (int i = 0; i < ARRAY_SIZE(nodes); ++i) {
        insert(&(nodes[ARRAY_SIZE(nodes) - (i + 1)].nd) , &hdr);
    }

#if ENABLE_DEBG
    sl_list_t *ptr = NULL;
    SL_FOR_EACH(ptr, hdr.nxt) {
        my_list  *p = SL_LIST_ENTRY(ptr, my_list, nd);
        std::cout << p->value << std::endl;
    }
#endif
    test_nth_from_end( hdr);

    //test floyd algo
    nodes[9].nd.nxt = nodes[4].nd.nxt;

    assert(is_circular(hdr.nxt));

    nodes[9].nd.nxt = NULL;
    assert(!is_circular(hdr.nxt));
    nodes[9].nd.nxt = nodes[0].nd.nxt;
    assert(is_circular(hdr.nxt));
}
