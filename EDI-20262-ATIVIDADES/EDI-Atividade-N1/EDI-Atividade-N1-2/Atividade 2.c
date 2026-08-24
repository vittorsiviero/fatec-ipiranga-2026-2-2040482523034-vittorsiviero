#include <stdio.h>

#define TAMANHO_ESTOQUE 5
#define ESTOQUE_MINIMO 10

int estoque[TAMANHO_ESTOQUE];

void exibirCabecalho(void) {
    printf("SISTEMA DE ESTOQUE LOJA CONSTRUMAIS\n");
}

void preencherEstoque(void) {
    int *p = estoque;
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        printf("Quantidade do produto %d: ", i + 1);
        scanf("%d", (p + i)); // p + i passa o endereco de memoria
    }
}

void exibirEstoque(int momento) {
    int *p = estoque;
    
    if (momento == 0) {
        printf("\n-- Estoque atual (antes da reposicao) --\n");
    } else {
        printf("\n-- Estoque final (apos reposicao) --\n");
    }

    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        printf("Produto %d: %d unidades\n", i + 1, *(p + i));
    }
}

float calcularMediaEstoque(void) {
    int *p = estoque;
    int soma = 0;

    // p + i e o endereco da posicao; *(p + i) e o valor guardado nesse endereco
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        soma += *(p + i);
    }

    return (float)soma / TAMANHO_ESTOQUE;
}

void simularReposicao(int quantidadeAtual, int reposicao) {
    printf("\n-- Simulacao de reposicao (passagem por valor) --\n");
    printf("Simulacao para o produto 1: %d + %d = %d (nao aplicado ainda)\n", 
           quantidadeAtual, reposicao, quantidadeAtual + reposicao);
}

void aplicarReposicaoGeral(int reposicao) {
    int *p = estoque;
    
    printf("\n-- Aplicacao real da reposicao (ponteiro interno ao vetor global) --\n");
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        *(p + i) += reposicao;
    }
    printf("Reposicao de %d unidades aplicada a todos os produtos do estoque.\n", reposicao);
}

void identificarEstoqueCritico(int minimo) {
    int *p = estoque;
    int criticos_encontrados = 0;

    printf("\n-- Analise de estoque critico (minimo = %d unidades) --\n", minimo);
    
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        if (*(p + i) < minimo) {
            printf("Produto %d esta em nivel critico: %d unidades (abaixo do minimo)\n", i + 1, *(p + i));
            criticos_encontrados++;
        }
    }

    if (criticos_encontrados == 0) {
        printf("Estoque regularizado: nenhum produto abaixo do minimo.\n");
    }
}

int main(void) {
    int reposicao;

    exibirCabecalho();
    preencherEstoque();

    printf("Quantidade de reposicao a aplicar: ");
    scanf("%d", &reposicao);

    exibirEstoque(0);

    int *p = estoque;
    simularReposicao(*p, reposicao);
    printf("Quantidade do produto 1 apos a simulacao (inalterada): %d\n", *p);

    aplicarReposicaoGeral(reposicao);
    exibirEstoque(1);

    printf("\n-- Media geral do estoque --\n");
    printf("Media final: %.2f unidades\n", calcularMediaEstoque());

    identificarEstoqueCritico(ESTOQUE_MINIMO);

    return 0;
}