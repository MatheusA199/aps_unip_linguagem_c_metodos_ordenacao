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

void countSort(int arr[], int n, int exp)
{
    int* output = (int*)malloc((unsigned int)n * sizeof(int));
    if (output == NULL) {
    perror("Erro de alocação de memória");
    exit(1);
    }
    int i, count[10] = { 0 };

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
}

void radixsort(int arr[], int n)
{
    int m = getMax(arr, n);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

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
    while (*n < 100000 && fscanf(inputFile, "%d", &arr[*n]) != EOF)
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

    int arr[100000];
    int n;

    // Ler os números do arquivo de entrada
    readNumbersFromFile(inputFileName, arr, &n);

    if (n < 100000)
    {
        printf("O arquivo não contém 10.000 números.\n");
        return 1; // Saia com um código de erro
    }

    // Aplicar o Radix Sort para ordenar os números
    start = clock();
    radixsort(arr, n);
    end = clock();

    // Escrever os números ordenados no arquivo de saída
   // Calcular o tempo decorrido em "tics de relógio"
    clock_t time_elapsed = end - start;

    // Converter "tics de relógio" para segundos (a unidade de clock() é geralmente 1/CLK_TCK segundos)
    double seconds_elapsed = (double)time_elapsed / CLOCKS_PER_SEC;

    // Escrever o tempo exato em segundos
    printf("Tempo de execução: %f segundos\n", seconds_elapsed);

    // Escrever os números ordenados no arquivo de saída
    writeNumbersToFile(outputFileName, arr, n);

    printf("Números organizados foram escritos em %s\n", outputFileName);

    return 0;
}