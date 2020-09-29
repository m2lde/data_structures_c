/*******************
*      dlist.h     *
********************/

#ifndef DLIST_H
#define	DLIST_H

#include <stdlib.h>

typedef struct DListElmt_ {
    void *data;
    struct DListElmt_ *next;
    struct DListElmt_ *prev;
} DListElmt;

typedef struct DList_ {
    int     size;
    int     (*match)(const void *key1, const void *key2);
    void    (*destroy)(void *data);
    void    (*show_elmt)(void *data);
    
    DListElmt *head;
    DListElmt *tail;
} DList;

DListElmt *dlist_elmt_init(DListElmt* next, DListElmt* prev, void* data);
//Prototypes.
DList *dlist_init(void (*)(void*), void(*)(void*));

void dlist_destroy(DList *list);

int dlist_set_elmt(DList *list, DListElmt *element, const void *data);

int dlist_ins_next(DList *list, DListElmt *element, const void *data);

int dlist_ins_prev(DList *list, DListElmt *element, const void *data);

int dlist_remove(DList *list, DListElmt *element, void **data);

void dlist_show(DList *list);

//Macros.
#define dlist_size(list) ((list)->size)

#define dlist_tail(list) ((list)->tail)

#define dlist_head(list) ((list)->head)

#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)

#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)

#define dlist_data(element) ((element)->data)

#define dlist_next(element) ((element)->next)

#define dlist_prev(element) ((element)->prev)

#define dlist_isempty(list) (((list)->size) == 0 ? 1 : 0)

#endif	/* DLIST_H */

