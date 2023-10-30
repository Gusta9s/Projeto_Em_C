#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

// Variaveis de contagem para os metodos de ordenacao
int insertionSortIterations = 0;
int mergeSortIterations = 0;
int bubbleSortIterations = 0, insertionSortComparisons = 0, mergeSortComparisons = 0, bubbleSortComparisons = 0;

// Defina a estrutura de dados para armazenar as informações de uma linha
struct Dados {
    char ano[100];
    char areaK2[100];
    char municipio[100];
    char codigo_do_IBGE_string[100];
    int codigo_do_IBGE;
};


void insertionSort(struct Dados *dados, int size) {
    int i = 0;

    while (i < size) {
        struct Dados key = dados[i];
        int j = i - 1;

        while (j >= 0 && dados[j].codigo_do_IBGE > key.codigo_do_IBGE) {
            dados[j + 1] = dados[j];
            j--;
            insertionSortIterations++;
        }

        dados[j + 1] = key;
        i++;
    }
}

void merge(struct Dados *dados, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Dados *L = (struct Dados *)malloc(n1 * sizeof(struct Dados));
    struct Dados *R = (struct Dados *)malloc(n2 * sizeof(struct Dados));

    for (i = 0; i < n1; i++) {
        L[i] = dados[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = dados[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i].codigo_do_IBGE <= R[j].codigo_do_IBGE) {
            dados[k] = L[i];
            i++;
        } else {
            dados[k] = R[j];
            j++;
        }
        k++;
        mergeSortIterations++;
    }

    while (i < n1) {
        dados[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        dados[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSortHelper(struct Dados *dados, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(dados, left, mid);
        mergeSortHelper(dados, mid + 1, right);
        merge(dados, left, mid, right);
    }
}

void mergeSort(struct Dados *dados, int size) {
    mergeSortHelper(dados, 0, size - 1);
}

void bubbleSort(struct Dados *dados, int size) {
    int i = 0;
    struct Dados temp;
    int mostrador = 0;

    while (i < size - 1) {
        mostrador = 0;
        int j = 0;

        while (j < size - i - 1) {
            if (dados[j].codigo_do_IBGE > dados[j + 1].codigo_do_IBGE) {
                temp = dados[j + 1];
                dados[j + 1] = dados[j];
                dados[j] = temp;
                bubbleSortIterations++;
                mostrador = 1;
            }

            j++;
        }

        if (mostrador == 0) {
            break;
        }

        i++;
    }
}

int main(int argc, char *argv[]) {
    int size;
    char *ptr;
    FILE *arquivo;

    printf("Digite o tamanho da tabela em linhas: ");
    scanf("%d", &size);
    printf("\n");

    struct timespec start, end;
    double elapsedTime;

    // Aloca memória para armazenar os dados
    struct Dados *dados = (struct Dados *)malloc(size * sizeof(struct Dados));
    if (dados == NULL) {
        perror("Erro ao alocar memória");
        return 1;
    }
    
    char caminho[500];
    int i = 0;
    int opcao = 0;

    // Mensagem receptiva
    printf("==========================\n");
    printf("== ORDENACAO DE DADOS ==\n");
    printf("==========================\n\n");

    // Leitura do caminho absoluto
    printf("Digite o caminho absoluto: ");
    scanf("%s", caminho);

    // Abertura do arquivo CSV
    arquivo = fopen(caminho, "r");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Ignora a primeira linha do arquivo (cabeçalho)
    char line[500];
    fgets(line, sizeof(line), arquivo);

		while (i < size && fgets(line, sizeof(line), arquivo) != NULL) {
	    int fields = sscanf(line, "%[^;];%[^;];%[^;];%[^\n]\n", dados[i].ano, dados[i].areaK2, dados[i].municipio, dados[i].codigo_do_IBGE_string);
	
	    dados[i].codigo_do_IBGE = atoi(dados[i].codigo_do_IBGE_string);

        // Imprime os valores das colunas
        printf("Ano da Verificacao: '%s'\n", dados[i].ano);
        printf("Area em K2: '%s'\n", dados[i].areaK2);
        printf("Municipio verificado: '%s'\n", dados[i].municipio);
        printf("Codigo do IBGE: '%d'\n\n", dados[i].codigo_do_IBGE);

        i++;
    }

    // Fecha o arquivo apos a leitura
    fclose(arquivo);

    // Menu para selecao do metodo de ordenacao
    printf("Selecione um metodo de ordenacao:\n");
    printf("1. Insertion Sort\n");
    printf("2. Merge Sort\n");
    printf("3. Bubble Sort\n");
    scanf("%d", &opcao);
    printf("\n");

    // Ordena os dados com base na opcao selecionada
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

            // Cálculo do tempo decorrido em segundos
            elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            
            printf("\n\n========== RESULTADO DA ORDENACAO ==========\n");
            for (i = 0; i < size; i++) {
                printf("%d ", dados[i].codigo_do_IBGE);
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

            // Chame mergeSort com os dados
    		mergeSort(dados, size);

            if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
                perror("clock_gettime");
                return 1;
            }


            // Cálculo do tempo decorrido em segundos
            elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            
            printf("\n\n========== RESULTADO DA ORDENACAO ==========\n");
            for (i = 0; i < size; i++) {
                printf("%d ", dados[i].codigo_do_IBGE);
            }
            printf("\n");

            printf("\n\n========== RELATORIO ==========\n");
            printf("Iteraveis do Merge Sort: %d\n", mergeSortIterations);
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

            // Cálculo do tempo decorrido em segundos
            elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            
            printf("\n\n========== RESULTADO DA ORDENACAO ==========\n");
            for (i = 0; i < size; i++) {
                printf("%d ", dados[i].codigo_do_IBGE);
            }
            printf("\n");

            printf("\n\n========== RELATORIO ==========\n");
            printf("Iteraveis do Bubble Sort: %d\n", bubbleSortIterations);
            printf("Tempo decorrido no metodo de ordenacao: %f segundos\n", elapsedTime);
            
            bubbleSortComparisons = bubbleSortIterations;
            break;
            
        default:
            printf("Opcao invalida.\n");
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

	int aud = 0;
	
    // Escreve os dados ordenados no novo arquivo
    while (aud < size) {
        fprintf(arquivoOrdenado, "%s, %s, %s, %d\n", dados[aud].ano, dados[aud].areaK2, dados[aud].municipio, dados[aud].codigo_do_IBGE);
        aud++;
    }

    // Fecha o arquivo de saï¿½da
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

    // Libera a memória alocada dinamicamente
	 	free(dados);

    return 0;
}
