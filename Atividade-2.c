#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ALUNOS 10
#define MAX_DISCIPLINAS 5


typedef struct {
    char nome[50];
    char codigo[10];
} Disciplina;


typedef struct {
    char nome[50];
    int matricula;
    Disciplina disciplinas[MAX_DISCIPLINAS];
    int quantidadeDisciplinas;
} Aluno;


void adicionarDisciplina(Aluno* aluno, char nome[], char codigo[]) {
    if (aluno->quantidadeDisciplinas < MAX_DISCIPLINAS) {
        strcpy(aluno->disciplinas[aluno->quantidadeDisciplinas].nome, nome);
        strcpy(aluno->disciplinas[aluno->quantidadeDisciplinas].codigo, codigo);
        aluno->quantidadeDisciplinas++;
    } else {
        printf("Limite de disciplinas atingido para o aluno %s.\n", aluno->nome);
    }
}


void imprimirAluno(Aluno* aluno) {
    printf("Nome: %s\n", aluno->nome);
    printf("Matricula: %d\n", aluno->matricula);
    printf("Disciplinas:\n");
    for (int i = 0; i < aluno->quantidadeDisciplinas; i++) {
        printf("  Nome: %s, Código: %s\n", aluno->disciplinas[i].nome, aluno->disciplinas[i].codigo);
    }
}


void imprimirTodosAlunos(Aluno alunos[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        imprimirAluno(&alunos[i]);
    }
}


void ordenarAlunosPorNome(Aluno alunos[], int quantidade) {
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = i + 1; j < quantidade; j++) {
            if (strcmp(alunos[i].nome, alunos[j].nome) > 0) {
                Aluno temp = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = temp;
            }
        }
    }
}


void ordenarAlunosPorMatricula(Aluno alunos[], int quantidade) {
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = i + 1; j < quantidade; j++) {
            if (alunos[i].matricula > alunos[j].matricula) {
                Aluno temp = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = temp;
            }
        }
    }
}


void ordenarDisciplinasPorNome(Aluno* aluno) {
    for (int i = 0; i < aluno->quantidadeDisciplinas - 1; i++) {
        for (int j = i + 1; j < aluno->quantidadeDisciplinas; j++) {
            if (strcmp(aluno->disciplinas[i].nome, aluno->disciplinas[j].nome) > 0) {
                Disciplina temp = aluno->disciplinas[i];
                aluno->disciplinas[i] = aluno->disciplinas[j];
                aluno->disciplinas[j] = temp;
            }
        }
    }
}


int main() {
    Aluno alunos[MAX_ALUNOS];
    int quantidadeAlunos = 0;

    printf("Quantos alunos deseja cadastrar (máximo %d)? ", MAX_ALUNOS);
    scanf("%d", &quantidadeAlunos);
    if (quantidadeAlunos > MAX_ALUNOS) quantidadeAlunos = MAX_ALUNOS;

    for (int i = 0; i < quantidadeAlunos; i++) {
        printf("\nDigite o nome do aluno %d: ", i + 1);
        scanf(" %[^\n]", alunos[i].nome);
        printf("Digite a matrícula do aluno %d: ", i + 1);
        scanf("%d", &alunos[i].matricula);
        alunos[i].quantidadeDisciplinas = 0;

        int quantidadeDisciplinas;
        printf("Quantas disciplinas o aluno %s está cursando (máximo %d)? ", alunos[i].nome, MAX_DISCIPLINAS);
        scanf("%d", &quantidadeDisciplinas);
        if (quantidadeDisciplinas > MAX_DISCIPLINAS) quantidadeDisciplinas = MAX_DISCIPLINAS;

        for (int j = 0; j < quantidadeDisciplinas; j++) {
            char nomeDisciplina[50], codigoDisciplina[10];
            printf("Digite o nome da disciplina %d: ", j + 1);
            scanf(" %[^\n]", nomeDisciplina);
            printf("Digite o código da disciplina %d: ", j + 1);
            scanf(" %s", codigoDisciplina);
            adicionarDisciplina(&alunos[i], nomeDisciplina, codigoDisciplina);
        }
    }

    
    printf("\n--- Alunos ordenados por nome ---\n");
    ordenarAlunosPorNome(alunos, quantidadeAlunos);
    imprimirTodosAlunos(alunos, quantidadeAlunos);

    
    printf("\n--- Alunos ordenados por matrícula ---\n");
    ordenarAlunosPorMatricula(alunos, quantidadeAlunos);
    imprimirTodosAlunos(alunos, quantidadeAlunos);


    printf("\n--- Disciplinas ordenadas por nome ---\n");
    for (int i = 0; i < quantidadeAlunos; i++) {
        ordenarDisciplinasPorNome(&alunos[i]);
        imprimirAluno(&alunos[i]);
    }

    return 0;
}