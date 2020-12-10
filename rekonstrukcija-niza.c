#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXS 100000

typedef struct Node{
	int val;
	struct Node *next;
} node;


node *insert(node *prev, int val){
	node *newn = malloc(sizeof(node));
	newn->val = val;
	newn->next = NULL;
	if(prev != NULL) prev->next = newn;
	return newn;
}


int main() {
	int n, q; // broj el. inicijalnog niza, broj akcija
	char entry[5];
	node *niz[MAXS];

	scanf("%d %d\n", &n, &q);
	// niz = malloc(sizeof(node *));

	// unos inicijalnog niza
	for(int i = 0; i < n; i++){
		int val;
		scanf("%d ", &val);

		// da li dodajemo na početak niza?
		node *prev = i ? niz[i-1] : NULL;

		niz[i] = insert(prev, val);
	}


	for(int i = 0; i < q; i++){
		int p, k;
		scanf("%s", entry);
		scanf("%d %d ", &p, &k);

		if(!strcmp(entry, "add")){
			// označiti početak gdje će se dodavati
			node *prev = niz[p - 1];
			// unos brojeva: add p k a1 a2 ... ak
			// iza p-tog elementa inicijalnog niza
			// unosi se k brojeva: a1, a2, ..., ak
			for(int i = 0; i < k; i++){
				// unosimo taj "an" niz
				int val;
				scanf("%d ", &val);
				prev = insert(prev, val);
			}
			if(p < n) prev->next = niz[p];

		} else if(!strcmp(entry, "prn")){
			// prn p k
			// od p-tog elementa cijelog niza
			// treba ispisati k elemenata
			node *curr = niz[p - 1];

			for(int i = 0; i < k; i++){
				printf("%d ", curr->val);
				if(curr->next){
					curr = curr->next;
				} else{
					break;
				}
			}
			printf("\n");
		}
	}
}