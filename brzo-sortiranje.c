#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif


void merge(int array[], int temp[], int left_start, int right_pos, int right_end){
	// right_pos == mid + 1

	int left_end = right_pos - 1;
	int left_pos = left_start;
	int temp_pos = left_start;

	while((left_pos <= left_end) && (right_pos <= right_end)){
		if(array[left_pos] <= array[right_pos]){
			// uzeti lijevi element
			// povećati indekse pozicija
			temp[temp_pos++] = array[left_pos++];
		} else{
			// uzeti desni element
			// povećati indekse pozicija
			temp[temp_pos++] = array[right_pos++];
		}
	}

	// prebaciti elemente s kraja jednog od nizova na kraj temp-a
	while(left_pos <= left_end){
		temp[temp_pos++] = array[left_pos++];
	}
	while(right_pos <= right_end){
		temp[temp_pos++] = array[right_pos++];
	}

	// prebacivanje nazad u polje
	--right_pos; // jer smo izvan polja
	while(right_pos >= left_start){
		array[right_pos] = temp[right_pos];
		right_pos--;
	}
}


void merge_sort(int array[], int temp[], int left, int right){
	
	if(right > left){
		int mid = (right + left) / 2;

		merge_sort(array, temp, left, mid);
		merge_sort(array, temp, mid + 1, right);
		merge(array, temp, left, mid + 1, right);
	}
}




void swap(int *a, int *b){
	int t = *a;
	*a = *b;
	*b = t;
}


void quick_sort(int array[], int l, int r){
	// int pivot_index = r; // pivot na kraju
	int pivot_index = (l + r) / 2;

	// stavljanje pivota na kraj
	swap(&array[pivot_index], &array[r]);
	int pivot_value = array[r];

	// partitioning
	int i = l - 1; // brojač stavljamo prije početka
	for(int j = l; j < r; j++){
		if(array[j] <= pivot_value){
			i++;
			swap(&array[i], &array[j]);
		}
	}
	// mijenjanje prvog elementa u desnom podnizu (++i)
	// sa onim zadnjim
	swap(&array[++i], &array[r]);

	// ako postoji više elemenata u nekom podnizu
	// taj se podniz mora sortirati
	if(i > l){
		quick_sort(array, l, i - 1);
	}
	if(i < r){
		quick_sort(array, i + 1, r);
	}
}



int main() {
	int n;
	int *array;// *temp;

	// unos
	scanf("%d\n", &n);
	array = malloc(n * sizeof(int));
	// temp = malloc(n* sizeof(int));
	for(int i = 0; i < n; i++){
		scanf("%d ", array + i);
	}

	// merge_sort(array, temp, 0, n - 1);
	quick_sort(array, 0, n - 1);

	// ispis
	for(int i = 0; i < n; i++){
		printf("%d ", array[i]);
	}
	printf("\n");

	// oslobađanje memorije
	free(array);
	// free(temp);

	return 0;
}