#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAX_TREE_STRING 100
#define MAX_NODES 100

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} Node;

int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    char b[HEIGHT];
    int i, left, right, width = 5;

    if (!tree) return 0;
    sprintf(b,"(%03d)",tree->key);
    left = print_tree(tree->left,1,offset,depth+1,s);
    right = print_tree(tree->right,0,offset+left+width,depth+1,s);
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

void add_node(Node **root, int key) {
    Node *new_node, *trenutni, *prethodni=NULL;

    new_node = malloc(sizeof(Node));
    new_node->key = key;
    new_node->left = new_node->right = NULL;

    trenutni = *root;
    while (trenutni!=NULL) {
        prethodni = trenutni;
        if (new_node->key < trenutni->key) {
            trenutni = trenutni->left;
        } else {
            trenutni = trenutni->right;
        }
    }

    if (prethodni==NULL) {
        *root = new_node;
    } else if (new_node->key < prethodni->key) {
        prethodni->left = new_node;
    } else {
        prethodni->right = new_node;
    }
}

int broj_aritmetickih_sredina(Node *node) {
    int isMed = 0; // pretpostavljamo da nije a.s.

        // osnovni slučaj
    // null čvor i čvor bez djece
    if(!node || (!node->left && !node->right)) return 0;

        // napredak
    // provjera je li a.s. i postoje li djeca!!
    isMed = (node->left && node->right &&
        node->key == (node->left->key + node->right->key) / 2);
    // dodavanje tog broja i pozivanje na podstabla
    return broj_aritmetickih_sredina(node->left) + broj_aritmetickih_sredina(node->right) + isMed;
}

int main () {
    Node *root=NULL;
    int i, menu_choice, val;
    char c;
    char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];

    setbuf(stdout, NULL);
    do {
        menu_choice = 0;
        /*DEBUG("1. Broj aritmetickih sredina\n");
        DEBUG("2. Kreiraj stablo\n");
        DEBUG("3. Ispis\n");
        DEBUG("4. Izlaz\n");*/
        scanf("%d", &menu_choice);
        switch (menu_choice) {
            case 1:
                printf("%d\n", (broj_aritmetickih_sredina(root)));
                break;
            case 2:
                // DEBUG("Unos zakljucite bilo kojim nebrojcanim znakom: ");
                while (scanf("%d", &val)==1) {
                    if (val<1 || val>999) continue;
                    add_node(&root,val);
                }
                while((c=getchar())!='\n' && c!=EOF);
                break;
            case 3:
                sprintf(print_format, "%%%ds", WIDTH-1);
                for (i=0; i<HEIGHT; i++)
                    sprintf(s[i], print_format, " ");

                print_tree(root,0,0,0,s);

                sprintf(empty_line, print_format, " ");
                for (i=0; i<HEIGHT; i++) {
                    if (strcmp(s[i],empty_line))
                        printf("%s\n", s[i]);
                }
                break;
            case 4:
                break;
            default:
                while((c = getchar()) != '\n' && c != EOF);
        }
    } while(menu_choice!=4);
    return 0;
}
