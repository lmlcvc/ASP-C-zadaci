#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define PARENT(i) ((i-1) / 2)
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)

int is_max_heap(int *array, int len) {
    int i;

    for (i=len-1; i>0; i--) {
        if (array[i]>array[PARENT(i)]) {
            return 0;
        }
    }
    return 1;
}

int istrazi(int *heap, int n, int k, int x) {
    int vecih = 0;
    for(int i = 0; i < n; i++){
        if(heap[i] > x){
            vecih++;
        }
        if(vecih >= k) return 1;
    }

    return vecih >= k;
}

int main() {
    int menu_choice, i, num, len=0, k, x, *heap=NULL;
    char c;

    setbuf(stdout, NULL);
    do {
        /*DEBUG("\n1.Istrazi (istrazi)");
        DEBUG("\n2.Unos gomile\n3.Izlaz\n");*/
        scanf("%d", &menu_choice);
        switch(menu_choice) {
            case 1:
                do {
                    // DEBUG("\nUnesite k: ");
                    scanf("%d", &k);
                } while(k<1 || k>=len);
                // DEBUG("\nUnesite x: ");
                scanf("%d", &x);
                printf("%c\n", istrazi(heap, len, k, x) ? 'Y' : 'N');
                break;
            case 2:
                // DEBUG("\nUnesite broj elemenata gomile: ");
                scanf("%d", &len);
                if (heap) free(heap);
                heap = malloc(len*sizeof(int));
                for (i=0; i<len; i++) {
                    scanf("%d", &num);
                    heap[i] = num;
                }
                if (!is_max_heap(heap, len)) {
                    // DEBUG("\nUneseni niz nije max gomila.");
                    free(heap);
                    heap = NULL;
                }
                break;
            case 3:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=3);
    return 0;
}
