#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

int insertionSortIterations = 0;
int mergeSortIterations = 0;
int bubbleSortIterations = 0, insertionSortComparisons = 0, mergeSortComparisons = 0, bubbleSortComparisons = 0;

// Defina a estrutura de dados para armazenar as informações de uma linha
struct Dados {
    char id[100];
    char nomeEmpresa[100];
    char classificacaoEmpresa[100];
    char dataConstrucaoBarragem[100];
};

void insertionSort(struct Dados *arr, int n) {
    int i, j;
    struct Dados key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && strcmp(arr[j].dataConstrucaoBarragem, key.dataConstrucaoBarragem) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
            insertionSortIterations++; // Incrementa o contador
        }
        arr[j + 1] = key;
    }
}

void merge(struct Dados *arr, int left, int middle, int right) {
    int i = 0, j = 0, k = left;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    struct Dados *L = (struct Dados *)malloc(n1 * sizeof(struct Dados));
    struct Dados *R = (struct Dados *)malloc(n2 * sizeof(struct Dados));

    if (L == NULL || R == NULL) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    while (i < n1) {
        L[i] = arr[left + i];
        i++;
    }
    while (j < n2) {
        R[j] = arr[middle + 1 + j];
        j++;
    }

    i = 0;
    j = 0;

    while (i < n1 && j < n2) {
        if (strcmp(L[i].dataConstrucaoBarragem, R[j].dataConstrucaoBarragem) <= 0) {
            arr[k] = L[i];
            i++;
            mergeSortIterations++;
        } else {
            arr[k] = R[j];
            j++;
            mergeSortIterations++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
    mergeSortIterations++; // Incrementa o contador de iterações
}

void mergeSort(struct Dados *arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

void bubbleSort(struct Dados *arr, int n) {
    int i = 0, j = 0;
    struct Dados temp;
    int swapped;

    for (i = 0; i < n - 1; i++) {
        swapped = 0;

        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].dataConstrucaoBarragem, arr[j + 1].dataConstrucaoBarragem) > 0) {
                // Troca os elementos se eles estiverem fora de ordem
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
                bubbleSortIterations++; // Incrementa o contador de iterações
            }
        }

        if (swapped == 0) {
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    int size;
    char *ptr;
    FILE *arquivo;
    
    printf("Digite o tamanho da tabela em linhas: ");
    scanf("%d", &size);

    struct timespec start, end;
    double elapsedTime;

    struct Dados *dados = (struct Dados *)malloc(size * sizeof(struct Dados));
    if (dados == NULL) {
        perror("Erro ao alocar memoria");
        return 1;
    }

    char *caminho[500];
    int i = 0, aud = 0;
    int opcao;

    // Mensagem receptiva
    printf("==========================\n");
    printf("== ORDENACAO DE DADOS ==\n");
    printf("==========================\n\n");

    // Leitura do caminho absoluto
    printf("Digite o caminho absoluto: ");
    scanf("%s", &caminho);

    // Abertura do arquivo CSV
    arquivo = fopen(caminho, "r");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

   char line[500];
    fgets(line, sizeof(line), arquivo);

		while (i < size && fgets(line, sizeof(line), arquivo) != NULL) {
	    int fields = sscanf(line, "%[^,],%[^,],%[^,],%[^,\n]", dados[i].id, dados[i].nomeEmpresa, dados[i].classificacaoEmpresa, dados[i].dataConstrucaoBarragem);

        // Imprime os valores das colunas
        printf("Id_Barragem: '%s'\n", dados[i].id);
        printf("Nome_Empresa: '%s'\n", dados[i].nomeEmpresa);
        printf("Classificacao_Empresa: '%s'\n", dados[i].classificacaoEmpresa);
        printf("Data_Construcao_Barragem: '%s'\n\n", dados[i].dataConstrucaoBarragem);
        i++;
    }

    fclose(arquivo);

    printf("Selecione um metodo de ordenacao:\n");
    printf("1. Insertion Sort\n");
    printf("2. Merge Sort\n");
    printf("3. Bubble Sort\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            
            if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
                perror("clock_gettime");
                return 1;
            }

            insertionSort(dados, size);

            if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
                perror("clock_gettime");
                return 1;
            }

            elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            
            printf("\n\n========== RESULTADO DA ORDENACAO ==========\n");
            for (i = 0; i < size; i++) {
                printf("%s ", dados[i].dataConstrucaoBarragem);
            }
            printf("\n");

            printf("\n\n========== RELATORIO ==========\n");
            printf("Iteracoes do Insertion Sort: %d\n", insertionSortIterations);
            printf("Tempo decorrido no metodo de ordenacao: %f segundos\n", elapsedTime);
            
            insertionSortComparisons = insertionSortIterations;
            break;
            
        case 2:
            
            if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
                perror("clock_gettime");
                return 1;
            }

            mergeSort(dados, 0, size - 1);

            if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
                perror("clock_gettime");
                return 1;
            }

            elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            
            printf("\n\n========== RESULTADO DA ORDENACAO ==========\n");
            for (i = 0; i < size; i++) {
                printf("%s ", dados[i].dataConstrucaoBarragem);
            }
            printf("\n");

            printf("\n\n========== RELATORIO ==========\n");
            printf("Iteracoes do Merge Sort: %d\n", mergeSortIterations);
            printf("Tempo decorrido no metodo de ordenacao: %f segundos\n", elapsedTime);
            
            mergeSortComparisons = mergeSortIterations;
            break;
            
        case 3:
            
            if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
                perror("clock_gettime");
                return 1;
            }

            bubbleSort(dados, size);

            if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
                perror("clock_gettime");
                return 1;
            }

            elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            
            printf("\n\n========== RESULTADO DA ORDENACAO ==========\n");
            for (i = 0; i < size; i++) {
                printf("%s ", dados[i].dataConstrucaoBarragem);
            }
              printf("\n");

            printf("\n\n========== RELATORIO ==========\n");
            printf("Iteracoes do Bubble Sort: %d\n", bubbleSortIterations);
            printf("Tempo decorrido no metodo de ordenacao: %f segundos\n", elapsedTime);
            
            bubbleSortComparisons = bubbleSortIterations;

            break;
            
        default:
        	
            printf("Opcao Invalida.\n");
            return 1;
    }

    // Cria um novo arquivo para os dados ordenados
    char nomeArquivo[100];
    printf("Digite o nome do arquivo de saida: ");
    scanf("%s", nomeArquivo);

    FILE *arquivoOrdenado = fopen(nomeArquivo, "w");
    if (arquivoOrdenado == NULL) {
        perror("Erro ao criar o arquivo de saida");
        return 1;
    }
	
    // Escreve os dados ordenados no novo arquivo
    while (aud < size) {
        fprintf(arquivoOrdenado, "%s, %s, %s, %s\n", dados[aud].id, dados[aud].nomeEmpresa, dados[aud].classificacaoEmpresa, dados[aud].dataConstrucaoBarragem);
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

    	free(dados);

    return 0;
}
