/*
// Exercicio 1: Lista Ligada Simples
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ALUNOS 100 
#define MAX_DISCIPLINAS 10 
#define INVALIDO -1

// Estrutura para Disciplina
typedef struct {
    char nome[50];
    char codigo[10];
    char turma[5];
} Disciplina;

// Estrutura para Aluno
typedef struct {
    char nome[50];
    int matricula;
    Disciplina disciplinas[MAX_DISCIPLINAS];
    int numDisciplinas;
} Aluno;

// Estrutura para o "nó" da lista
typedef struct {
    Aluno aluno;
    int proximo;
} No;

// Estrutura para a Lista Ligada
typedef struct {
    No elementos[MAX_ALUNOS];
    int inicio;
    int disponivel;
} Lista;

// Inicializar a lista
void Inicializar_Lista(Lista *L) {
    L->inicio = INVALIDO;
    L->disponivel = 0;
    for (int i = 0; i < MAX_ALUNOS - 1; i++) {
        L->elementos[i].proximo = i + 1;
    }
    L->elementos[MAX_ALUNOS - 1].proximo = INVALIDO;
}

// Obter um nó disponível
int Obtencao_do_NO(Lista *L) {
    int resultado = L->disponivel;
    if (L->disponivel != INVALIDO) {
        L->disponivel = L->elementos[L->disponivel].proximo;
    }
    return resultado;
}

// Devolver um nó para a lista de disponíveis
void Devolver_No_Disponivel_Lista(Lista *L, int i) {
    L->elementos[i].proximo = L->disponivel;
    L->disponivel = i;
}

// Inserir um aluno na lista (ordenado por matrícula)
bool Inserir_Aluno(Lista *L, Aluno novoAluno) {
    int novoNo = Obtencao_do_NO(L);
    if (novoNo == INVALIDO) {
        return false; // Lista cheia
    }

    L->elementos[novoNo].aluno = novoAluno;
    int anterior = INVALIDO;
    int atual = L->inicio;

    while (atual != INVALIDO && L->elementos[atual].aluno.matricula < novoAluno.matricula) {
        anterior = atual;
        atual = L->elementos[atual].proximo;
    }

    L->elementos[novoNo].proximo = atual;
    if (anterior == INVALIDO) {
        L->inicio = novoNo;
    } else {
        L->elementos[anterior].proximo = novoNo;
    }
    return true;
}

// Buscar aluno por matrícula
int Buscar_Aluno(Lista *L, int matricula) {
    int atual = L->inicio;
    while (atual != INVALIDO && L->elementos[atual].aluno.matricula != matricula) {
        atual = L->elementos[atual].proximo;
    }
    return atual; // Retorna o índice do aluno ou INVALIDO se não encontrado
}

// Excluir aluno por matrícula
bool Excluir_Aluno(Lista *L, int matricula) {
    int anterior = INVALIDO;
    int atual = L->inicio;

    while (atual != INVALIDO && L->elementos[atual].aluno.matricula != matricula) {
        anterior = atual;
        atual = L->elementos[atual].proximo;
    }

    if (atual == INVALIDO) {
        return false; // Aluno não encontrado
    }

    if (anterior == INVALIDO) {
        L->inicio = L->elementos[atual].proximo;
    } else {
        L->elementos[anterior].proximo = L->elementos[atual].proximo;
    }

    Devolver_No_Disponivel_Lista(L, atual);
    return true;
}

// Adicionar disciplina ao aluno
bool Adicionar_Disciplina(Lista *L, int matricula, Disciplina disciplina) {
    int alunoIndex = Buscar_Aluno(L, matricula);
    if (alunoIndex == INVALIDO) {
        return false; // Aluno não encontrado
    }
    if (L->elementos[alunoIndex].aluno.numDisciplinas < MAX_DISCIPLINAS) {
        L->elementos[alunoIndex].aluno.disciplinas[L->elementos[alunoIndex].aluno.numDisciplinas] = disciplina;
        L->elementos[alunoIndex].aluno.numDisciplinas++;
        return true;
    } else {
        return false;
    }
}

// Função auxiliar para comparar alunos
int compararAlunosPorMatricula(const void *a, const void *b) {
    int matriculaA = ((No *)a)->aluno.matricula;
    int matriculaB = ((No *)b)->aluno.matricula;
    return matriculaA - matriculaB;
}

int compararAlunosPorNome(const void *a, const void *b) {
    return strcmp(((No *)a)->aluno.nome, ((No *)b)->aluno.nome);
}

int compararDisciplinasPorNome(const void *a, const void *b) {
    return strcmp(((Disciplina *)a)->nome, ((Disciplina *)b)->nome);
}

int compararDisciplinasPorCodigo(const void *a, const void *b) {
    return strcmp(((Disciplina *)a)->codigo, ((Disciplina *)b)->codigo);
}

// Imprimir alunos por turma (opcional, necessita da lógica de turmas)
void Imprimir_Alunos_Por_Turma(Lista *L, char turma[]) {
    printf("\nAlunos da Turma %s:\n", turma);
    No tempAlunos[MAX_ALUNOS];
    int count = 0;
    int atual = L->inicio;

    while (atual != INVALIDO) {
        for (int i = 0; i < L->elementos[atual].aluno.numDisciplinas; i++){
            if (strcmp(L->elementos[atual].aluno.disciplinas[i].turma, turma) == 0){
                tempAlunos[count] = L->elementos[atual];
                count++;
                break;
            }
        }
        atual = L->elementos[atual].proximo;
    }

    // Ordenar por nome
    qsort(tempAlunos, count, sizeof(No), compararAlunosPorNome);

    for (int i = 0; i < count; i++) {
        printf("  - %s (Matrícula: %d)\n", tempAlunos[i].aluno.nome, tempAlunos[i].aluno.matricula);
    }
}

// Imprimir todos os alunos
void Imprimir_Todos_Alunos(Lista *L, bool ordenarPorMatricula) {
    printf("\nLista de Todos os Alunos:\n");
    No tempAlunos[MAX_ALUNOS];
    int count = 0;
    int atual = L->inicio;

    while (atual != INVALIDO) {
        tempAlunos[count] = L->elementos[atual];
        count++;
        atual = L->elementos[atual].proximo;
    }

    if (ordenarPorMatricula) {
        qsort(tempAlunos, count, sizeof(No), compararAlunosPorMatricula);
    } else {
        qsort(tempAlunos, count, sizeof(No), compararAlunosPorNome);
    }

    for (int i = 0; i < count; i++) {
        printf("  - %s (Matrícula: %d)\n", tempAlunos[i].aluno.nome, tempAlunos[i].aluno.matricula);
    }
}

// Imprimir informações de um aluno específico
void Imprimir_Aluno(Lista *L, int matricula, char nome[], bool buscarPorMatricula, bool ordenarDisciplinasPorCodigo) {
    int alunoIndex = INVALIDO;
    if (buscarPorMatricula) {
        alunoIndex = Buscar_Aluno(L, matricula);
    } else {
        int atual = L->inicio;
        while (atual != INVALIDO && strcmp(L->elementos[atual].aluno.nome, nome) != 0) {
            atual = L->elementos[atual].proximo;
        }
        alunoIndex = atual;
    }

    if (alunoIndex == INVALIDO) {
        printf("\nAluno não encontrado.\n");
        return;
    }

    printf("\nInformações do Aluno:\n");
    printf("  - Nome: %s\n", L->elementos[alunoIndex].aluno.nome);
    printf("  - Matrícula: %d\n", L->elementos[alunoIndex].aluno.matricula);
    printf("  - Disciplinas:\n");

    if (L->elementos[alunoIndex].aluno.numDisciplinas > 0) {
        // Criar um array temporário de disciplinas para ordenar
        Disciplina tempDisciplinas[MAX_DISCIPLINAS];
        for (int i = 0; i < L->elementos[alunoIndex].aluno.numDisciplinas; i++) {
            tempDisciplinas[i] = L->elementos[alunoIndex].aluno.disciplinas[i];
        }

        if (ordenarDisciplinasPorCodigo) {
            qsort(tempDisciplinas, L->elementos[alunoIndex].aluno.numDisciplinas, sizeof(Disciplina), compararDisciplinasPorCodigo);
        } else {
            qsort(tempDisciplinas, L->elementos[alunoIndex].aluno.numDisciplinas, sizeof(Disciplina), compararDisciplinasPorNome);
        }

        for (int i = 0; i < L->elementos[alunoIndex].aluno.numDisciplinas; i++) {
            printf("    - %s (%s)\n", tempDisciplinas[i].nome, tempDisciplinas[i].codigo);
        }
    } else {
        printf("    Nenhuma disciplina cadastrada.\n");
    }
}

// Buscar alunos por disciplina
void Buscar_Alunos_Por_Disciplina(Lista *L, char nomeDisciplina[]) {
    printf("\nAlunos matriculados em %s:\n", nomeDisciplina);
    int atual = L->inicio;
    bool encontrado = false;

    while (atual != INVALIDO) {
        for (int i = 0; i < L->elementos[atual].aluno.numDisciplinas; i++) {
            if (strcmp(L->elementos[atual].aluno.disciplinas[i].nome, nomeDisciplina) == 0) {
                printf("  - %s (Matrícula: %d)\n", L->elementos[atual].aluno.nome, L->elementos[atual].aluno.matricula);
                encontrado = true;
                break;
            }
        }
        atual = L->elementos[atual].proximo;
    }

    if (!encontrado) {
        printf("  Nenhum aluno encontrado matriculado nesta disciplina.\n");
    }
}

int main() {
    Lista listaAlunos;
    Inicializar_Lista(&listaAlunos);

    int opcao;
    do {
        printf("\n--- Sistema de Gestão de Alunos ---\n");
        printf("1. Inserir Aluno\n");
        printf("2. Buscar Aluno por Matrícula\n");
        printf("3. Excluir Aluno\n");
        printf("4. Adicionar Disciplina ao Aluno\n");
        printf("5. Imprimir Todos os Alunos\n");
        printf("6. Imprimir Aluno\n");
        printf("7. Buscar Alunos por Disciplina\n");
        printf("8. Imprimir Alunos por Turma\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Aluno novoAluno;
                printf("Nome do Aluno: ");
                scanf(" %[^\n]s", novoAluno.nome);
                printf("Matrícula: ");
                scanf("%d", &novoAluno.matricula);
                novoAluno.numDisciplinas = 0;
                if (Inserir_Aluno(&listaAlunos, novoAluno)) {
                    printf("Aluno inserido com sucesso.\n");
                } else {
                    printf("Erro ao inserir aluno (lista cheia).\n");
                }
                break;
            }
            case 2: {
                int matricula;
                printf("Matrícula do Aluno a ser buscado: ");
                scanf("%d", &matricula);
                int alunoIndex = Buscar_Aluno(&listaAlunos, matricula);
                if (alunoIndex != INVALIDO) {
                    printf("Aluno encontrado: %s\n", listaAlunos.elementos[alunoIndex].aluno.nome);
                } else {
                    printf("Aluno não encontrado.\n");
                }
                break;
            }
            case 3: {
                int matricula;
                printf("Matrícula do Aluno a ser excluído: ");
                scanf("%d", &matricula);
                if (Excluir_Aluno(&listaAlunos, matricula)) {
                    printf("Aluno excluído com sucesso.\n");
                } else {
                    printf("Aluno não encontrado.\n");
                }
                break;
            }
            case 4: {
                int matricula;
                Disciplina novaDisciplina;
                printf("Matrícula do Aluno: ");
                scanf("%d", &matricula);
                printf("Nome da Disciplina: ");
                scanf(" %[^\n]s", novaDisciplina.nome);
                printf("Código da Disciplina: ");
                scanf(" %[^\n]s", novaDisciplina.codigo);
                printf("Turma da Disciplina: ");
                scanf(" %[^\n]s", novaDisciplina.turma);
                if (Adicionar_Disciplina(&listaAlunos, matricula, novaDisciplina)) {
                    printf("Disciplina adicionada com sucesso.\n");
                } else {
                    printf("Erro ao adicionar disciplina.\n");
                }
                break;
            }
            case 5: {
                int ordenarPor;
                printf("Ordenar por (1 - Matrícula, 2 - Nome): ");
                scanf("%d", &ordenarPor);
                Imprimir_Todos_Alunos(&listaAlunos, ordenarPor == 1);
                break;
            }
            case 6: {
                int buscarPor;
                printf("Buscar por (1 - Matrícula, 2 - Nome): ");
                scanf("%d", &buscarPor);
                if (buscarPor == 1) {
                    int matricula;
                    printf("Matrícula do Aluno: ");
                    scanf("%d", &matricula);
                    int ordenarDisciplinas;
                    printf("Ordenar disciplinas por (1 - Código, 2 - Nome): ");
                    scanf("%d", &ordenarDisciplinas);
                    Imprimir_Aluno(&listaAlunos, matricula, "", true, ordenarDisciplinas == 1);
                } else {
                    char nome[50];
                    printf("Nome do Aluno: ");
                    scanf(" %[^\n]s", nome);
                    int ordenarDisciplinas;
                    printf("Ordenar disciplinas por (1 - Código, 2 - Nome): ");
                    scanf("%d", &ordenarDisciplinas);
                    Imprimir_Aluno(&listaAlunos, 0, nome, false, ordenarDisciplinas == 1);
                }
                break;
            }
            case 7: {
                char nomeDisciplina[50];
                printf("Nome da Disciplina: ");
                scanf(" %[^\n]s", nomeDisciplina);
                Buscar_Alunos_Por_Disciplina(&listaAlunos, nomeDisciplina);
                break;
            }
            case 8: {
                char turma[5];
                printf("Nome da Turma: ");
                scanf(" %[^\n]s", turma);
                Imprimir_Alunos_Por_Turma(&listaAlunos, turma);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}

// Exercício 2: Lista Duplamente Encadeada

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
    
    // Definindo o tipo para a chave
    typedef int Tipo_Chave;
    
    // Estrutura para os dados (Registro)
    typedef struct {
        Tipo_Chave chave;
        // Outros dados, se necessário
        int valor;
        char nome[50];
        bool novoCliente;
    } Registro;
    
    // Estrutura para o nó da lista duplamente encadeada
    typedef struct Aux_Elemento {
        struct Aux_Elemento *anterior;
        Registro r;
        struct Aux_Elemento *proximo;
    } Elemento;
    
    // Definindo um ponteiro para Elemento
    typedef Elemento *PONT;
    
    // Estrutura para a Lista Duplamente Encadeada
    typedef struct {
        PONT inicio;
    } Lista;
    
    // Inicializar a lista
    void Inicializar_Lista(Lista *lista) {
        lista->inicio = NULL;
    }
    
    // Retornar o número de elementos
    int Retornar_Numero_Elementos(Lista *lista) {
        int contador = 0;
        PONT atual = lista->inicio;
        while (atual != NULL) {
            contador++;
            atual = atual->proximo;
        }
        return contador;
    }
    
    // Imprimir a lista
    void Imprimir(Lista *lista) {
        PONT atual = lista->inicio;
        printf("Lista: ");
        while (atual != NULL) {
            printf("%d ", atual->r.chave);
            atual = atual->proximo;
        }
        printf("\n");
    }
    
    // Buscar um elemento na lista
    PONT Buscar(Lista *lista, Tipo_Chave chave) {
        PONT atual = lista->inicio;
        while (atual != NULL) {
            if (atual->r.chave == chave) {
                return atual;
            }
            atual = atual->proximo;
        }
        return NULL;
    }
    
    // Inserir um elemento no início da lista
    bool Inserir(Lista *lista, Registro registro) {
        PONT novo = (PONT)malloc(sizeof(Elemento));
        if (novo == NULL) return false;
    
        novo->r = registro;
        novo->anterior = NULL;
        novo->proximo = lista->inicio;
    
        if (lista->inicio != NULL) {
            lista->inicio->anterior = novo;
        }
    
        lista->inicio = novo;
        return true;
    }
    
    // Excluir um elemento da lista
    bool Excluir(Lista *lista, Tipo_Chave chave) {
        PONT atual = lista->inicio;
        PONT paraExcluir = NULL;
    
        while (atual != NULL) {
            if (atual->r.chave == chave) {
                paraExcluir = atual;
                break;
            }
            atual = atual->proximo;
        }
    
        if (paraExcluir == NULL) return false;
    
        if (paraExcluir->anterior != NULL) {
            paraExcluir->anterior->proximo = paraExcluir->proximo;
        } else {
            lista->inicio = paraExcluir->proximo;
        }
    
        if (paraExcluir->proximo != NULL) {
            paraExcluir->proximo->anterior = paraExcluir->anterior;
        }
    
        free(paraExcluir);
        return true;
    }
    
    // Reinicializar a lista (esvaziar)
    void Reinicializar_Lista(Lista *lista) {
        PONT atual = lista->inicio;
        PONT proximo;
        while (atual != NULL) {
            proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        lista->inicio = NULL;
    }
    
    // Exercício 2: Lista Duplamente Encadeada Circular
    
    // Excluir
    bool Excluir_Circular(Lista *lista, Tipo_Chave chave) {
        if (lista->inicio == NULL) return false; // Lista vazia
    
        PONT atual = lista->inicio;
        PONT paraExcluir = NULL;
    
        if (lista->inicio->proximo == lista->inicio && lista->inicio->r.chave == chave) { // Único nó
            free(lista->inicio);
            lista->inicio = NULL;
            return true;
        }
    
        do {
            if (atual->r.chave == chave) {
                paraExcluir = atual;
                break;
            }
            atual = atual->proximo;
        } while (atual != lista->inicio);
    
        if (paraExcluir == NULL) return false; // Não encontrado
    
        PONT anterior = paraExcluir->anterior;
        PONT proximo = paraExcluir->proximo;
    
        anterior->proximo = proximo;
        proximo->anterior = anterior;
    
        if (paraExcluir == lista->inicio) {
            lista->inicio = proximo;
        }
    
        free(paraExcluir);
        return true;
    }
    
    // Exercício 3: Inserções Específicas
    
    // Inserir no fim da lista
    bool Inserir_Fim(Lista *lista, Registro registro) {
        PONT novo = (PONT)malloc(sizeof(Elemento));
        if (novo == NULL) return false;
    
        novo->r = registro;
        novo->proximo = NULL;
    
        if (lista->inicio == NULL) {
            novo->anterior = NULL;
            lista->inicio = novo;
        } else {
            PONT atual = lista->inicio;
            while (atual->proximo != NULL) {
                atual = atual->proximo;
            }
            atual->proximo = novo;
            novo->anterior = atual;
        }
        return true;
    }
    
    // Inserir no meio (após um nó com uma chave específica)
    bool Inserir_Meio(Lista *lista, Tipo_Chave chave, Registro registro) {
        PONT novo = (PONT)malloc(sizeof(Elemento));
        if (novo == NULL) return false;
    
        novo->r = registro;
    
        PONT atual = lista->inicio;
        while (atual != NULL && atual->r.chave != chave) {
            atual = atual->proximo;
        }
    
        if (atual == NULL) {
            free(novo);
            return false; // Nó com a chave não encontrado
        }
    
        novo->proximo = atual->proximo;
        novo->anterior = atual;
        if (atual->proximo != NULL) {
            atual->proximo->anterior = novo;
        }
        atual->proximo = novo;
        return true;
    }
    
    // Exercício 4: Soma de Pares
    int Somar_Pares(Lista *lista) {
        int soma = 0;
        PONT atual = lista->inicio;
        while (atual != NULL) {
            if (atual->r.chave % 2 == 0) {
                soma += atual->r.chave;
            }
            atual = atual->proximo;
        }
        return soma;
    }
    
    // Exercício 5: Média de Valores
    float Calcular_Media(Lista *lista) {
        if (lista->inicio == NULL) return 0.0;
    
        float soma = 0;
        int contador = 0;
        PONT atual = lista->inicio;
        while (atual != NULL) {
            soma += atual->r.valor;
            contador++;
            atual = atual->proximo;
        }
        return soma / contador;
    }
    
    // Exercício 6: Imprimir Nomes com Letra Inicial
    void Imprimir_Nomes_Com_Letra(Lista *lista, char letra) {
        printf("Nomes começando com '%c':\n", letra);
        PONT atual = lista->inicio;
        while (atual != NULL) {
            if (atual->r.nome[0] == letra) {
                printf("- %s\n", atual->r.nome);
            }
            atual = atual->proximo;
        }
    }
    
    // Exercício 7: Imprimir do Último ao Primeiro
    void Imprimir_Inverso(Lista *lista) {
        if (lista->inicio == NULL) return;
    
        PONT atual = lista->inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
    
        printf("Lista Inversa: ");
        while (atual != NULL) {
            printf("%d ", atual->r.chave);
            atual = atual->anterior;
        }
        printf("\n");
    }
    
    // Exercício 8: Imprimir em Ordem Alfabética
    void Imprimir_Em_Ordem_Alfabetica(Lista *lista) {
        if (lista->inicio == NULL) return;
    
        // Criar um array temporário para armazenar os nós
        PONT atual = lista->inicio;
        PONT temp[100];
        int count = 0;
    
        while (atual != NULL) {
            temp[count++] = atual;
            atual = atual->proximo;
        }
    
        // Ordenar o array temporário
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (strcmp(temp[j]->r.nome, temp[j + 1]->r.nome) > 0) {
                    PONT swap = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = swap;
                }
            }
        }
    
        printf("Lista em Ordem Alfabética:\n");
        for (int i = 0; i < count; i++) {
            printf("- %s\n", temp[i]->r.nome);
        }
    }
    
    // Exercício 9: Imprimir Novos Clientes
    void Imprimir_Novos_Clientes(Lista *lista) {
        printf("Novos Clientes:\n");
        PONT atual = lista->inicio;
        while (atual != NULL) {
            if (atual->r.novoCliente) {
                printf("- %s\n", atual->r.nome);
            }
            atual = atual->proximo;
        }
    }
    
    // Função main com exemplos de uso
    int main() {
        Lista minhaLista;
        Inicializar_Lista(&minhaLista);
    
        // Exemplos de uso das funções
        Inserir(&minhaLista, (Registro) {10, 5, "ClienteA", false});
        Inserir(&minhaLista, (Registro) {20, 10, "ClienteB", true});
        Inserir(&minhaLista, (Registro) {30, 15, "ClienteC", false});
        Inserir_Fim(&minhaLista, (Registro) {40, 20, "ClienteD", true});
        Inserir_Meio(&minhaLista, 20, (Registro) {25, 12, "ClienteE", false});
    
        Imprimir(&minhaLista);
    
        printf("Soma dos pares: %d\n", Somar_Pares(&minhaLista));
        printf("Média dos valores: %.2f\n", Calcular_Media(&minhaLista));
    
        Imprimir_Nomes_Com_Letra(&minhaLista, 'C');
        Imprimir_Inverso(&minhaLista);
        Imprimir_Em_Ordem_Alfabetica(&minhaLista);
        Imprimir_Novos_Clientes(&minhaLista);
    
        return 0;
    }

