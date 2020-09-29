#include <stdio.h>
#include <stdlib.h>
#include "../d_linked_list/dlist.h"

void list_info(DList* list) { printf("list size: \t%d\n", list->size); }

void insert_test(DList* list, int n, int q) {
     int a[n];
     for(int i = 1; i <= n; i++) a[i-1] = i;

     switch (q)  {
     case 4:
          for (int i = n-1; i >= 0; i--)
               dlist_ins_prev(list, list->tail, &a[i]);
          dlist_show(list);
          printf("\n");
     case 3:
          for (int i = n-1; i >= 0; i--)
               dlist_ins_prev(list, list->head, &a[i]);
          dlist_show(list);
          printf("\n");
          
     case 2:
          for (int i = 0; i < n; i++)
               dlist_ins_next(list, list->tail, &a[i]);
          dlist_show(list);
          printf("\n");
     case 1:
          for (int i = 0; i < n; i++)
               dlist_ins_next(list, list->head, &a[i]);
          dlist_show(list);
          printf("\n");
          break;
     default:
          break;
     }
     return;
}

void delete_test(DList* list, DListElmt* element) {
     void* data;
     
     while(!dlist_isempty(list))
          list_info(list), dlist_remove(list, element, (void**) &data);

     list_info(list);
     dlist_show(list);
     printf("\n");
     free(data);

     return;
}

int main(void) {
     //int (*max)(int, int) = ({ int __fn__ (int x, int y) { return x > y ? x : y; } __fn__; });
     //printf("%d\n", max(2,6));

     DList *list = dlist_init(
          ({
               void free_po(void *a) { return; } free_po;
          }),
          ({
               void show_number(void *n) {
                    if (n != NULL)
                         printf("%d ", *(int *)n);
               } show_number;
          })
     );
     
     
     insert_test(list, 2, 1);
     delete_test(list, list->tail);

     return EXIT_SUCCESS;
}
