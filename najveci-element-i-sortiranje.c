#include<stdio.h>
#include<stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAX_SIZE 10

int max_rec(int *polje, int N) {
    int index;

    // osnovni slučaj - zadnji element (osim polje[0])
    if(N == 1) return 0;

    // napredak
    // pobrojati iteracije da dobijemo indekse
    index = max_rec(polje + 1, N - 1) + 1;

    return polje[0] > polje[index] ? 0 : index;
}

void sort_rec(int *polje, int N) {
    int max_index, tmp;

    // osnovni slučaj
    if(N == 1) return;

    // napredak
    max_index = max_rec(polje, N);

    tmp = polje[max_index];
    polje[max_index] = polje[0];
    polje[0] = tmp;

    sort_rec(polje + 1, N - 1);
}

void print_array(int array[], int size) {
    int i;

    for (i=0; i<size; i++) printf ("%d ",array[i]);
    printf("\n");
}

int main() {
    int array[MAX_SIZE];
    int i = 0;

    for (i=0; i<MAX_SIZE; i++) {
        scanf("%d", array+i);
    }
    printf("%d\n", max_rec(array, MAX_SIZE));
    sort_rec(array, MAX_SIZE);
    print_array(array, MAX_SIZE);
    return 0;
}
