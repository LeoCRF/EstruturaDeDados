#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


/*
//Exercicio 1

bool buscarSequencial(int vetor[], int tamanho, int elemento) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == elemento) {
            return true;
        }
    }
    return false;
}


void inserirSemRepetir(int vetor[], int elemento, int quantidadeAtual, int quantidadeMaxima) {
    if (quantidadeAtual >= quantidadeMaxima) {
        printf("Erro: o vetor está cheio.\n");
        return;
    }
    if (!buscarSequencial(vetor, quantidadeAtual, elemento)) {
        vetor[quantidadeAtual] = elemento;
        printf("Valor %d inserido com sucesso.\n", elemento);
    } else {
        printf("Erro: o valor %d já existe no vetor.\n", elemento);
    }
}


void percorrer(int vetor[], int quantidade) {
    printf("Vetor: ");
    for (int i = 0; i < quantidade; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int quantidadeMaxima = 5;
    int vetor[quantidadeMaxima];
    int quantidadeAtual = 0;
    int elemento;

    printf("Insira até %d valores diferentes:\n", quantidadeMaxima);

    while (quantidadeAtual < quantidadeMaxima) {
        printf("Digite um valor: ");
        scanf("%d", &elemento);
        inserirSemRepetir(vetor, elemento, quantidadeAtual, quantidadeMaxima);
        if (!buscarSequencial(vetor, quantidadeAtual, elemento)) {
            quantidadeAtual++;
        }
    }

    percorrer(vetor, quantidadeAtual);

    return 0;
}

*/

//Exercicio 2
/*
#define max 10

void inserir(int lista[], int *tamanho, int valor) {
    if (*tamanho >= max) {
        printf("Lista cheia. Não é possível inserir o valor %d.\n", valor);
        return;
    }
    int i;
    for (i = *tamanho - 1; i >= 0 && lista[i] < valor; i--) {
        lista[i + 1] = lista[i];
    }
    lista[i + 1] = valor;
    (*tamanho)++;
    printf("Valor %d inserido com sucesso.\n", valor);
}

void remover(int lista[], int *tamanho, int valor) {
    int i, posicao = -1;
    for(i = 0; i < *tamanho; i++) {
        if(lista[i] == valor) {
            posicao = i;
            break;
        }
    }

    (*tamanho)--;
    printf("Valor %d removido com sucesso.\n", valor);
}

int buscar(int lista[], int tamanho, int valor) {
    int inicio = 0, fim = tamanho - 1, meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if(lista[meio] == valor) {
            return meio;
        } else if (lista[meio] < valor) {
            fim = meio -1;
        } else {
            inicio = meio + 1;
        }
    }
    return -1;
}

void percorrer( int lista[], int tamanho) {
    printf("Lista: ");
    for(int i = 0; i < tamanho; i++) {
        printf(" %d ", lista[i]);
    }
    printf("\n");
}

int main() {
    int lista[max];
    int tamanho = 0, opcao, valor;

    do {
        printf("\n Menu: \n");
        printf("1. Inserir valor\n");
        printf("2. Remover valor\n");
        printf("3. Buscar valor\n");
        printf("4. Percorrer lista\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                inserir(lista, &tamanho, valor);
                break;

            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                remover(lista, &tamanho, valor);
                break;

            case 3:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                int posicao = buscar(lista, tamanho, valor);
                if (posicao != -1) {
                    printf("Valor %d encontrado na posição %d.\n", valor, posicao);
                } else {
                    printf("Valor %d não encontrado.\n", valor);
                }
                break;

            case 4:
                percorrer(lista, tamanho);
                break;

            case 5:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}
*/

/*
//Exercicio 3
#define MAX_CLIENTES 100
typedef struct {
    char nome [50];
    int conta;
    float saldo;
} Cliente;

typedef struct {
    Cliente clientes[MAX_CLIENTES];
    int tamanho;
} Lista;

//Essa função inicializa a lista de clientes, definindo o tamanho como 0.
void inicializar (Lista *lista) {
    lista -> tamanho = 0;
}


//Essa função retorna o número de elementos na lista.
//Ela acessa o campo "tamanho" da estrutura "Lista" e retorna seu valor.
int retornarElementos (Lista *lista) {
    return lista -> tamanho;
}


//Essa função imprime os dados de todos os clientes na lista.
//Ela percorre a lista e exibe o nome, número da conta e saldo de cada cliente.
void imprimir(Lista *lista) {
    for (int i = 0; i < lista -> tamanho; i++) {
        printf("Nome: %s, Conta: %d, Saldo: %.2f\n", lista -> clientes[i].nome, lista -> clientes[i].conta, lista -> clientes[i].saldo);
    }
}


//Essa função busca um cliente na lista com base no número da conta ou nome.
//Ela percorre a lista e retorna o índice do cliente encontrado ou -1 se não encontrado.
int buscar(Lista *lista, int conta, char *nome) {
    for (int i = 0; i < lista -> tamanho; i++) {
        if (lista -> clientes[i].conta == conta || (nome != NULL && strcmp(lista -> clientes[i].nome, nome) == 0)) {
            return i;
        }
    }
    return -1;
}


//Essa função insere um novo cliente na lista, se houver espaço disponível.
//Ela copia os dados do cliente para a lista e incrementa o tamanho.
void inserir(Lista *lista, char *nome, int conta, float saldo) {
    if (lista -> tamanho < MAX_CLIENTES) {
        strcpy(lista -> clientes[lista -> tamanho].nome, nome);
        lista -> clientes[lista -> tamanho].conta = conta;
        lista -> clientes[lista -> tamanho].saldo = saldo;
        lista -> tamanho++;
    } else {
        printf("Lista cheia. Não é possível inserir mais clientes.\n");
    }
}


//Essa função exclui um cliente da lista com base no número da conta.
//Ela busca o cliente e, se encontrado, remove-o da lista, ajustando o tamanho.
void excluir(Lista *lista, int conta) {
    int posicao = buscar(lista, conta, "");
    if (posicao != -1) {
        for (int i = posicao; i < lista -> tamanho - 1; i++) {
            lista -> clientes[i] = lista -> clientes[i + 1];
        }
        lista -> tamanho--;
    } else {
        printf("Cliente não encontrado.\n");
    }
}


//Essa função reinicializa a lista, definindo o tamanho como 0.
void reinicializar(Lista *lista) {
    lista -> tamanho = 0;
}


//Essa função coleta os dados do cliente (nome, conta e saldo) e os insere na lista.
//Ela solicita ao usuário que insira os dados e chama a função de inserção.
void dados(Lista *lista) {
    char nome[50];
    int conta;
    float saldo;

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", nome);

    printf("Digite o número da conta: ");
    scanf("%d", &conta);

    printf("Digite o saldo: ");
    scanf("%f", &saldo);

    inserir(lista, nome, conta, saldo);
}


//Essa função é o ponto de entrada do programa.
//Ela inicializa a lista e exibe um menu para o usuário interagir com as opções disponíveis.
//O loop continua até que o usuário escolha sair.
int main() {
    Lista lista;
    inicializar(&lista);

    int opcao;

    do {
        printf("\n======== Menu ========\n");
        printf("1. Inserir cliente\n");
        printf("2. Buscar cliente\n");
        printf("3. Excluir cliente\n");
        printf("4. Imprimir clientes\n");
        printf("5. Reinicializar lista\n");
        printf("6. Sair\n");
        printf("========================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados(&lista);
                break;
            case 2: {
                int conta;
                printf("Digite o número da conta: ");
                scanf("%d", &conta);
                int posicao = buscar(&lista, conta, "");
                if (posicao != -1) {
                    printf("Cliente encontrado: Nome: %s, Conta: %d, Saldo: %.2f\n", lista.clientes[posicao].nome, lista.clientes[posicao].conta, lista.clientes[posicao].saldo);
                } else {
                    printf("Cliente não encontrado.\n");
                }
                break;
            }
            case 3: {
                int conta;
                printf("Digite o número da conta a ser excluído: ");
                scanf("%d", &conta);
                excluir(&lista, conta);
                break;
            }
            case 4:
                imprimir(&lista);
                break;
            case 5:
                reinicializar(&lista);
                printf("Lista reinicializada.\n");
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
} while (opcao != 6); // Loop até o usuário escolher sair

    return 0;
}

*/