#include "FuncForca.h"


#define MAX_TENTATIVAS 6

void ortografia() {
    setlocale(LC_ALL, "Portuguese");
}

// Função que desenha a forca com base no número de erros
void desenhaForca(int tentativasRestantes) {
    int erros = MAX_TENTATIVAS - tentativasRestantes;

    printf("\n==== Forca ====\n");
    printf("   _______\n");
    printf("  |       |\n");
    printf("  |       %s\n", erros > 0 ? "O" : " ");
    printf("  |      %s%s%s\n", erros > 2 ? "/" : " ", erros > 1 ? "|" : " ", erros > 3 ? "\\" : " ");
    printf("  |      %s %s\n", erros > 4 ? "/" : " ", erros > 5 ? "\\" : " ");
    printf("  |\n");
    printf("__|__\n\n");
}

// Função para carregar as palavras do arquivo para a lista
void carregaPalavras(Palavra **lista) {
    FILE *arquivo = fopen("palavras.txt", "r");
    if (!arquivo) {
        printf("Arquivo de palavras nao encontrado. Criando novo...\n");
        arquivo = fopen("palavras.txt", "w");  // Se o arquivo não abrir, criamos um novo
        fclose(arquivo);
        return;
    }

    char linha[150];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0'; // Remove o '\n', caso exista
        char *dica = strtok(linha, ";");    // Divide a linha pelo ";"
        char *palavra = strtok(NULL, ";");
        if (dica && palavra) {
            adicionaPalavra(lista, palavra, dica);
        }
    }

    fclose(arquivo);
}

// Salva as palavras no arquivo
void salvaPalavras(Palavra *lista) {
    FILE *arquivo = fopen("palavras.txt", "w");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo para salvar");
        return;
    }

    Palavra *atual = lista;
    while (atual) {
        fprintf(arquivo, "%s;%s\n", atual->dica, atual->palavra);
        atual = atual->prox;
    }

    fclose(arquivo);
    printf("\nPalavras salvas com sucesso!\n");
}

// Adiciona uma nova palavra à lista
void adicionaPalavra(Palavra **lista, const char *palavra, const char *dica) {
    Palavra *nova = (Palavra *)malloc(sizeof(Palavra));
    if (!nova) {
        perror("Erro ao alocar memoria");
        return;
    }

    strcpy(nova->palavra, palavra);
    strcpy(nova->dica, dica);
    nova->prox = NULL;

    if (*lista == NULL) {
        *lista = nova;
    } else {
        Palavra *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = nova;
    }
}

// Exibe todas as palavras da lista (não vale trapacear hein"
void exibePalavras(Palavra *lista) {
    printf("\n=== LISTA DE PALAVRAS ===\n");
    Palavra *atual = lista;
    while (atual) {
        printf("Palavra: %s | Dica: %s\n", atual->palavra, atual->dica);
        atual = atual->prox;
    }
}

// Remove uma palavra da lista
void removePalavra(Palavra **lista, const char *palavra) {
    Palavra *atual = *lista;
    Palavra *anterior = NULL;

    while (atual != NULL && strcmp(atual->palavra, palavra) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("\nPalavra '%s' nao encontrada!\n", palavra);
        return;
    }

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("\nPalavra '%s' removida com sucesso!\n", palavra);
    salvaPalavras(*lista);
}

// Libera a memória alocada para a lista
void limpaLista(Palavra *lista) {
    Palavra *atual;
    while (lista) {
        atual = lista;
        lista = lista->prox;
        free(atual);
    }
}

// Função principal do jogo
void jogo(Palavra *lista) {
    if (!lista) {
        printf("\nNenhuma palavra cadastrada!\n");
        return;
    }

    Palavra *atual = lista;
    int total = 0;
    while (atual) {
        total++;
        atual = atual->prox;
    }

    int i = rand() % total;
    atual = lista;
    while (i-- && atual) {
        atual = atual->prox;
    }

    char *palavra = atual->palavra;
    char *dica = atual->dica;
    char tentativa[strlen(palavra) + 1];
    for (int i = 0; i < strlen(palavra); i++) {
        tentativa[i] = '_';
    }
    tentativa[strlen(palavra)] = '\0';

    int tentativasRestantes = MAX_TENTATIVAS, acertos = 0, tamanhoPalavra = strlen(palavra);
    printf("\nDica: %s\n", dica);

    while (tentativasRestantes > 0 && acertos < tamanhoPalavra) {
        printf("\nPalavra: %s\n", tentativa);
        printf("Tentativas restantes: %d\n", tentativasRestantes);
        desenhaForca(tentativasRestantes);

        printf("Digite uma letra: ");
        char chute;
        scanf(" %c", &chute);
        chute = toupper(chute);

        int encontrou = 0;
        for (int i = 0; i < tamanhoPalavra; i++) {
            if (toupper(palavra[i]) == chute && tentativa[i] == '_') {
                tentativa[i] = palavra[i];
                acertos++;
                encontrou = 1;
            }
        }

        if (!encontrou) {
            tentativasRestantes--;
            printf("\nLetra incorreta!\n");
        } else {
            printf("\nBoa!\n");
        }
    }

    if (acertos == tamanhoPalavra) {
        printf("\nParabens! Voce acertou a palavra: %s\n", palavra);
    } else {
        printf("\nQue pena! A palavra era: %s\n", palavra);
        desenhaForca(0);  // Desenha o boneco completo após derrota
    }
}
