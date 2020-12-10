#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXS 1000001


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



int main() {
	int n;
	stack *s = stack_ctor(MAXS);
	// char operand;//int a, b;
	int res = 0;

	scanf("%d\n", &n);

	for(int i = 0; i < n; i++){
		char val;
		scanf("%c ", &val);

		// brojeve unesti u stog
		if(val >= '0' && val <= '9'){
			stack_push(s, (val - '0'));
		} else{
		// s operandima izvršiti operaciju
		// vrši se nad zadnjim i predzadnjim elementom stoga

			int a, b;

			a = s->arr[s->top];
			stack_pop(s);
			b = s->arr[s->top];
			stack_pop(s);

			if(val == '+'){
				res = a + b;
			} else if(val == '-'){
				res = b - a;
			} else if(val == '*'){
				res = a * b;
			} 

		// novi rezultat stavljamo na vrh stoga
			stack_push(s, res);
		}
	}

	printf("%d\n", res);
	stack_dtor(s);
}