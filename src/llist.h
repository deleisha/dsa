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

static inline void insert( sl_list_t *node, sl_list_t *list)
{
    if (!list) return;
    sllist__insert( node, list, list->nxt);
}

static inline void append(sl_list_t *node, sl_list_t *list)
{
    sl_list_t *prv = NULL;
    sl_list_t *t = NULL;
    SL_FOR_EACH (t, list) {
        prv = t;
    }
    sllist__insert(node, prv, prv->nxt);
}

static inline void delete_nd(sl_list_t *node, sl_list_t *list)
{
    sl_list_t *t = NULL;
    if ( !(node && list) ) return;

    SL_FOR_EACH(t, list) {
        if ( (t && t->nxt) && (t->nxt == node) ) {
            break;
        }
    }
    t->nxt = node->nxt;
}

static int sllist_len(sl_list_t *list)
{
    int count = 0;
    sl_list_t *tmp;

    if (!list) return count;

    SL_FOR_EACH(tmp, list) {
        ++count;
    }
    return count;
}

#ifdef __cplusplus
}
#endif

//
#endif
