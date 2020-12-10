#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXS 1000001

typedef struct {
  int top;
  int *arr;
  // int max;
} stack;

stack *stack_ctor(int size) {
  stack *s = malloc(sizeof(stack));
  s->top = -1;
  s->arr = malloc(size*sizeof(int));
  // max = -1;
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

  // provjera
}

void stack_clear(stack *s) {
  s->top = -1;
}


int main() {
  int n;
  char *op = malloc(6*sizeof(char));
  stack *s = stack_ctor(MAXS);
  // stog u koji ćemo pohranjivati maksimume
  stack *maximums = stack_ctor(MAXS);

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf(" %s", op);
    if (strcmp(op, "push")==0) {
      int x;
      scanf(" %d", &x);

      /* ne bi bilo dobro izbjegavati dodavanje elementa
      sa vrednošću koja je već u stogu
      jer bi to poremetilo maksimume kod pop-anja
      npr if(stack_is_empty(s) || x != s->arr[s->top]){*/


      // to sam riješila tako da u sljedećoj f-ji stavim >=

      
      // ako je uneseni x veći od trenutnog max-a
      // (ukoliko uopće postoji), trebamo ga dodati u polje maksimuma
      if(stack_is_empty(s) || x >= maximums->arr[maximums->top]){
        stack_push(maximums, x);
      } 

      stack_push(s, x);

    } else if (strcmp(op, "pop")==0) {

      // ako je element kojeg mičemo trenutni max
      if(!stack_is_empty(s) && s->arr[s->top] == maximums->arr[maximums->top]){
        stack_pop(maximums);
      }

      stack_pop(s);
    } else if (strcmp(op, "max")==0) {
      // ako je stog prazan, ispisuje se -
      if(stack_is_empty(s)){
        printf("-\n");
      } else{
        printf("%d\n", maximums->arr[maximums->top]);
      }
    }
  }

  stack_dtor(s);
  free(op);
  return 0;
}
