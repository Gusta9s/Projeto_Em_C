#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

int insertionSortIterations = 0, mergeSortIterations = 0, bubbleSortIterations = 0, insertionSortComparisons = 0, mergeSortComparisons = 0, bubbleSortComparisons = 0;

void insertionSort(int arr[], int size) {
	
	int i = 0;
    
	while (i < size) {
    
	    int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
    
	        arr[j + 1] = arr[j];
            j--;
            insertionSortIterations++; // Incrementa o contador de iteracoes
    
	    }

        arr[j + 1] = key;
        i++;
    
	}
}

void merge(int arr[], int left[], int right[], int left_size, int right_size) {
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
            mergeSortIterations++;
        } else {
            arr[k] = right[j];
            j++;
            mergeSortIterations++;
        }
        k++;
    }

    while (i < left_size) {
        arr[k] = left[i];
        i++;
        k++;
        mergeSortIterations++;
    }

    while (j < right_size) {
        arr[k] = right[j];
        j++;
        k++;
        mergeSortIterations++;
    }
}

void mergeSort(int arr[], int size) {
    if (size <= 1) {
        return;
    }

    int mid = size / 2;
    int left[mid];
    int right[size - mid];
    int i = 0;

    while (i < mid) {
        left[i] = arr[i];
        mergeSortIterations++;
        i++;
    }

    while (i < size) {
        right[i - mid] = arr[i];
        mergeSortIterations++;
        i++;
    }

    mergeSort(left, mid);
    mergeSort(right, size - mid);

    merge(arr, left, right, mid, size - mid);
}

void bubbleSort(int arr[], int size){
	
	int i = 0, temp = 0, mostrador = 0;
	
	while(i < size - 1){
		
		mostrador = 0;
		int j = 0;
		
		while(j < size - i - 1){
			
			if(arr[j] > arr[j + 1]){
				
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
				bubbleSortIterations++;
				mostrador = 1;
				
			}	
			
			j++;
				
		}
			
		if(mostrador == 0){
			break;
			
		}
		
		i++;
	}
}

/**void insertionSort(int arr[], int size) {
	
	int i = 0;
	
    while (i < size - 1) {
        
		int *key = arr[i];
        int j = i - 1;
        int temp;
        
        if(key[i] > key[i + 1]){
        	
			temp = key[i + 1];
        	key[i + 1] = key[i];
        	key[i] = temp;
        	insertionSortIterations++; // Incrementa o contador de iteraï¿½ï¿½es
        	
        	while(j >= 0){
        		
        		if(key[j] > temp){
        			
					key[j + 1] = key[j];
        			key[j] = temp;
        			j--;
        			insertionSortIterations++; // Incrementa o contador de iteraï¿½ï¿½es
        			
				}
        		
			}
		}
    }
}
**/

int main() {
    char caminho[500];
    int size;
    int i = 0, opcao = 0;
    struct timespec start, end;
    double elapsedTime;

    printf("Digite o tamanho do array: ");
    scanf("%d", &size);

    int *arr = (int *)malloc(size * sizeof(int));

    printf("Digite o caminho do arquivo: ");
    scanf("%s", caminho);

    FILE *nomeArquivo = fopen(caminho, "r");

    if (nomeArquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return 1;
    }

    int value;
    char line[500]; // Suponha que cada linha do arquivo contenha nï¿½meros inteiros, um por linha

    while (i < size && fgets(line, sizeof(line), nomeArquivo) != NULL) {
    
	// Use atoi para converter a linha em um nï¿½mero inteiro
    value = atoi(line);

    // Armazene o valor no array de inteiros
    arr[i] = value;
    printf("Valor adquirido: %d\n", arr[i]);
    i++;
	
	}

    fclose(nomeArquivo);
    
    // Mensagem receptiva
    printf("==========================\n");
    printf("== ORDENACAO DE DADOS ==\n");
    printf("==========================\n\n");
    
    // Menu para selecao do metodo de ordenacao
    printf("Selecione um metodo de ordenacao:\n");
    printf("1. Insertion Sort\n");
    printf("2. Merge Sort\n");
    printf("3. Bubble Sort\n");
    printf("\n");
	scanf("%d", &opcao);
    
    
    switch (opcao) {
        case 1:
            
			if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
                perror("clock_gettime");
                return 1;
            }

            insertionSort(arr, size);

            if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
                perror("clock_gettime");
                return 1;
            }

            // Cálculo do tempo decorrido em segundos
            elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

            printf("\n\n========== RESULTADO DA ORDENACAO ==========\n");
            for (i = 0; i < size; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");

            printf("\n========== RELATORIO ==========\n");
            printf("Iteracoes do Insertion Sort: %d\n", insertionSortIterations);
            printf("Tempo decorrido no metodo de ordenacao: %f segundos\n\n", elapsedTime);
            
            insertionSortComparisons = insertionSortIterations;
            break;

        case 2:

			if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
                perror("clock_gettime");
                return 1;
            }

            mergeSort(arr, size);

            if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
                perror("clock_gettime");
                return 1;
            }
            
            // Cálculo do tempo decorrido em segundos
            elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

            printf("\n\n========== RESULTADO DA ORDENACAO ==========\n");
            for (i = 0; i < size; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");

            printf("\n========== RELATORIO ==========\n");
            printf("Iteracoes do Merge Sort: %d\n", mergeSortIterations);
            printf("Tempo decorrido no metodo de ordenacao: %f segundos\n\n", elapsedTime);
            
            mergeSortComparisons = mergeSortIterations;
            break;
            
        case 3:
        	
        	if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
                perror("clock_gettime");
                return 1;
            }

            bubbleSort(arr, size);

            if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
                perror("clock_gettime");
                return 1;
            }
            
            // Cálculo do tempo decorrido em segundos
            elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

            printf("\n\n========== RESULTADO DA ORDENACAO ==========\n");
            for (i = 0; i < size; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");

            printf("\n========== RELATORIO ==========\n");
            printf("Iteracoes do Bubble Sort: %d\n", bubbleSortIterations);
            printf("Tempo decorrido no metodo de ordenacao: %f segundos\n\n", elapsedTime);
            
        	bubbleSortComparisons = bubbleSortIterations;
            break;
    }

	char gravacaoAOrdenados[100];
	int aud = 0;
	
    printf("Digite o nome do arquivo de saida, dos dados ordenados: ");
    scanf("%s", gravacaoAOrdenados);

    FILE *arquivoOrdenado = fopen(gravacaoAOrdenados, "w");
    if (arquivoOrdenado == NULL) {
        perror("Erro ao criar o arquivo de saida");
        return 1;
    }

    // Escreve os dados ordenados no novo arquivo
        
    while (aud < size) {
    	fprintf(arquivoOrdenado, "%d\n", arr[aud]);
    	aud++;
	}

	fclose(arquivoOrdenado);
	
	char gravacaoIteraveis[100];
	
	printf("Digite o nome do arquivo de saida para os iteraveis: ");
	scanf("%s", gravacaoIteraveis);
	
	FILE *arquivoIteravel = fopen(gravacaoIteraveis, "w");
	if (arquivoIteravel == NULL) {
        perror("Erro ao criar o arquivo de saida");
        return 1;
    }
    
    // Gravar o número de iterações de cada algoritmo
        fprintf(arquivoIteravel, "%d\n", insertionSortComparisons);
        fprintf(arquivoIteravel, "%d\n", mergeSortComparisons);
        fprintf(arquivoIteravel, "%d\n", bubbleSortComparisons);

        fclose(arquivoIteravel);		
	
	char gravacaoTempo[100];
	
	printf("Digite o nome do arquivo de saida para o tempo de execucao dos metodos de ordenacao: ");
	scanf("%s", gravacaoTempo);
	
	FILE *arquivoTempo = fopen(gravacaoTempo, "w");
	if (arquivoTempo == NULL) {
        perror("Erro ao criar o arquivo de saida");
        return 1;
    }
    
    // Gravar o número de iterações de cada algoritmo
        fprintf(arquivoTempo, "%f", elapsedTime);

        fclose(arquivoTempo);	
	
    free(arr);

    return 0;
}
