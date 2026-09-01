#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALOR_PREMIUM 100.0

/* Registro para armazenar dados de cada veiculo */
typedef struct {
    char placa[8];
    float valor;
} Veiculo;

/* Funcao que imprime o cabecalho padrao do sistema */
void exibirCabecalho(void) {
    printf("=========================================\n");
    printf("LAVA-RAPIDO BRILHO TOTAL FILA DE ATENDIMENTO\n");
    printf("=========================================\n");
}

/* Preenchimento iterativo utilizando aritmetica de ponteiros */
void preencherFrota(Veiculo *frota, int quantidade) {
    int i;
    for (i = 0; i < quantidade; i++) {
        printf("Placa do veiculo %d: ", i + 1);
        scanf("%7s", (frota + i)->placa);
        printf("Valor do servico (R$): ");
        scanf("%f", &(frota + i)->valor);
    }
}

/* Exibicao recursiva dos veiculos cadastrados */
void exibirFrotaRecursivo(Veiculo *frota, int indice, int quantidade) {
    /* Caso base: alcancou o final do vetor */
    if (indice == quantidade) {
        return;
    }
    
    /* Passo recursivo: imprime o elemento atual e avanca o indice */
    printf("%d) Placa: %s | Valor: R$ %.2f\n", indice + 1, frota[indice].placa, frota[indice].valor);
    exibirFrotaRecursivo(frota, indice + 1, quantidade);
}

/* 
 * Soma recursiva dos valores arrecadados:
 * - Caso base: quando indice == quantidade, retorna 0.0f
 * - Passo recursivo: soma o valor do indice atual com o retorno da chamada para (indice + 1)
 */
float calcularValorTotalRecursivo(Veiculo *frota, int indice, int quantidade) {
    if (indice == quantidade) {
        return 0.0f;
    }
    return frota[indice].valor + calcularValorTotalRecursivo(frota, indice + 1, quantidade);
}

/* Busca recursiva de um veiculo pela placa */
int buscarVeiculoRecursivo(Veiculo *frota, int indice, int quantidade, char placa[8]) {
    /* Caso base 1: chegou ao fim sem encontrar */
    if (indice == quantidade) {
        return -1;
    }
    /* Caso base 2: encontrou o veiculo correspondente */
    if (strcmp(frota[indice].placa, placa) == 0) {
        return indice;
    }
    /* Passo recursivo: busca no proximo elemento */
    return buscarVeiculoRecursivo(frota, indice + 1, quantidade, placa);
}

/* Contagem recursiva de servicos com valor igual ou superior a VALOR_PREMIUM */
int contarPremiumRecursivo(Veiculo *frota, int indice, int quantidade) {
    int count = 0;
    
    /* Caso base: fim do vetor */
    if (indice == quantidade) {
        return 0;
    }
    
    /* Passo recursivo: incrementa se for premium e chama o proximo */
    if (frota[indice].valor >= VALOR_PREMIUM) {
        count = 1;
    }
    
    return count + contarPremiumRecursivo(frota, indice + 1, quantidade);
}

int main(void) {
    int quantidade;
    Veiculo *frota = NULL;
    char placaBusca[8];
    int posEncontrada;
    int qtdPremium;
    float totalArrecadado;

    exibirCabecalho();

    printf("Quantos veiculos serao atendidos hoje? ");
    if (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
        return 1;
    }

    /* Alocacao dinamica do vetor conforme tamanho informado */
    frota = (Veiculo *) malloc(quantidade * sizeof(Veiculo));
    
    /* Verificacao de seguranca do retorno do malloc */
    if (frota == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    /* Leitura dos dados */
    preencherFrota(frota, quantidade);

    /* Relatorio dos atendimentos */
    printf("\nVeiculos atendidos hoje\n");
    exibirFrotaRecursivo(frota, 0, quantidade);

    /* Busca por placa */
    printf("\n--- Busca recursiva por placa\n");
    printf("Placa a ser pesquisada: ");
    scanf("%7s", placaBusca);

    posEncontrada = buscarVeiculoRecursivo(frota, 0, quantidade, placaBusca);
    if (posEncontrada != -1) {
        printf("Veiculo encontrado na posicao %d! Placa: %s | Valor: R$ %.2f\n", 
               posEncontrada + 1, frota[posEncontrada].placa, frota[posEncontrada].valor);
    } else {
        printf("Veiculo nao encontrado na frota.\n");
    }

    /* Processamento recursivo dos totais */
    qtdPremium = contarPremiumRecursivo(frota, 0, quantidade);
    totalArrecadado = calcularValorTotalRecursivo(frota, 0, quantidade);

    /* Resumo final */
    printf("\n--- Resumo dia\n");
    printf("Total de veiculos atendidos: %d\n", quantidade);
    printf("Servicos premium (>= R$ 100.00): %d\n", qtdPremium);
    printf("Valor total arrecadado: R$ %.2f\n", totalArrecadado);

    /* Liberacao de memoria e anulacao do ponteiro */
    free(frota);
    frota = NULL;
    printf("\nMemoria da frota liberada com sucesso. Sistema encerrado.\n");

    return 0;
}