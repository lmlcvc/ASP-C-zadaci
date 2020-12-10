#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXK 100000


int main() {
	int n; // broj stranica
	int k; // broj obrisanih stranica
	int a[MAXK]; // polje s obrisanim stranicama 
	int q; // broj upita

	// unos podataka
	scanf("%d %d\n", &n, &k);
	for(int i = 0; i < k; i++){
		scanf("%d ", &a[i]);
	}

	// odgovaranje na q upita
	scanf("%d\n", &q);
	for(int i = 0; i < q; i++){
		int lo = -1;
		int hi = k;
		int mid;
		int p; // broj stranice koju tražimo
		scanf("%d\n", &p);

		// binarnim pretraživanjem u polju a
		// pronaći indeks elementa koji je
		// veći od traženog, i oduzeti

		while(lo + 1 < hi){
			mid = (hi + lo) / 2;
			if(p < a[mid]){
				hi = mid;
			} else{
				lo = mid;
			}
		}
		printf("%d\n", p - hi);
	}

	return 0;
}