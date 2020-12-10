#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    int i, left, right, width = 3;

    if (!tree) return 0;
    sprintf(b, "(%c)", tree->key);
    left = print_tree(tree->left, 1, offset, depth+1, s);
    right = print_tree(tree->right, 0, offset+left+width, depth+1, s);
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

Node *create_tree(char *tree_string) {
    Node *queue[MAX_NODES];
    Node *trenutni, *parent;
    int tail, head, i;

    tail = head = -1;
    trenutni = parent = NULL;

    for(i=0; i<strlen(tree_string); i++) {
        if (tree_string[i]!=';') {
            if (tree_string[i]=='-') continue;
            trenutni = (Node *)malloc(sizeof(Node));
            trenutni->key = tree_string[i];
            trenutni->left = trenutni->right = NULL;

            queue[++tail] = trenutni;
            if (parent && tree_string[i-1]==';') {
                parent->left = trenutni;
            } else if (i>0) {
                parent->right = trenutni;
            }
        } else {
            parent = queue[++head];
        }
    }
    return queue[0];
}


int sum_depths(Node *node, int depth, int *num){
    int h = 0;

    // osnovni slučaj - prazan čvor
    if(!node) return 0;

    // napredak
    // našli smo čvor koji ima samo jedno dijete
    if((node->left && !(node->right)) || (node->right && !(node->left))){
        h = depth;
        (*num)++;
    }
    // rekurzivni poziv i dodavanje h
    return sum_depths(node->left, depth+1, num) + sum_depths(node->right, depth+1, num) + h;

}


void prosjecna_dubina(Node *root) {
    int depth, num = 0;

    // provjera da stablo nije prazno
    if(root){
        depth = (double)sum_depths(root, 0, &num);
        // provjera da ne dijelimo s 0 (root jedina razina)
        if(num > 0){
            printf("%.2f\n", depth / (double)num);
            return;
        }
    }

    // prazno stablo
    printf("0.00\n");
}

int main () {
    Node *root=NULL;
    int i, menu_choice;
    char c, tree_string[MAX_TREE_STRING];
    char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];

    setbuf(stdout, NULL);
    do {
        menu_choice = 0;
        DEBUG("\n1 Prosjecna dubina cvorova s jednim djetetom (prosjecna_dubina)");
        DEBUG("\n2 Kreiraj stablo \n3 Ispis \n4 Izlaz\n");
        scanf("%d", &menu_choice);
        switch (menu_choice) {
            case 1:
                prosjecna_dubina(root);
                break;
            case 2:
                DEBUG("Unesite stablo kao niz alfanumerickih znakova odvojenih sa znakom ;\n");
                scanf(" %s", tree_string);
                root = create_tree(tree_string);
                break;
            case 3:
                sprintf(print_format, "%%%ds", WIDTH-1);
                for (i=0; i<HEIGHT; i++)
                    sprintf(s[i], print_format, " ");

                print_tree(root, 0, 0, 0, s);

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
