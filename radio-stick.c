#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif



int binary_search(int array[], int n, int q){
	int hi = n;
	int lo = -1;
	int mid;

	while(lo + 1 < hi){
		mid = (lo + hi) / 2;

		if(q <= array[mid]){
			hi = mid;
		} else{
			lo = mid;
		}
	}

	return hi;
}



int main() {
	int n; // broj stickova
	int m;
	int q;
	int array[100000]; // stickovi


	// unos broja stickova
	scanf("%d\n", &n);
	for(int i = 0; i < n; i++){
		// svaki stick (element u polju) 
		// zapisuje indeks zadnje pjesme na danom sticku
		scanf("%d ", &array[i]);
		if(i > 0){
			array[i] += array[i - 1];
		}
	}

	// unos broja upita i upita
	scanf("%d\n", &m);
	for(int i = 0; i < m; i++){
		scanf("%d ", &q);

		// +1 zbog modifikacije indeksa sticka
		printf("%d\n", binary_search(array, n, q) + 1);
	}

}