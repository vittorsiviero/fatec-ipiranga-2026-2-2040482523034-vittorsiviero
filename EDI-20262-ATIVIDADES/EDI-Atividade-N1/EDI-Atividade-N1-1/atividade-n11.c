#include <stdio.h>
#define TAMANHO_TURMA 5

void exibirCabecalho(void) {
    printf("===================================\n");
    printf("SISTEMA DE NOTAS - TURMA ADS\n");
    printf("===================================\n");
}

float calcularMedia(float vetor[], int tamanho) {
    float soma = 0.0;
    for (int i = 0; i < tamanho; i++) {
        soma += vetor[i];
    }
    return soma / tamanho;
}

void simularAjuste(float notaOriginal, float bonus) {
    float resultado = notaOriginal + bonus;
    printf("Simulacao para o aluno 1: %.2f + %.2f = %.2f (nao aplicado ainda)\n", 
           notaOriginal, bonus, resultado);
}

void aplicarBonus(float *nota, float bonus) {
    *nota += bonus;
}

int main(void) {
    float notas[TAMANHO_TURMA];
    float bonus;

    exibirCabecalho();

    for (int i = 0; i < TAMANHO_TURMA; i++) {
        printf("Nota do aluno %d: ", i + 1);
        scanf("%f", &notas[i]);
    }
    
    printf("Informe o valor do bonus a aplicar: ");
    scanf("%f", &bonus);

    printf("\n--- Media da turma antes do ajuste ---\n");
    float mediaInicial = calcularMedia(notas, TAMANHO_TURMA);
    printf("Media inicial: %.2f\n\n", mediaInicial);

    printf("--- Simulacao do ajuste (passagem por valor) ---\n");
    simularAjuste(notas[0], bonus);
    printf("Nota do aluno 1 apos a simulacao (inalterada): %.2f\n\n", notas[0]);

    printf("--- Aplicacao real do bonus (passagem por referencia) ---\n");
    for (int i = 0; i < TAMANHO_TURMA; i++) {
        aplicarBonus(&notas[i], bonus);
    }
    printf("Bonus de %.2f aplicado a todas as notas da turma.\n\n", bonus);

    printf("--- Notas finais da turma ---\n");
    for (int i = 0; i < TAMANHO_TURMA; i++) {
        printf("Aluno %d: %.2f\n", i + 1, notas[i]);
    }

    printf("\n--- Media da turma apos o ajuste ---\n");
    float mediaFinal = calcularMedia(notas, TAMANHO_TURMA);
    printf("Media final: %.2f\n", mediaFinal);

    return 0;
}