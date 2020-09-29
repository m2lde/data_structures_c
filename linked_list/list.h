/************************
 * 	        list.h		  *
 ************************/

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct ListElmt ListElmt;
typedef struct List List;

struct ListElmt {
    void               *data;
    struct ListElmt    *next;
};

struct List {
    int     size;
    int     (*match)(const void*, const void*);
    void    (*destroy)(void *data);
    ListElmt *head;
    ListElmt *tail;
};



List *list_init(void (destroy)(void *data));

void show_list(List*);

void list_destroy(List*);

int list_ins_next(List*, ListElmt*, const void*);

int list_rem_next(List*, ListElmt*, void**);

#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)

#define list_is_tail(list, element) ((element)->next == NULL ? 1 : 0)

#define list_data(element) ((element)->data)

#define list_next(element) ((element)->next)

#endif
