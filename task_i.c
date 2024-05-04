#define _CRT_SECURE_NO_WARNINGS    //这一行不用加上，防止编译器报错的
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int compare(const void* a, const void* b) {
    double f = *(double*)a - *(double*)b;
    if (f > 0) return 1;
    if (f < 0) return -1;
    return 0;
}

double findMedian(double arr[], int n) {
    qsort(arr, n, sizeof(double), compare);
    if (n % 2 != 0)
        return (double)arr[n / 2];

    return (double)(arr[(n - 1) / 2] + arr[n / 2]) / 2.0;
}

int main(void) {
#define N 201
#define M 3
    double data[N][M];

#define MAXCHAR 1000
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
        if (row == 1) {
            continue;
        }
        char* value = strtok(buffer, ", ");
        while (value) {
            data[row - 2][column] = strtod(value, &ptr);
            value = strtok(NULL, ", ");
            column++;
        }
    }
    fclose(fptr);
    fptr = NULL;

    double medians[M];
    for (int i = 0; i < M; i++) {
        medians[i] = findMedian(data[i], N);
    }

    printf("%.2f,%.2f,%.2f\n", medians[0], medians[1], medians[2]);

    return EXIT_SUCCESS;
}