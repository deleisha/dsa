#ifndef LLIST_H
#define LLIST_H
//
#ifdef __cplusplus
extern "C" {
#endif

typedef struct sllist_s {
    struct sllist_s *nxt;
} sl_list_t;

#define SL_LIST_HD(hdr)                                                       \
  sl_list_t  hdr = { .nxt = NULL }


static inline void sllist__insert(sl_list_t *nd, sl_list_t *prv, sl_list_t *nxt)
{
    prv->nxt = nd;
    nd->nxt = nxt;
}

static inline void insert( sl_list_t *node, sl_list_t *list)
{
    sllist__insert( node, list, list->nxt);
}
//static inline void remove(

#ifdef __cplusplus
}
#endif

//
#endif
