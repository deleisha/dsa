#ifndef LLIST_H
#define LLIST_H
//
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct sllist_s {
    struct sllist_s *nxt;
} sl_list_t;

#define SL_LIST_HD(hdr)    \
  sl_list_t  hdr = { (NULL) }

#define SL_LIST_ENTRY(ptr, type, member)   \
  (type*)((char*)ptr - offsetof(type, member))

#define SL_FOR_EACH(pos, list)      \
  for( (pos) = list; (pos); (pos) = (pos)->nxt)


static inline void sllist__insert(sl_list_t *nd, sl_list_t *prv, sl_list_t *nxt)
{
    prv->nxt = nd;
    nd->nxt = nxt;
}

static inline void sllist_insert( sl_list_t *node, int pos, sl_list_t *list)
{
    sl_list_t *prev = NULL;
    sl_list_t *nxt = NULL;
    sl_list_t *itr = NULL;
    int i = 1;
    
    if (!list) return;
    if ( pos == 1) {
        prev = list;
        nxt = list->nxt;
    }
    else {
        for( itr = list; (itr && i < pos); itr = itr->nxt) {
            ++i;
        }
        prev = itr;
        nxt = itr->nxt;
    }
    sllist__insert( node, prev, nxt);
}

static inline void sllist_del_node(sl_list_t *node, int pos, sl_list_t *list)
{
}

int sllist_len(sl_list_t *list)
{
    int count = 0;
    sl_list_t *tmp;

    if (!list) return count;

    SL_FOR_EACH(tmp, list) {
        ++count;
    }
    return count;
}
//static inline void remove(

#ifdef __cplusplus
}
#endif

//
#endif
