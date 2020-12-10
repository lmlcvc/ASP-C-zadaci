#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif



typedef struct Node {
  int val;
  struct Node *next;
  struct Node *prev;
} node;



typedef struct {
  node *head;
  node *mid;
  node *end;
  int size;
} stacks;



stacks *create_stack(){
    stacks *t = malloc(sizeof(stacks));
    t->head = NULL;
    t->mid = NULL;
    t->end = NULL;
    t->size = 0;
    return t;
}


void swapn(node **x, node **y){
	node *tmp = *x;
	*x = *y;
	*y = tmp;
}


void add_node(stacks *stack, int val){
    // postavljanje novog čvora
    node *newn = malloc(sizeof(node));
    newn->val = val;
    newn->next = newn->prev = NULL;

    // postavljanje novog čvora na kraj
    if(stack->end) stack->end->next = newn;
    newn->prev = stack->end;
    stack->end = newn;
    stack->size++;

    // situacija da je to jedini element u nizu
    if(stack->size == 1){
        stack->head = stack->end;
    }
    // situacija da imamo 2 elementa u nizu
    // onda se sredina gleda kao head
    // ^ podiskutirati
    else if(stack->size == 2){
        stack->mid = stack->head;
    }
    // situacija gdje polje ima neki veći parni broj elemenata
    // sredina je uvijek onaj "lijevi"
    else if(stack->size > 3 && stack->size % 2 == 0){
    	stack->mid = stack->mid->next;
    }
}


void delete_node(stacks *stack){
	// prazan stog
	if(!stack->head) return;

	if(stack->end->prev){
		stack->end->prev->next = NULL;
	}

	node *tmp = stack->end;
	stack->end = stack->end->prev;
	free(tmp);
	stack->size -= 1;

	// provjere sredine poslijesmanjivanja
		// samo 1 element
	if(stack->size == 1) stack->mid = NULL;
		// neparan broj elemenata
	else if(stack->size % 2) stack->mid = stack->mid->prev;
		// potpuno prazan stog
	if(stack->size == 0){
		stack->head = NULL;
		stack->end = NULL;
	}
}


void permute(stacks *stack){
	// nemoguće napraviti premutaciju
	if(stack->size == 0 || stack->size == 1) return;

	// razne zamjene
	stack->end->next = stack->head;
	stack->head->prev = stack->end;
	stack->head = stack->mid->next;
	stack->mid->prev = NULL;
	stack->mid->next = NULL;

	// zamjena kraja i sredine
	swapn(&stack->end, &stack->mid);

	// neparan broj elemenata
	if(stack->size % 2 == 1){
		stack->mid = stack->mid->prev;
	}
}




int main() {
    char menu_choice;
    int val;
    int n;
    stacks *stack = create_stack();

    scanf("%d\n", &n);

    for(int i = 0; i < n; i++){
        scanf(" %c", &menu_choice);
        switch (menu_choice) {
            case 'd':
                scanf("%d", &val);
                add_node(stack, val);
                break;
            case 'o':
                scanf("%d", &val);
                delete_node(stack);
                break;
            case 'p':
                permute(stack);
                break;
        }
    }

    printf("%d\n", stack->size);
    for(node *t = stack->head; t != NULL; t = t->next){
        printf("%d ", t->val);
    }
    free(stack);

    return 0;
}