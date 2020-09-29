#include <string.h>
#include "dlist.h"

DList *dlist_init(void (*destroy)(void *data), void (*show_elmt)(void *data)) {
    DList *list = (DList *)malloc(sizeof(DList));
    list->size = 0;
    list->destroy = destroy;
    list->show_elmt = show_elmt;
    list->head = dlist_elmt_init(NULL, NULL, NULL);
    list->tail = dlist_elmt_init(NULL, list->head, NULL);
    list->head->next = list->tail;
    return list;
}

DListElmt *dlist_elmt_init(DListElmt *next, DListElmt *prev, void *data) {
    DListElmt *elmt;
    if ((elmt = (DListElmt *)calloc(1, sizeof(DListElmt))) == NULL)
        return NULL;
    elmt->next = next;
    elmt->prev = prev;
    elmt->data = data;
    return elmt;
}

void dlist_destroy(DList *list) {
    void *data;

    while (!dlist_isempty(list))
        if (dlist_remove(list, dlist_tail(list), (void **) &data) == 0 && list->destroy != NULL)
            list->destroy(data);

    return;
}

int dlist_set_elmt(DList *list, DListElmt *element, const void *data) {
    if (element == NULL && dlist_size(list) != 0)
        return -1;

    if(element == list->head)
        list->head->next->data = (void*) data;
    else if( element == list->tail)
        list->tail->prev->data = (void*) data;
    else
        element->data = (void *) data;
    return 1;
}

int dlist_ins_between(DList*list, DListElmt *a, DListElmt *b, const void* data) {
    if( ((a  == NULL || b == NULL) && dlist_size(list) != 0))
        return -1;

    DListElmt *new_element;
    if ((new_element = dlist_elmt_init(b, a, (void *) data)) == NULL)
        return -1;

    a->next = new_element;
    b->prev = new_element;
    return 1;
}

int dlist_del_between(DList*list, DListElmt *a, DListElmt *b) {
    if( ((a  == NULL || b == NULL) && dlist_size(list) != 0))
        return -1;

    DListElmt* tmp = a->next;
    tmp->next = tmp->prev = NULL;
    list->destroy(tmp->data);
    free(tmp);

    a->next = b;
    b->prev = a;
    return 1;
}

int dlist_ins_next(DList *list, DListElmt *element, const void *data) {
    if (element == NULL && dlist_size(list) != 0)
        return -1;

    DListElmt *new_element;
    if ((new_element = dlist_elmt_init(NULL, NULL, (void *) data)) == NULL)
        return -1;
    
    if(dlist_isempty(list)) 
        dlist_ins_between(list, list->head, list->tail, data);
     else if(element == list->tail) 
        dlist_ins_between(list, list->tail->prev, list->tail, data);
     else if(element == list->head) 
        dlist_ins_between(list, list->head->next, list->head->next->next, data);
     else  
        dlist_ins_between(list, element, element->next, data);
    
    list->size++;
    return 0;
}

int dlist_ins_prev(DList *list, DListElmt *element, const void *data) {
    if (element == NULL && dlist_size(list) != 0)
        return -1;

    DListElmt *new_element;
    if ((new_element = dlist_elmt_init(NULL, NULL, (void *)data)) == NULL)
        return -1;

    if(dlist_isempty(list)) 
        dlist_ins_between(list, list->head, list->tail, data);
    else if(element == list->head) 
        dlist_ins_between(list, list->head, list->head->next, data);
     else if(element == list->tail) 
        dlist_ins_between(list, list->tail->prev->prev, list->tail->prev, data);
     else 
        dlist_ins_between(list, element->prev, element, data);

    list->size++;
    return 0;
}

int dlist_remove(DList * list, DListElmt * element, void **data) {
    if(element == NULL || dlist_isempty(list))
        return -1;

    *data = element->data;

    if(element == list->head) 
        element=list->head->next;
    if(element == list->tail) 
        element=list->tail->prev;
        
    dlist_del_between(list, element->prev, element->next);

    list->size--;
    return 0;
}

void dlist_show(DList * list) {
    for (DListElmt *i = list->head->next; i->next != NULL; i = i->next)
        list->show_elmt(i->data);
    return;
}

