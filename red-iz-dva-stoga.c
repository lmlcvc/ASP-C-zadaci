#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXS 1000

typedef struct {
  int top;
  int *arr;
} stack;



stack *stack_ctor(int size) {
  stack *s = malloc(sizeof(stack));
  s->top = -1;
  s->arr = malloc(size*sizeof(int));
  return s;
}



void stack_dtor(stack *s) {
  free(s->arr);
  free(s);
}



int stack_is_empty(stack *s) {
  return s->top==-1;
}



void stack_push(stack *s, int val) {
  s->arr[++(s->top)] = val;
}



void stack_pop(stack *s) {
  if (stack_is_empty(s)) return;
  s->top--;
}



void stack_clear(stack *s) {
  s->top = -1;
}


void stack_copy(stack *s1, stack *s2) {
  while(!stack_is_empty(s1)) {
    stack_push(s2, s1->arr[s1->top]);
    stack_pop(s1);
  }
}


void print_head(stack *s1, stack *s2) {
  if (stack_is_empty(s2)) stack_copy(s1, s2);
  if (stack_is_empty(s2)) printf("buffering\n");
  else printf("%d\n", s2->arr[s2->top]);
}


/*void print_head(stack *s1, stack *s2) {
  if(stack_is_empty(s1) && stack_is_empty(s2)) printf("buffering\n");

  if(stack_is_empty(s2)) stack_copy(s1, s2);
  printf("%d\n", s2->arr[s2->top]);
}*/



void enqueue(stack *s1, stack *s2, int val) {
  stack_push(s1, val);
  // stack_push(s2, val);
}



void dequeue(stack *s1, stack *s2) {
  if (stack_is_empty(s2)) stack_copy(s1, s2);
  if (stack_is_empty(s2)) return;
  stack_pop(s2);
}




int main() {
  int n;
  stack *s1 = stack_ctor(MAXS);
  stack *s2 = stack_ctor(MAXS);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    char op;
    scanf(" %c", &op);
    if (op=='e') {
      int x;
      scanf(" %d", &x);
      enqueue(s1, s2, x);
    } else {
      print_head(s1, s2);
      dequeue(s1, s2);
    }
  }
  stack_dtor(s1);
  stack_dtor(s2);
  return 0;
}
