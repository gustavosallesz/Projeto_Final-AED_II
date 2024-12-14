#include "FuncPucTeca.h"


void adicionarLivro(Livro **head, int id, const char *nome, const char *genero) {
    Livro *novo = (Livro*)malloc(sizeof(Livro));
    novo->id = id;
    strcpy(novo->nome, nome);
    strcpy(novo->genero, genero);
    novo->prox = *head;
    *head = novo;
}

void removerLivro(Livro **head, int id) {
    Livro *temp = *head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->prox;
    }
    if (temp == NULL) {
        printf("Livro não encontrado!\n");
        return;
    }
    if (prev == NULL) {
        *head = temp->prox;
    } else {
        prev->prox = temp->prox;
    }
    free(temp);
    printf("Livro removido com sucesso!\n");
}

void listarLivros(Livro *head) {
    Livro *temp = head;
    while (temp != NULL) {
        printf("ID: %d, Nome: %s, Gênero: %s\n", temp->id, temp->nome, temp->genero);
        temp = temp->prox;
    }
}

void salvarLivros(Livro *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    Livro *temp = head;
    while (temp != NULL) {
        fprintf(file, "%d;%s;%s\n", temp->id, temp->nome, temp->genero);
        temp = temp->prox;
    }
    fclose(file);
}

Livro* carregarLivros(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    Livro *head = NULL;
    char linha[100], *nome, *genero;
    int id;

    while (fgets(linha, sizeof(linha), file) != NULL) {
        linha[strcspn(linha, "\n")] = '\0'; // Remove newline
        id = atoi(strtok(linha, ";"));
        nome = strtok(NULL, ";");
        genero = strtok(NULL, ";");
        adicionarLivro(&head, id, nome, genero);
    }

    fclose(file);
    return head;
}

int gerarID(Livro *head) {
    int id = 1;
    Livro *temp = head;
    while (temp != NULL) {
        if (temp->id >= id) {
            id = temp->id + 1;
        }
        temp = temp->prox;
    }
    return id;
}

void buscarLivroPorNome(Livro *head, const char *nome) {
    Livro *temp = head;
    int encontrado = 0;
    while (temp != NULL) {
        if (strcmp(temp->nome, nome) == 0) {
            printf("ID: %d, Nome: %s, Gênero: %s\n", temp->id, temp->nome, temp->genero);
            encontrado = 1;
        }
        temp = temp->prox;
    }
    if (!encontrado) {
        printf("Nenhum livro encontrado com o nome '%s'\n", nome);
    }
}

void buscarLivroPorGenero(Livro *head, const char *genero) {
    Livro *temp = head;
    int encontrado = 0;
    while (temp != NULL) {
        if (strcmp(temp->genero, genero) == 0) {
            printf("ID: %d, Nome: %s, Gênero: %s\n", temp->id, temp->nome, temp->genero);
            encontrado = 1;
        }
        temp = temp->prox;
    }
    if (!encontrado) {
        printf("Nenhum livro encontrado no gênero '%s'\n", genero);
    }
}

void ordenarLivrosPorNome(Livro **head) {
    if (*head == NULL || (*head)->prox == NULL) {
        return;
    }

    Livro *sorted = NULL;

    while (*head != NULL) {
        Livro *current = *head;
        *head = (*head)->prox;

        if (sorted == NULL || strcmp(current->nome, sorted->nome) < 0) {
            current->prox = sorted;
            sorted = current;
        } else {
            Livro *temp = sorted;
            while (temp->prox != NULL && strcmp(current->nome, temp->prox->nome) >= 0) {
                temp = temp->prox;
            }
            current->prox = temp->prox;
            temp->prox = current;
        }
    }

    *head = sorted;
}

void ordenarLivrosPorGenero(Livro **head) {
    if (*head == NULL || (*head)->prox == NULL) {
        return;
    }

    Livro *sorted = NULL;

    while (*head != NULL) {
        Livro *current = *head;
        *head = (*head)->prox;

        if (sorted == NULL || strcmp(current->genero, sorted->genero) < 0) {
            current->prox = sorted;
            sorted = current;
        } else {
            Livro *temp = sorted;
            while (temp->prox != NULL && strcmp(current->genero, temp->prox->genero) >= 0) {
                temp = temp->prox;
            }
            current->prox = temp->prox;
            temp->prox = current;
        }
    }

    *head = sorted;
}
