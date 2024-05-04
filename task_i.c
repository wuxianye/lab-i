#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // Used for fabs function

// Exchange function
void swap(double* a, double* b) {
	double t = *a;
	*a = *b;
	*b = t;
}
// Quick sort function for sorting
void quickSort(double arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

// partition function
int partition(double arr[], int low, int high) {
	double pivot = arr[high];
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}


// The function for calculating the median
double findMedian(double arr[], int n) {
	quickSort(arr, 0, n - 1);
	if (n % 2 != 0)
		return (double)arr[n / 2];
	return (double)(arr[(n - 1) / 2] + arr[n / 2]) / 2.0;
}

int main(void) {
#define N 201
#define M 3
	double data[N][M];

#define MAXCHAR 100
	char buffer[MAXCHAR];
	int row = 0;
	int column = 0;
	char* ptr;

	char fn[] = "data.csv";
	FILE* fptr;
	fptr = fopen(fn, "r");
	if (fptr == NULL) {
		printf("Error opening file.\n");
		return EXIT_FAILURE;
	}
	while (fgets(buffer, MAXCHAR, fptr)) {
		column = 0;
		row++;
		//if (row == 1) {
		//	continue; // Skip Title Rows
		//}
		char* value = strtok(buffer, ", ");
		while (value) {
			data[row - 2][column] = strtod(value, &ptr);
			value = strtok(NULL, ", ");
			column++;
		}
	}
	fclose(fptr);
	fptr = NULL;

	// Calculate the median of each column
	double medians[M];
	for (int i = 0; i < M; i++) {
		medians[i] = findMedian(data[i], N);
	}

	// Format output result
	printf("%.2f,%.2f,%.2f\n", medians[0], medians[1], medians[2]);

	return EXIT_SUCCESS;
}