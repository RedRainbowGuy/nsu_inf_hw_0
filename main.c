#include <stdio.h>
#include <stdlib.h>

int findBigger(int array[], int startIndex, int sepIndex, int separator) {
    for (int i = startIndex; i < sepIndex; ++i) {
        if (array[i] >= separator)
            return i;
    }
    return -1;
}

int findLower(int array[], int endIndex, int sepIndex, int separator) {
    for (int i = sepIndex+1; i < endIndex+1; ++i) {
        if (array[i] <= separator)
            return i;
    }
    return -1;
}

void quickSort(int array[], int arrSize, int startIndex, int endIndex) {
    int sepIndex = (arrSize - 1)/2 + startIndex;
    int separator = array[sepIndex];
    if (arrSize <= 1)
        return;

    int lowerIndex = findLower(array, endIndex, sepIndex, separator);
    int tmp;
    while (lowerIndex != -1) {
        tmp = array[sepIndex];
        array[sepIndex] = array[lowerIndex];
        for (int i = lowerIndex; i > sepIndex + 1; --i) {
            array[i] = array[i - 1];
        }
        array[++sepIndex] = tmp;
        lowerIndex = findLower(array, endIndex, sepIndex, separator);
    }
    int biggerIndex = findBigger(array, startIndex, sepIndex, separator);
    while (biggerIndex != -1) {
        tmp = array[sepIndex];
        array[sepIndex] = array[biggerIndex];
        for (int i = biggerIndex; i < sepIndex-1; ++i) {
            array[i] = array[i + 1];
        }
        array[--sepIndex] = tmp;
        biggerIndex = findBigger(array, startIndex, sepIndex, separator);
    }
    quickSort(array, sepIndex-startIndex+1, startIndex, sepIndex-1);
    quickSort(array, endIndex-sepIndex+1, sepIndex+1, endIndex);
}

int main() {
    FILE *inFile = fopen("in.txt", "r");
    int arrSize;
    if (1 != fscanf(inFile, "%d\n", &arrSize)) {
        fclose(inFile);
        return 0;
    }
    int *array = malloc(sizeof (int) * arrSize);
    for (int i = 0; i < arrSize; ++i)
        fscanf(inFile, "%d", (array + i));
    fclose(inFile);
    quickSort(array, arrSize, 0, arrSize - 1);

    FILE *outFile = fopen("out.txt", "w");
    for (int i = 0; i < arrSize; ++i)
        fprintf(outFile, "%d ", array[i]);
    fclose(outFile);

    return 0;
}
