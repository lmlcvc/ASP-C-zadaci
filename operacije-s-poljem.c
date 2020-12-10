#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define SIZE 10


struct stack_s {
    int array[SIZE];
    int tops[2];
} stack_init = { .tops={-1, SIZE} };
typedef struct stack_s stack_t;



int push(stack_t *stack, int stack_nr, int val) {
    // nedozvoljeni broj stoga
    if(stack_nr != 1 && stack_nr != 2) return -2;

    // stog je pun
    if(stack->tops[0] + 1 == stack->tops[1]) return -1;
    // ^ zašto nije stack->tops[0] == stack->tops[1]
    // ili u biti stack->tops[0] + stack->tops[1] == SIZE - 1

    // koristimo stack_nr kao indeks polja tops
    stack_nr--;
    // prvom topu se dodaje, a drugom oduzima 1 
        // želim proanalizirati zašto se drugi stog kreće obrnuto
    stack->tops[stack_nr] += (stack_nr == 0 ? 1 : -1);
    // u polje na top postavljamo val
    stack->array[stack->tops[stack_nr]] = val;

    return 0;
}



int pop(stack_t *stack, int stack_nr) {
    // nedozvoljeni broj stoga
    if(stack_nr != 1 && stack_nr != 2) return -2;

    // stog je prazan
    // provjera zavisno o broju stoga
    if(stack_nr == 1 && stack->tops[0] == -1) return -1;
    if(stack_nr == 2 && stack->tops[1] == SIZE) return -1;

    // brisanje pomicanjem topa, obrnuto od push funkcije
    stack_nr--;
    stack->tops[stack_nr] += (stack_nr == 0 ? -1 : 1);

    return 0;
}



void print(stack_t stack, int stack_nr) {
    // nevaljani broj stoga
    if(stack_nr != 1 && stack_nr != 2) return;

    // ispis po ključu broja stoga
    // stack_nr--;
    printf("Stog: ");
    if(stack_nr == 1){
        for(int i = 0; i <= stack.tops[0]; i++){
            printf("%d ", stack.array[i]);
        }
    } else{
        for(int i = SIZE-1; i >= stack.tops[1]; i--){
            printf("%d ", stack.array[i]);
        }
    }
    printf("\n");
}



int main() {
    char menu_choice;
    stack_t stack = stack_init;
    int val, retval, stack_nr;

    DEBUG("\n(d) dodaj - push\n(b) brisi - pop\n(i) ispis - print\n(e) Exit\n");
    do {
        scanf(" %c", &menu_choice);
        switch (menu_choice) {
            case 'd':
                scanf("%d", &stack_nr);
                scanf("%d", &val);
                retval = push(&stack, stack_nr, val);
                if (retval==-1) {
                    printf("Stog je %d pun. Ne mogu dodati element.\n", stack_nr);
                } else if (retval==-2) {
                    printf("Stog je %d ne postoji.\n", stack_nr);
                }
                break;
            case 'b':
                scanf("%d", &stack_nr);
                retval = pop(&stack, stack_nr);
                if (retval==-1) {
                    printf("Stog je %d prazan. Ne mogu obrisati element.\n", stack_nr);
                } else if (retval==-2) {
                    printf("Stog je %d ne postoji.\n", stack_nr);
                }
                break;
            case 'i':
                scanf("%d", &stack_nr);
                print(stack, stack_nr);
                break;
        }
    } while (menu_choice!='e');
    return 0;
}
