#include <stdio.h>
#include <stdlib.h>
#define INPUT_FILE_NAME "in.txt"
#define OUTPUT_FILE_NAME "out.txt"

void swap(int *array, int aInx, int bInx) {
    /* :Action: Swap to elements.
     * :args: {array} array, which elements will have been swapped;
     *        {aInx} fist element index;
     *        {bInx} second element index.
     * */
    int tmp = array[aInx];
    array[aInx] = array[bInx];
    array[bInx] = tmp;
}

void quickSort(int array[], int startIndex, int endIndex) {
    /* :Action: Sort the array.
     * :args: {array} array, which will have been sorted;
     *        {startIndex} start index of array part, which will have been sorted;
     *        {endIndex} end index of array part, which will have been sorted.
     * */
    int separator = array[(startIndex+endIndex)/2];
    int toRightInx = startIndex;
    int toLeftInx = endIndex;
    // Replace elements next to pivot {separator}.
    while (toRightInx <= toLeftInx) {
        while (array[toRightInx] < separator)
            toRightInx++;
        while (array[toLeftInx] > separator)
            toLeftInx--;
        if (toRightInx <= toLeftInx) {
            swap(array, toLeftInx, toRightInx);
            toRightInx++;
            toLeftInx--;
        }
    }
    // Sort left subarray and right subarray.
    if (startIndex < toLeftInx)
        quickSort(array, startIndex, toLeftInx);
    if (toRightInx < endIndex)
        quickSort(array, toRightInx, endIndex);
}

void saveIntArray(int *array, int arrSize, FILE *outFile) {
    /* :Action: Save the array in outFile.
     */
    for (int i = 0; i < arrSize; ++i)
        fprintf(outFile, "%d ", array[i]);
}

void fillArray(int *array, int arrSize, FILE *inFile) {
    /* :Action: File the array form inFile.
     */
    for (int i = 0; i < arrSize; ++i)
        fscanf(inFile, "%d", (array + i));
}

int main() {
    int arrSize;
    // Get count of elements from first row in file.
    FILE *inFile = fopen(INPUT_FILE_NAME, "r");
    if (1 != fscanf(inFile, "%d\n", &arrSize)) {
        fclose(inFile);
        return 0;
    }
    // Create and fill the array.
    int *array = malloc(sizeof (int) * arrSize);
    fillArray(array, arrSize, inFile);
    fclose(inFile);
    // Sort the array.
    quickSort(array, 0, arrSize - 1);
    // Save sorted array.
    FILE *outFile = fopen(OUTPUT_FILE_NAME, "w");
    saveIntArray(array, arrSize, outFile);
    fclose(outFile);
    return 0;
}
