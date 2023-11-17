#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h> // Adicione esta linha para usar o tipo bool

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped; // Use o tipo bool para representar se houve uma troca
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
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
    int n; // Não é necessário especificar o tamanho do array aqui

    // Ler os números do arquivo de entrada
    readNumbersFromFile(inputFileName, arr, &n);

    if (n < 5000)
    {
        printf("O arquivo não contém 10.000 números.\n");
        return 1; // Saia com um código de erro
    }

    // IIInicio do timer de execução da ordenacao
    start = clock();
    bubbleSort(arr, n);
    end = clock();
    // Termino do timer de execução da ordenacao

    // Escrever os números ordenados no arquivo de saída
    writeNumbersToFile(outputFileName, arr, n);

    printf("Números organizados foram escritos em %s\n", outputFileName);


    // Cálculo do tempo decorrido em segundos
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %f segundos\n", cpu_time_used);

    return 0;
}
