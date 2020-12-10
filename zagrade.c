#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXS 10001



// stog koji sprema podatak o topu te otvorene zagrade
typedef struct {
  int top;
  char *arr;
} stack;


stack *create_stack(int size){
	stack *s = malloc(sizeof(stack));
	s->top = -1;
	s->arr = malloc(sizeof(int) * (size + 1));
	return s;
}


void push(stack *s, char val){
	s->top++;
	s->arr[s->top] = val;
}


void pop(stack *s){
	if(s->top == -1) return;
	s->top--;
}


void stack_dtor(stack *s) {
  free(s->arr);
  free(s);
}



int main(){
	// polje otvorenih zagrada
	char z[2] = "([";
	// broj upita
	int n;
	// stog
	stack *s = create_stack(MAXS);
	// niz koji ćemo unesti
	char *str = malloc((MAXS+1)*sizeof(char));


	scanf("%d\n", &n);

	for(int i = 0; i < n; i++){
		// da li je niz ispravan, pretpostavljamo da je
		int valid = 1;

		scanf("%s", str);

		for(int j = 0; j < strlen(str); j++){

			// otvorene zagrade stavljamo na stog
			if(str[j] == '(' || str[j] == '['){
				push(s, str[j]);

			} else if(valid && s->top != -1 && s->arr[s->top] == z[str[j] == ']']){
				// zatvorene zagrade provjeravamo sa otvorenim
				// niz mora biti ispravan i neprazan
				// ako to vrijedi, skidamo zadnju zagradu sa stoga

				pop(s);

			} else{
				valid = 0;
				pop;
			}
		}

		// došli smo do kraja niza, provjeravamo uvjete
		if(valid && s->top == -1){
			printf("YES\n");
		} else{
			printf("NO\n");
		}

		s->top = -1;
	}

	// oslobađanje stoga i stringa

	/*
	OVO NE RADI i javlja prekoračenje vremenskog limita: 
	---> odgovor: ne radi jer memorija inicijalno nije bila 
	dinamički alocirana...
	*/
	free(s->arr);
	free(s);
	free(str);

	/* 
	NE RADI NI OVO, javlja korištenje nedozvoljene f-je:
	warning: attempt to free a non-heap object ‘str’
	---> isto nedinamička memorija jaoo
	stack_dtor(s);
	free(str);
	*/


	/* AAAAAAA ZAŠTO JOŠ UVIJEK,
	I SA DINAMIČKI ALOCIRANOM MEMORIJOM, JAVLJA
	PREKORAČENJE VREMENSKOG LIMITA??*/

	return 0;
}
