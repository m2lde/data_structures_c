#include <stdlib.h>
#include "../linked_list/list.h"
#include "stack.h"


int stack_push(Stack *stack, const void *data) {
    return list_ins_next(stack, NULL, data);
}

int stack_pop(Stack *stack, void **data){
    list_rem_next(stack, NULL, data);
}