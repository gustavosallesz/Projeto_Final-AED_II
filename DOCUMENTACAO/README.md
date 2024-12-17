# Documentação do Jogo da Forca

## Introdução
Este documento descreve a implementação do jogo da forca em linguagem **C**.

O código foi projetado para ser modular e utiliza algumas listas, como a **Lista Simplesmente Encadeada (LSE)** para gerenciar as tentativas de descoberta e letras incorretas digitadas. Além disso, há funcionalidades de **leitura e escrita de arquivos** para manter um histórico de palavras e dicas, tornando o jogo mais dinâmico.

---

## Estruturas de Dados Utilizadas

### Lista Simplesmente Encadeada (LSE)
A **Lista Simplesmente Encadeada (LSE)** é usada para armazenar dinamicamente as letras adivinhadas e as letras incorretas digitadas pelo jogador.

#### Estruturas Principais:
- **Nó (`No`)**: Representa cada elemento da lista, contendo um valor (letra) e um ponteiro para o próximo nó.
- **Lista (`listaLSE`)**: Contém um ponteiro para o primeiro nó da lista.

#### Funções Associadas:
1. `criaLista()`: Cria uma nova lista.
2. `adicionaLetra()`: Adiciona uma letra à lista.
3. `exibeLista()`: Exibe as letras armazenadas na lista.
4. `liberaLista()`: Libera a memória alocada para a lista.

---

## Funcionalidades Adicionais
1. **Leitura de Arquivos**:
   - Lê palavras e dicas de um arquivo predefinido para gerar as rodadas do jogo.
2. **Escrita de Arquivos**:
   - Permite que o jogador cadastre e remova palavras do jogo.
3. **Interface Gráfica**:
   - Removemos do projeto final pois o tempo tava curto e o trabalho tava muito kkkkkkk. Porém, na pasta "OLD_FORCA", há um projeto mais simples, utilizando o modo gráfico.

---

## Como Executar
1. **Pré-requisitos**:
   - Um compilador que suporte **C/C++**.
   - Configuração da biblioteca gráfica `graphics.h`. (Não é mais necessário)
2.  **Execução**:
   - Faça o download do diretório que armazena os arquivos.
   - Abra o CodeBlocks e selecione a opção `Abrir projeto existente`.
   - Na pasta recém baixada, selecione o arquivo `TrabalhoFinal_AED`, cujo tipo é `project file`.
   - Após isso, todos os códigos que compõem o projeto serão carregados nas abas à esquerda: `Sources/.c e Headers/.h`.
  
---
##Acesso ao Vídeo

Siga este link do Youtube para acesso ao nosso vídeo explicativo [Jogo da Forca - Apresentação Final](https://youtu.be/bU2nXbKyRW0)

## Contribuidores
- **Leonardo, Luiz e Maykel**: Desenvolvedores principais do projeto.

---
