#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

typedef struct node_struct{
    int key;
    struct node_struct *parent;
    struct node_struct *left;
    struct node_struct *right;
} Node;

void add_node(Node **root, int key) {
    Node *new_node, *trenutni, *prethodni=NULL;

    new_node = malloc(sizeof(Node));
    new_node->key = key;
    new_node->left = new_node->right = NULL;

    trenutni = *root;
    while (trenutni!=NULL) {
        prethodni = trenutni;
        if (new_node->key < trenutni->key)
            trenutni = trenutni->left;
        else
            trenutni = trenutni->right;
    }

    new_node->parent = prethodni;
    if (prethodni==NULL)
        *root = new_node;
    else if (new_node->key < prethodni->key)
        prethodni->left = new_node;
    else
        prethodni->right = new_node;
}

Node *search(Node *node, int key) {
    while (node!=NULL && key!=node->key) {
        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    int i, left, right, width=5;
    char b[width+1];

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

int najnizi_zajednicki_predak(Node *node, int n1, int n2) {
    // napreduj kroz stablo dok su ti i n1 i n2
    // sigurno lijevo ili sigurno desno od trenutnog čvora
    if(node->key > n1 && node->key > n2){
        // pozvati se na lijevo podstablo
        return najnizi_zajednicki_predak(node->left, n1, n2);
    } else if(node->key < n1 && node->key < n2){
        // pozvati se na desno podstablo
        return najnizi_zajednicki_predak(node->right, n1, n2);
    }

    // suprotno od toga je da su na odvojenim stranama
    // ili kad imamo čvor koji je sam sebi predak
    // u svakom slučaju tad nam je trenutni čvor predak
    // i ne treba tražiti dalje
    return node->key;
}

int main() {
    int menu_choice, val, n1, n2, i;
    char c, print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
    Node *root = NULL;

    do {
        /*DEBUG("\n1.Najnizi zajednicki predak (najnizi_zajednicki_predak)");
        DEBUG("\n2.Unos vrijednosti kljuceva (1-999)\n3.Ispis stabla\n4.Izlaz\n");*/
        scanf("%d", &menu_choice);

        switch(menu_choice) {
            case 1:
                do {
                    // DEBUG("Unesite vrijednost prvog cvora: ");
                    scanf("%d", &n1);
                } while (!search(root, n1));
                do {
                    // DEBUG("Unesite vrijednost drugog cvora: ");
                    scanf("%d", &n2);
                } while (!search(root, n2));
                printf("%d\n", najnizi_zajednicki_predak(root, n1, n2));
                break;
            case 2:
                // DEBUG("\nUnos zakljucite bilo kojim nebrojcanim znakom: ");
                while (scanf("%d", &val)==1) {
                    if (val<1 || val>999) continue;
                    add_node(&root, val);
                }
                while((c=getchar())!='\n' && c!=EOF);
                break;
            case 3:
                sprintf(print_format, "%%%ds", WIDTH-1);
                for (i=0; i<HEIGHT; i++)
                    sprintf(s[i], print_format, " ");

                print_tree(root, 0, 0, 0, s);

                sprintf(empty_line, print_format, " ");
                for (i=0; i<HEIGHT; i++) {
                    if (strcmp(s[i], empty_line))
                        printf("%s\n", s[i]);
                }
                break;
            case 4:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=4);
    return 0;
}
