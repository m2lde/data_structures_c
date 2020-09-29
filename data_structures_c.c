
/*
 * File:   data_structures_c.c
 * Author: murilo
 *
 * Created on August 3, 2016, 8:34 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list/list.h"

int main(void) {
	List *list = list_init(free);
	int i;
	
	for(i = 1; i <= 10; i++){ 
		printf("%d ", list_ins_next(list, NULL, (void*) &i));
	}

	printf("%d\n", *((int*) list->tail->data));

	return EXIT_SUCCESS;
}
