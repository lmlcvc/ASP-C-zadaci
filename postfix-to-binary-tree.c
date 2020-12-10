#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXS 1000


typedef struct node{ 
  char val; 
  struct node *left; 
  struct node *right; 
} tree;


typedef struct {
  tree *arr[MAXS];
  int top;
} stack;



/*stack *stack_ctor(int size) {
  stack *s = malloc(sizeof(stack));
  s->top = -1;
  s->arr = malloc(size*sizeof(int));
  return s;
}*/

void stack_dtor(stack *s) {
  free(s->arr);
  free(s);
}

int stack_is_empty(stack *s) {
  return s->top==-1;
}

void stack_push(stack *s, tree *t) {
  s->arr[++(s->top)] = t;
}

tree *stack_pop(stack *s) {
  if (stack_is_empty(s)) return NULL;
  tree *tmp = s->arr[s->top];
  s->top--;
  return tmp;

}

tree *make_tree(char c, tree *ch1, tree *ch2){
	tree *p;
	p->val = c;
	p->left = ch1;
	p->right = ch2;

	return p;
}


int main() {
  char c; // simbol koji će biti pročitan
  stack s; // stog sa pokazivačima na stabla

  do{
  	scanf("%c", &c);

  	// ako je operand stvori stablo
  	// i stavi pokazivač u stog
  	if(isdigit(c) || isalpha(c)){
  		tree *tmp = make_tree(c, NULL, NULL);
  		stack_push(&s, tmp);
  	} else{
  	// ako je operator, pop-uj 2 pokazivača
  	// i stvori novo stablo koje u korijenu
  	// ima operator, a u djeci ta dva stabla
  	// push novi pokazivač na stablo
  		tree *tmp1 = stack_pop(&s);
  		tree *tmp2 = stack_pop(&s);
  		tree *new = make_tree(c, tmp1, tmp2);
  		stack_push(&s, new);
  	}
  } while(c != '\n');

  stack_dtor(&s);
}

