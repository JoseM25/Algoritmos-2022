#ifndef Ordenador_h
#define Ordenador_h

#include <cmath>

class Ordenador{
	private:
    // Defina aquí los métodos auxiliares de los algoritmos de ordenamiento solamente.
    // Puede definir cuantos métodos quiera.
	void merge(int* array, int begin, int middle, int end) {
		int left = middle - begin + 1;
		int right = end - middle;

		int* leftArray = new int[left];
		int* rightArray = new int[right];

		for(int i = 0; i < left; i++) {
			leftArray[i] = array[begin + i];
		}

		for(int j = 0; j < right; j++) {
			rightArray[j] = array[middle + 1 + j];
		}

		int leftCount = 0;
		int rightCount = 0;
		int mergeCount = begin;

		while(leftCount < left && rightCount < right) {
			if(leftArray[leftCount] <= rightArray[rightCount]) {
				array[mergeCount] = leftArray[leftCount];
				leftCount++;
			} else {
				array[mergeCount] = rightArray[rightCount];
				rightCount++;
			}
			mergeCount++;
		}

		while(leftCount < left) {
			array[mergeCount] = leftArray[leftCount];
			leftCount++;
			mergeCount++;
		}

		while(rightCount < right) {
			array[mergeCount] = rightArray[rightCount];
			rightCount++;
			mergeCount++;
		}

		delete[] leftArray;
		delete[] rightArray;
	}

	void mergeSort(int* array, int begin, int end) {
		if(begin < end) {
			int middle = begin + (end - begin) / 2;
			mergeSort(array, begin, middle);
			mergeSort(array, middle + 1, end);
			merge(array, begin, middle, end);
		}
	}

	void maxHeapify(int* array, int n, int i) {
		int temp = 0;
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		if(left < n && array[left] > array[largest]) {
			largest = left;
		}

		if(right < n && array[right] > array[largest]) {
			largest = right;
		}

		if(largest != i) {
			temp = array[i];
			array[i] = array[largest];
			array[largest] = temp;
			maxHeapify(array, n, largest);
		}
	}

	int partition(int* array, int first, int last) {
		int temp = 0;
		int pivot = array[last];
		int i = (first - 1);

		for(int j = first; j < last; j++) {
			if(array[j] <= pivot) {
				i = i + 1;
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
		
		temp = array[i + 1];
		array[i + 1] = array[last];
		array[last] = temp;

		return (i + 1);
	}

	void quickSort(int* array, int first, int last) {
		if(first < last) {
			int pivot = partition(array, first, last);
			quickSort(array, first, pivot - 1);
			quickSort(array, pivot + 1, last);
		}
	}

	size_t getMax(size_t* array, int n) {
		size_t max = array[0];
		for(int i = 1; i < n; i++) {
			if(array[i] > max) {
				max = array[i];
			}
		}
		return max;
	}

	long createBase(int n) {
		long log = (long) floor(log2(n));
		long power = (long) pow(2, log);

		return power;
 	}

	void countingSort(size_t* array, int n, long exp, long base) {
		int* B = new int[n];
		long* C = new long[base];

		for(long i = 0; i < base; i++) {
			C[i] = 0;
		}

		for(int i = 0; i < n; i++) {
			C[(array[i] / exp) % base]++;
		}

		for(long i = 1; i < base; i++) {
			C[i] = C[i] + C[i - 1];
		}

		for(int i = n - 1; i >= 0; i--) {
			B[C[(array[i] / exp) % base] - 1] = array[i];
			C[(array[i] / exp) % base]--;
		}

		for(int i = 0; i < n; i++) {
			array[i] = B[i];
		}

		delete[] C;
		delete[] B;
	}

	void radixSort(size_t* array, int n) {
		long max = (long) getMax(array, n);
		long base = createBase(n);
		for(long exp = 1; max / exp > 0; exp *= base) {
			countingSort(array, n, exp, base);
		}
	}

	void convertInt(int* array, size_t* array2, int n) {
		for(int i = 0; i < n; i++) {
			array2[i] = array[i] + 2147483648;
		}
	}

	void convertBack(int* array, size_t* array2, int n) {
		for(int i = 0; i < n; i++) {
			array[i] = array2[i] - 2147483648;
		}
	}

	public:
	Ordenador(){};
	~Ordenador(){};
    // Si no implementa algunos de los métodos de ordenamiento no lo borre;
    // déjelo con el cuerpo vacío para evitar errores de compilación, ya
    // que se va a ejecutar el mismo «main» para todas las tareas.
    // Implemente los algoritmos en este archivo, no en un CPP.
	void seleccion(int *A, int n) {
		int i, j, min, temp;
		for(i = 0; i < n-1; i++) {
			min = i;
			for(j = i + 1; j < n; j++) {
				if(A[j] < A[min]) {
					min = j;
				}
			}
			temp = A[i];
			A[i] = A[min];
			A[min] = temp;
		}
	}

	void insercion(int *A, int n) {
		int i, j, key;
		for(j = 1; j < n; j++) {
			key = A[j];
			i = j - 1;
			while(i  >= 0 && A[i] > key) {
				A[i + 1] = A[i];
				i = i - 1;
			}
			A[i + 1] = key;
		}
	}

	void mergesort(int *A, int n) {
		mergeSort(A, 0, n-1);
	}
	
	void heapsort(int *A, int n) {
		int temp = 0;
		for(int i = n / 2 - 1; i >= 0; i--) {
			maxHeapify(A, n, i);
		}

		for(int i = n - 1; i > 0; i--) {
			temp = A[0];
			A[0] = A[i];
			A[i] = temp;
			maxHeapify(A, i , 0);

		}
	}

	void quicksort(int *A, int n) {
		quickSort(A, 0, n - 1);
	}

	void radixsort(int *A, int n) {
		size_t* array2 = new size_t[n];
		convertInt(A, array2, n);
		radixSort(array2, n);
		convertBack(A, array2, n);
		delete[] array2;
	}
};
#endif
