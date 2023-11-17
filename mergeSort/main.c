#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}

// A utility function to print an array
void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void readNumbersFromFile(const char* fileName, int arr[], int* n)
{
    FILE* inputFile = fopen(fileName, "r");

    if (!inputFile)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    *n = 0;
    while (*n < 5000 && fscanf(inputFile, "%d", &arr[*n]) != EOF)
    {
        (*n)++;
    }

    fclose(inputFile);
}

void writeNumbersToFile(const char* fileName, int arr[], int n)
{
    FILE* outputFile = fopen(fileName, "w");

    if (!outputFile)
    {
        perror("Erro ao criar o arquivo");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(outputFile, "%d\n", arr[i]);
    }

    fclose(outputFile);
}

int main()
{
    clock_t start, end;
    double cpu_time_used;


    const char* inputFileName = "C:\\C_Project\\input.txt";   // Nome do arquivo de entrada
    const char* outputFileName = "output.txt"; // Nome do arquivo de saída

    int arr[5000];
    int n;

    // Ler os números do arquivo de entrada
    readNumbersFromFile(inputFileName, arr, &n);

    if (n < 5000)
    {
        printf("O arquivo não contém 10.000 números.\n");
        return 1; // Saia com um código de erro
    }

    int arr_size = sizeof(arr) / sizeof(arr[0]);    

    start = clock();
    mergeSort(arr, 0, arr_size - 1);
    end = clock();

    // Escrever os números ordenados no arquivo de saída
    writeNumbersToFile(outputFileName, arr, n);

    printf("Números organizados foram escritos em %s\n", outputFileName);


    // Cálculo do tempo decorrido em segundos
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %f segundos\n", cpu_time_used);

    return 0;
}