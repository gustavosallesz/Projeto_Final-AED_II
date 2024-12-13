#include "FuncForca.h"

 void ortografia() {
    setlocale(LC_ALL, "Portuguese");
}

 /* Nessa função a gente faz com que as palavras sejam carregadas
    da lista para o arquivo*/
void carregaPalavras(Palavra **lista) {
    FILE *arquivo = fopen("palavras.txt", "r");
    if (!arquivo) {
        printf("Arquivo de palavras nao encontrado. Criando novo...\n");
        arquivo = fopen("palavras.txt", "w");  // Abre em modo de escrita para criar o arquivo vazio
        fclose(arquivo);  // Fecha o arquivo vazio
        return;
    }

    char linha[150];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0'; // Remove o \n
        char *dica = strtok(linha, ";");
        char *palavra = strtok(NULL, ";");
        if (dica && palavra) {
            adicionaPalavra(lista, palavra, dica);
        }
    }

    fclose(arquivo);
}


// Salva palavras da lista no arquivo
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

// Exibe todas as palavras da lista
void exibePalavras(Palavra *lista) {
    printf("\n=== LISTA DE PALAVRAS ===\n");
    Palavra *atual = lista;
    while (atual) {
        printf("Palavra: %s | Dica: %s\n", atual->palavra, atual->dica);
        atual = atual->prox;
    }
}


// Remove uma palavra específica da lista
void removePalavra(Palavra **lista, const char *palavra) {
    Palavra *atual = *lista;
    Palavra *anterior = NULL;

    // Procura a palavra na lista
    while (atual != NULL && strcmp(atual->palavra, palavra) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    // Palavra não encontrada
    if (atual == NULL) {
        printf("\nPalavra '%s' nao encontrada!\n", palavra);
        return; // Apenas sai da função, sem encerrar o programa
    }

    // Remove o nó da lista
    if (anterior == NULL) {
        *lista = atual->prox; // A palavra está no início
    } else {
        anterior->prox = atual->prox; // A palavra está no meio ou no fim
    }

    free(atual); // Libera a memória
    printf("\nPalavra '%s' removida com sucesso!\n", palavra);

    // Atualiza o arquivo
    salvaPalavras(*lista);
}


// Libera memória alocada para a lista
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

    int indice = rand() % total;
    atual = lista;
    while (indice-- && atual) {
        atual = atual->prox;
    }

    char *palavra = atual->palavra;
    char *dica = atual->dica;
    char tentativa[strlen(palavra) + 1];
    memset(tentativa, '_', strlen(palavra));
    tentativa[strlen(palavra)] = '\0';

    int tentativasRestantes = 6, acertos = 0, tamanhoPalavra = strlen(palavra);
    printf("\nDica: %s\n", dica);

    while (tentativasRestantes > 0 && acertos < tamanhoPalavra) {
        printf("\nPalavra: %s\n", tentativa);
        printf("Tentativas restantes: %d\n", tentativasRestantes);

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
    }
}
