#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAX_TREE_STRING 100
#define MAX_NODES 100
// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 6

typedef struct node {
    char val;
    struct node *left;
    struct node *right;
} Node;

int broj_cvorova (Node *node) {
    // osnovni slučaj
    if(node == NULL) return 0;

    // napredak
    return broj_cvorova(node->left) + broj_cvorova(node->right) + 1;
}


char najveci_element(Node *node) {
    // nema root = stablo je prazno
    if(node == NULL) return 0;

    char left_max = najveci_element(node->left);
    char right_max = najveci_element(node->right);

    // usporediti trenutnu i max vrijednost
    char max = left_max > right_max ? left_max : right_max;
    if(node->val > max){
        max = node->val;
    }

    return max;
}


char najmanji_element(Node *node) {
    // nema root = stablo je prazno
    if(node == NULL) return 127;

    char left_min = najmanji_element(node->left);
    char right_min = najmanji_element(node->right);

    // usporediti trenutnu i min vrijednost
    char min = left_min < right_min ? left_min : right_min;
    if(node->val < min){
        min = node->val;
    }

    return min;
}


void zrcalno_stablo(Node *node) {
    // osnovni uvjet
    if(node == NULL) return;

    // napredak
    // zamijeniti lijevi i desni
    Node *tmp = node->left;
    node->left = node->right;
    node->right = tmp;

    // nastaviti na podstablima
    zrcalno_stablo(node->left);
    zrcalno_stablo(node->right);
}


int identicna(Node *n1, Node *n2) {
    // da li su na istoj poziciji isti elementi

    // osnovni slučaj
    // do kraja
    if(n1 == NULL && n2 == NULL) return 1;
    // nisu isti
    if(n1 == NULL || n2 == NULL) return 0;
    // optimizacija: if(n1 == NULL || n2 == NULL) return n1 == n2;

    // napredak
    return (n1->val == n2->val && identicna(n1->left, n2->left) && identicna(n1->right, n2->right));
}

int sprint_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    char b[HEIGHT];
    int i, left, right, width = 5;

    if (!tree) return 0;
    sprintf(b, "( %c )", tree->val);
    left = sprint_tree(tree->left, 1, offset, depth+1, s);
    right = sprint_tree(tree->right, 0, offset+left+width, depth+1, s);
    for (i=0; i<width; i++)
        s[depth][offset+left+i] = b[i];
    if (depth) {
        if (is_left) {
            for (i=0; i<width+right; i++)
                s[depth-1][offset+left+width/2+i] = '-';
        } else {
            for (i=0; i<left+width; i++)
                s[depth-1][offset-width/2+i] = '-';
        }
        s[depth-1][offset+left+width/2] = '.';
    }
    return left+width+right;
}

void ispisi_stablo(Node *root) {
    char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
    int i;
    sprintf(print_format, "%%%ds", WIDTH-1);
    for (i=0; i<HEIGHT; i++)
        sprintf(s[i], print_format, " ");

    sprint_tree(root, 0, 0, 0, s);

    sprintf(empty_line, print_format, " ");
    for (i=0; i<HEIGHT; i++) {
        if (strcmp(s[i],empty_line))
            printf("%s\n", s[i]);
    }
}

Node *create_tree(char *tree_string) {
    Node *trenutni, *parent, *parents_queue[MAX_NODES];
    int tail, head, i;

    tail = head = -1;
    trenutni = parent = NULL;
    parents_queue[0] = NULL;
    for (i=0; i<strlen(tree_string); i++) {
        if (tree_string[i]!=';') {
            if (tree_string[i]=='-') continue;
            trenutni = malloc(sizeof(Node));
            trenutni->val = tree_string[i];
            trenutni->left = trenutni->right = NULL;

            parents_queue[++tail] = trenutni;
            if (parent && tree_string[i-1]==';') {
                parent->left = trenutni;
            } else if (i>0) {
                parent->right = trenutni;
            }
        } else {
            parent = parents_queue[++head];
        }
    }
    return parents_queue[0];
}

int main () {
    Node *root=NULL, *root2=NULL;
    int menu_choice;
    char c, tree_string[MAX_TREE_STRING];

    setbuf(stdout, NULL);
    do {
        menu_choice = 0;
        DEBUG("\n1 Kreiraj stablo\n2 Ispisi stablo\n3 Najveci element\n4 Najmanji element\n5 Broj cvorova\n6 Zrcalno stablo\n7 Identicno\n8 Izlaz\n");
        scanf("%d", &menu_choice);
        switch (menu_choice) {
            case 1:
                DEBUG("Unesite stablo kao niz alfanumerickih znakova odvojenih sa znakom ;\n");
                scanf(" %s", tree_string);
                root = create_tree(tree_string);
                break;
            case 2:
                ispisi_stablo(root);
                break;
            case 3:
                printf("%c\n", najveci_element(root));
                break;
            case 4:
                printf("%c\n", najmanji_element(root));
                break;
            case 5:
                printf("%d\n", broj_cvorova(root));
                break;
            case 6:
                zrcalno_stablo(root);
                break;
            case 7:
                DEBUG("Unesite stablo za usporedbu kao niz alfanumerickih znakova odvojenih sa znakom ;\n");
                scanf(" %s", tree_string);
                root2 = create_tree(tree_string);
                printf("%c\n", identicna(root, root2) ? 'Y' : 'N');
                break;
            case 8:
                break;
            default:
                while((c = getchar()) != '\n' && c != EOF);
        }
    } while(menu_choice!=8);
    return 0;
}
