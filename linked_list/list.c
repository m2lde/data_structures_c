#include<string.h>
#include<stdio.h>
#include "list.h"

/********************************************
 * Inicializa a lista apenas passando uma		*
 * funcao como parametro para apagar o tipo	*
 * especifico de dados que sera inserido na	*
 * lista.																		*
 ********************************************/
List *list_init(void (destroy)(void *data)) {
    List *list = (List*) malloc(sizeof(List));
		list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void show_list(List *list){
	ListElmt *e;
	for(e = list->tail; e != NULL; e = e->next){
		printf("%d\n", *((int*) e->data));
	}
}

/* ************************************************
 * Apaga elemento por elemento da lista.					*
 * Se foi passado NULL na inicializadao da lista,	*
 * sera usado a funcao free												*
 **************************************************/
void list_destroy(List *list) {
    void    *data;
    while (list_size(list) > 0)
        if (list_rem_next(list, NULL, (void **) &data) == 0 
						&& list->destroy != NULL)
				list->destroy(data);
    memset(list, 0, sizeof(List));
    return;
}

/************************************************** 
 * Insere um elemento logo apos o elemento				*
 * indicado como parametro.												*
 * Caso o ListElmt seja NULL sera criado um novo	*
 * elemento que sera colocado na cabeca da lista.	*
 **************************************************/
int list_ins_next(List *list, ListElmt *element, const void *data) {
    ListElmt *new_element;

    if ((new_element = (ListElmt*) malloc(sizeof(ListElmt))) == NULL)
        return -1;

    new_element->data = (void*) data;

    if(element == NULL) {  
			if (list_size(list) == 0) 
				list->tail = new_element;
			new_element->next = list->head;
			list->head = new_element;
    }
    else {
      if(element->next == NULL) 
				list->tail = new_element;
      new_element->next = element->next;
      element->next = new_element;
		}
		list->size++;
    return 0;
}

/******************************************************
 * Remove o elemento imediatamente apos o elemento		*
 * especificado.																			*
 * Se ListElmt for NULL sera removido elemento da			*
 * cabeca da lista.																		*
 ******************************************************/
int list_rem_next(List *list, ListElmt *element, void **data) {
    ListElmt        *old_element;

    if(list_size(list) == 0)
        return -1;

    if(element == NULL) {
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;
        if(list_size(list) == 0) list->tail = NULL;
    }

    else {
        if(element->next == NULL)
            return -1;

        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;

        if(element->next == NULL)
            list->tail = element;

        free(old_element);
        old_element = NULL;
    }

    list->size--;
    return 0;
}
