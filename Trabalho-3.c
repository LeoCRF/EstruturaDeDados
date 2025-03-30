#include <stdio.h>


//Exercicio 1
/*
int s(int n) {
    if (n == 0) {
        return 1;
    } else {
        return 2 * s(n - 1) + 1;
    }
}

int main() {
    int n;
    printf("Digite um numero inteiro: ");
    scanf("%d", &n);

    printf("O resultado da função s(%d) é: %d\n", n, s(n));

    return 0;
}
    */

    //Exercicio 2
    /*
int s(int n) {
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return 2;
    } else {
        return 2 * s(n - 1) - 3 * s(n - 2);
    }
}

int main() {
    int n;

    printf("Digite um numero inteiro: ");
    scanf("%d", &n);

    printf("O resultado da função s(%d) é: %d\n", n, s(n));
    return 0;
}
*/

//Exercicio 3
/*
int s(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else if (n % 2 == 0) {
        return 2 * s(n - 1) - s(n - 2);
    } else {
        return s(n - 1) - 2 * s(n - 2);
    }
}

int main () {
    int n;

    printf("Digite um numero inteiro: ");
    scanf("%d", &n);

    printf("O resultado da função s(%d) é: %d\n", n, s(n));
    return 0;
}
*/