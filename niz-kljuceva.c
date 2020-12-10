#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

int niz_pretrazivanja(int *niz, int len) {
    int goal = niz[len - 1];
    int min = INT_MIN;
    int max = INT_MAX;

    for(int i = 0; i < len; i++){
        // desila se pogreška - izlazak iz granica
        if(niz[i] < min || niz[i] > max){
            return 0;
        }

        // postavljanje granica
        if(niz[i] <= goal){
            min = niz[i];
        } else{
            max = niz[i];
        }
    }

    return 1;
}

int main() {
    int menu_choice, i, num, len=0, *niz=NULL;
    char c;

    setbuf(stdout, NULL);
    do {
        DEBUG("\n1.Niz pretrazivanja (niz_pretrazivanja)");
        DEBUG("\n2.Unos niza\n3.Izlaz\n");
        scanf("%d", &menu_choice);
        switch(menu_choice) {
            case 1:
                printf("%c\n", niz_pretrazivanja(niz, len) ? 'Y' :'N');
                break;
            case 2:
                DEBUG("\nUnesite broj elemenata niza: ");
                scanf("%d", &len);
                DEBUG("\nUnesite elemente niza: ");
                if (niz) free(niz);
                niz = malloc(len*sizeof(int));
                for (i=0; i<len; i++) {
                    scanf("%d", &num);
                    niz[i] = num;
                }
                DEBUG("\nUneseni niz:\n");
                for (i=0; i<len; i++) {
                    DEBUG("%d ", niz[i]);
                }
                DEBUG("\n");
                break;
            case 3:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=3);
    return 0;
}
