#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

typedef struct Node {
    int val;
    struct Node *next;
} node;

node *scan_list() {
    node *head=NULL, *prethodni=NULL, *novi=NULL;
    char c;
    int val;

    while (scanf(" %d", &val)==1) {
        if (prethodni && prethodni->val > val) {
            DEBUG("\nListe moraju biti uzlazno sortirane: %d > %d, zanemarujem %d i nastavljam\n", prethodni->val, val, val);
            continue;
        }
        novi = (node*)malloc(sizeof(node));
        novi->val = val;
        novi->next = NULL;
        if (prethodni) {
            prethodni->next = novi;
            prethodni = novi;
        } else {
            head = prethodni = novi;
        }
    }
    while((c=getchar())!='\n' && c!=EOF);
    return head;
}

int print_list(node *head) {
    node *trenutni;

    if (!head) return -1;
    for (trenutni=head; trenutni!=NULL; trenutni=trenutni->next) {
        printf("%d ", trenutni->val);
    }
    printf("\n");
    return 0;
}

node *spoji_sortirane_liste(node *head_prva, node *head_druga) {
    // slučajevi s praznim listama
    // prazne su obje
    if(!head_prva && head_druga) return NULL;
    // prazna je samo jedna pa se odmah vraća ona druga
    if(!head_prva) return head_druga;
    if(!head_druga) return head_prva;

    // spaja liste tako da krene od manjeg head-a
    // onda za svaki idući uzima manju od 2 moguće vrijednosti:
    // next iz prve i next iz druge liste

    // postavljanje glave na vrijednost one manje od dvaju poslanih
    node *head = (head_prva->val < head_druga->val ? head_prva : head_druga);

    // trenutni postavljamo na prvi iza glave
    node *t = malloc(sizeof(node));
    t->next = NULL;
    head->next = t;

    // prethodni postavljamo na glavu
    node *p = head;

    node *t1 = head_prva, *t2 = head_druga;

    // kretanje do kraja obaju listi
    while(t1 != NULL || t2 != NULL){
        // ako je oba postoje, ali je manji t1 ili uopće nema t2
        if((t1 && t2 && (t1->val < t2->val))
            || !t2){
            t->val = t1->val;
            p->next = t;
            t->next = NULL;
            t1 = t1->next;
        }
        // isto kao prije samo za t2 + s uvjetom za ==
        else if((t1 && t2 && (t1->val > t2->val))
            || !t1
            || t1->val == t2->val){
            t->val = t2->val;
            p->next = t;
            t->next = NULL;
            t2 = t2->next;
        }
    }

    return head;
}

int main() {
    node *head_spojena=NULL, *head_prva=NULL, *head_druga=NULL;
    int menu_choice;
    char c;

    setbuf(stdout, NULL);
    do {
        menu_choice = 0;
        //DEBUG("\n1 spoji sortirane liste (spoji_sortirane_liste)");
        //DEBUG("\n2 Ispis\n3 Unesi liste ( kao niz cijelih brojeva u uzlaznom redoslijedu odvojenih razmacima sve do pojave prvog nenumerickog znaka)\n4 Izlaz\n");
        scanf("%d", &menu_choice);
        switch (menu_choice) {
            case 1:
                head_spojena = spoji_sortirane_liste(head_prva, head_druga);
                break;
            case 2:
                print_list(head_spojena);
                break;
            case 3:
                //DEBUG("Unesite prvu listu: ");
                head_prva = scan_list();
                //DEBUG("Unesite drugu listu: ");
                head_druga = scan_list();
                break;
            case 4:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=4);
    return 0;
}
