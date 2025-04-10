#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    char areaAtuacao[50];
    double valorAtual;
    double valorAnterior;
    double variacao;
} Acao;

// Função para calcular a variação em porcentagem
void calcularVariacao(Acao *acao) {
    acao->variacao = ((acao->valorAtual - acao->valorAnterior) / acao->valorAnterior) * 100;
}

// Função para preencher os campos de uma ação
void preencherAcao(Acao *acao) {
    printf("Nome da companhia: ");
    scanf("%s", acao->nome);

    printf("Área de atuação: ");
    scanf("%s", acao->areaAtuacao);

    printf("Valor atual da ação (R$): ");
    scanf("%lf", &acao->valorAtual);

    printf("Valor anterior da ação (R$): ");
    scanf("%lf", &acao->valorAnterior);

    calcularVariacao(acao);
}

// Função para imprimir os campos de uma ação
void imprimirAcao(Acao *acao) {
    printf("\nNome da companhia: %s\n", acao->nome);
    printf("Área de atuação: %s\n", acao->areaAtuacao);
    printf("Valor atual da ação (R$): %.2f\n", acao->valorAtual);
    printf("Valor anterior da ação (R$): %.2f\n", acao->valorAnterior);
    printf("Variação da ação: %.2f%%\n", acao->variacao);
}

int main() {
    Acao acoes[3];

    // Preencher os campos de 3 structs
    for (int i = 0; i < 3; i++) {
        printf("\nPreenchendo dados da ação %d:\n", i + 1);
        preencherAcao(&acoes[i]);
    }

    // Imprimir os campos de 3 structs
    for (int i = 0; i < 3; i++) {
        printf("\nDados da ação %d:\n", i + 1);
        imprimirAcao(&acoes[i]);
    }

    return 0;
}