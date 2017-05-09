#include "MMSort.h"

void minMaxPopArr(unsigned long * Arr1, unsigned long * Arr1Size, unsigned long * min, unsigned long * max) {
	//cout << *Arr1Size << " ";
	unsigned long i = 1, j =1, k;
	unsigned long NewSize = 1, * Arr2;
	*min = Arr1[i];
	*max = Arr1[i];
	unsigned long key1 = 0, key2 = 0;
	//find min max
	for (i = 0; i < *Arr1Size; i++) {
		if (Arr1[i] < *min) {
			*min = Arr1[i];
			key1 = i;
		}
		else if (Arr1[i] > *max) {
			*max = Arr1[i];
			key2 = i;
		}

	}
	if (key1 && key2) {
		k = 1;
		Arr2 = (unsigned long *)(malloc(sizeof(unsigned long *) * k));
		for (i = 0; i < (*Arr1Size -= 2) && i != key1 || i != key2; i++)
		{
			for (j = 0; j < k; j++)
				Arr2[j] = Arr1[i];
		}

	}
	else
		cout << "failed" << endl;
	/*j = 1;
	Arr2 = (unsigned long *)(malloc(sizeof(unsigned long *) * (j)));
	for (i = 0; ; i++, j++) {
		cout << i << " " << j << " ";
		if (i != key1 && i != key2) {

		}
		Arr2[j-1] = Arr1[i];
	}*/
	//printArr(Arr2, j);
	//Arr1 = Arr2;
	//free(Arr2);
}
void printArr(unsigned long * arr, unsigned long siz) {
	cout << "{";
	for (unsigned int i = 0; i < siz; i++)
		cout << arr[i] << ", ";
	cout << "}" << endl;
}
void MMSort(unsigned long * Arr1, unsigned long * Arr2, unsigned long * Arr1Size, unsigned long * Arr2Size, unsigned long first) {
	unsigned long min, max;
	if (*Arr1Size == 1 || *Arr1Size == 0) {
		Arr2[first] = Arr1[*Arr1Size];
	}
	else {
		minMaxPopArr(Arr1, Arr1Size, &min, &max);
		*Arr2Size += 2;
		*Arr1Size -= 2;
		Arr2[first] = min;
		Arr2[*Arr2Size - 1] = max;
		first += 1;
		//cout << *Arr1Size << " " << *Arr2Size << endl;
		MMSort(Arr1, Arr2, Arr1Size, Arr2Size, first);
	}	
	
}