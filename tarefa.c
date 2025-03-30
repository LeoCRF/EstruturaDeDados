#include <stdio.h>
#include <string.h>


int main() {
    // exercicio 1
    /*
    int numero;

    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);

    if (numero % 2 == 0) {
        printf("O numero %d é par.\n", numero);
    } else {
        printf("O numero %d é ímpar.\n", numero);
    }
    */

    // exercicio 2
    /*
    int numero;

    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);

    if (numero > 0) {
        printf("O numero %d é positivo.\n", numero);
    } else if (numero < 0) {
        printf("O numero %d é negativo.\n", numero);
    } else {
        printf("O numero é zero.\n");
    }
*/
// exercicio 3
/*
char letra;

    printf("Digite uma letra: ");
    fflush(stdout); 

    
    scanf(" %c", &letra); 

    
    if (letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u' ||
        letra == 'A' || letra == 'E' || letra == 'I' || letra == 'O' || letra == 'U') {
        printf("A letra '%c' é uma vogal.\n", letra);
    } else {
        printf("A letra '%c' é uma consoante.\n", letra);
    }
*/


// exercicio 4
/*
    int quantidade, regiao;
    float valor_unnitario = 5.0, total_compra, frete, total_com_frete;

    printf("Digite a quantidade de itens (1 a 100): ");
    scanf("%d", &quantidade);

    if (quantidade < 1 || quantidade > 100) {
        printf("Quantidade inválida. Deve ser entre 1 e 100.\n");
        return 1;
    }

    printf("Digite o código da região (1- Norte, 2-Nordeste, 3- Centro-Oeste, 4- Sudeste, 5- Sul): ");
    scanf("%d", &regiao);

    total_compra = quantidade * valor_unnitario;

    switch (regiao) {
        case 1:
            frete = total_compra * 0.10;
            break;
        case 2:
            frete = total_compra * 0.08;
            break;
        case 3:
            frete = total_compra * 0.12;
            break;
        case 4:
            frete = total_compra * 0.15;
            break;
        case 5:
            frete = total_compra * 0.11;
            break;
        default:
            printf("Região inválida.\n");
            return 1;
    }

    total_com_frete = total_compra + frete;

    printf("Total sem frete: R$ %.2f\n", total_compra);
    printf("Frete: R$ %.2f\n", frete);
    printf("Total com frete: R$ %.2f\n", total_com_frete);
*/

// exercicio 5
    int opcao;
    char nome_conjuge[100], cidade[100], sexo;
    int idade, quantidade_filhos, idade_mais_velho;
    float salario;

    printf("Digite sua situação civil:\n");
    printf("1 - Solteiro(a)\n");
    printf("2 - Casado(a)\n");
    printf("3 - Divorciado(a)\n");
    printf("4 - Viúvo(a)\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: //Solteiro
            printf("Digite sua idade: ");
            scanf("%d", &idade);
            printf("Solteiro(a)\n");
            printf("Idade: %d\n", idade);
            break;
        case 2: //Casado
            printf("Digite o sexo (M/F): ");
            scanf(" %c", &sexo);
            printf("Digite o nome do cônjuge: ");
            scanf(" %[^\n]", nome_conjuge);
            printf("Casado(a)\n");
            printf("Sexo: %c\n", sexo);
            printf("Nome do cônjuge: %s\n", nome_conjuge);
            break;
        case 3: //Divorciado
            printf("Digite a quantidade de filhos (0 caso não tenha filhos): ");
            scanf("%d", &quantidade_filhos);
            if (quantidade_filhos > 0) {
                printf("Digite a idade do filho mais velho: ");
                scanf("%d", &idade_mais_velho);
            } else {
                idade_mais_velho = 0;
            }
            printf("Divorciado(a)\n");
            printf("Quantidade de filhos: %d\n", quantidade_filhos);
            if (quantidade_filhos > 0) {
                printf("Idade do filho mais velho: %d\n", idade_mais_velho);
            }
            break;
        case 4: //Viúvo
            printf("Digite o nome da cidade onde mora: ");
            scanf(" %[^\n]", cidade);
            printf("Digite o salário: ");
            scanf("%f", &salario);
            printf("Viúvo(a)\n");
            printf("Cidade: %s\n", cidade);
            printf("Salário: R$%.2f\n", salario);
            break;

        default:
            printf("Opção inválida Digite.\n");
            return 1;
        }

    return 0;
}