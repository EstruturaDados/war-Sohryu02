#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio (já existente)
typedef struct {
    char nome[50];
    char corExercito[20];
    int quantidadeTropas;
} Territorio;

// NOVA: Definição da struct Jogador
typedef struct {
    char nome[50];
    char cor[20];
    char *missao; // PONTEIRO para a string da missão sorteada
} Jogador;

// --- DADOS GLOBAIS/CONSTANTES (Pré-definidos) ---
const char *MISSOES[] = {
    "Conquistar 18 territórios (qualquer um).",
    "Conquistar a Ásia e a África.",
    "Conquistar a América do Norte e 1 continente de sua escolha.",
    "Destruir o exército da cor AZUL (ou conquistar 24 territórios se o azul for você).",
    "Conquistar 24 territórios (qualquer um)."
};
const int NUM_MISSOES = 5;

// --- FUNÇÕES DE SETUP ---

// Função para sortear e atribuir uma missão a um jogador
// Recebe um ponteiro para a struct Jogador (Passagem por Referência)
void atribuirMissao(Jogador *jogador) {
    // Sorteia um índice aleatório
    int indiceSorteado = rand() % NUM_MISSOES;

    // Aloca dinamicamente memória para a string da missão
    size_t tamanhoMissao = strlen(MISSOES[indiceSorteado]) + 1;
    jogador->missao = (char *)malloc(tamanhoMissao);

    if (jogador->missao == NULL) {
        perror("Falha na alocação da missão");
        return;
    }

    // Copia a string da missão para a memória alocada
    strcpy(jogador->missao, MISSOES[indiceSorteado]);
    printf("✅ Missão atribuída a %s com sucesso.\n", jogador->nome);
}

// Função para exibir a missão (Passagem por Valor e Referência)
// Recebe o nome por valor (copia) e o ponteiro da missão por referência
void exibirMissao(char nomeJogador[], const char *missao) {
    printf("\n--- Missão de %s ---\n", nomeJogador);
    printf("OBJETIVO: **%s**\n", missao);
    printf("---------------------------\n");
}


// --- FUNÇÕES DE GESTÃO DE JOGO (Exemplo da Verificação) ---

// Função de verificação (Simulada para demonstração)
// Passagem do array de territórios (ponteiro) e do jogador (referência)
int verificarVitoria(const Territorio *territorios, int numTerritorios, const Jogador *jogador) {
    printf("\n--- Verificando condição de vitória para %s ---\n", jogador->nome);

    // Simplificação: Contar quantos territórios o jogador possui
    int territoriosConquistados = 0;
    for (int i = 0; i < numTerritorios; i++) {
        // Acessando o elemento 'i' através de aritmética de ponteiros
        if (strcmp((territorios + i)->corExercito, jogador->cor) == 0) {
            territoriosConquistados++;
        }
    }

    printf("  Territórios atuais de %s: %d\n", jogador->nome, territoriosConquistados);
    printf("  Missão atual: %s\n", jogador->missao);

    // Simplificação: Se a missão for "Conquistar 18 territórios" e ele tiver >= 18
    if (strstr(jogador->missao, "18 territórios") != NULL && territoriosConquistados >= 18) {
        return 1; // Vencedor
    }
    // Simplificação: Se a missão for "Conquistar 24 territórios" e ele tiver >= 24
    if (strstr(jogador->missao, "24 territórios") != NULL && territoriosConquistados >= 24) {
        return 1; // Vencedor
    }

    // Outras missões exigiriam lógica complexa (ex: verificar continentes)
    printf("  Condição de vitória **não** atingida (simulação).\n");
    return 0; // Não venceu
}

// --- FUNÇÕES DO CÓDIGO ANTERIOR (Otimizadas) ---
// Função para simular a rolagem de um dado (1 a 6) (Passagem por Valor)
int rolarDado() {
    return (rand() % 6) + 1;
}

// Função para exibir os territórios (Passagem por Referência)
void exibirTerritorios(const Territorio *territorios, int numTerritorios) {
    // ... (Mantido o código de exibição anterior)
    if (numTerritorios == 0) {
        printf("\nNenhum território cadastrado.\n");
        return;
    }
    printf("\n--- LISTA DE TERRITÓRIOS (%d Cadastrados) ---\n", numTerritorios);
    for (int i = 0; i < numTerritorios; i++) {
        printf("[%d] %s\n", i + 1, (territorios + i)->nome);
        printf("    Cor: %s | Tropas: %d\n", (territorios + i)->corExercito, (territorios + i)->quantidadeTropas);
    }
    printf("-------------------------------------------\n");
}
// OBS: A função simularAtaque() foi omitida na main para focar no novo requisito, mas seria mantida.

// --- MAIN ---

int main() {
    srand(time(NULL));

    // CONFIGURAÇÃO DO JOGO (Hardcoded para demonstração)
    int maxTerritorios = 5;
    int numTerritorios = maxTerritorios;
    int numJogadores = 2; // Simplificação para 2 jogadores

    // 1. ALOCAÇÃO DE MEMÓRIA PARA TERRITÓRIOS
    Territorio *listaTerritorios = (Territorio *)malloc(maxTerritorios * sizeof(Territorio));
    // 2. ALOCAÇÃO DE MEMÓRIA PARA JOGADORES
    Jogador *listaJogadores = (Jogador *)malloc(numJogadores * sizeof(Jogador));

    if (listaTerritorios == NULL || listaJogadores == NULL) {
        perror("Falha na alocação de memória inicial");
        if (listaTerritorios) free(listaTerritorios);
        if (listaJogadores) free(listaJogadores);
        return 1;
    }

    // --- POPULANDO DADOS INICIAIS (Hardcoded para teste rápido) ---
    // Jogador 1
    strcpy(listaJogadores[0].nome, "Alice");
    strcpy(listaJogadores[0].cor, "Verde");
    atribuirMissao(&listaJogadores[0]); // Atribuição da Missão

    // Jogador 2
    strcpy(listaJogadores[1].nome, "Bob");
    strcpy(listaJogadores[1].cor, "Azul");
    atribuirMissao(&listaJogadores[1]); // Atribuição da Missão

    // Territórios
    strcpy(listaTerritorios[0].nome, "Brazil");
    strcpy(listaTerritorios[0].corExercito, "Verde");
    listaTerritorios[0].quantidadeTropas = 10;

    strcpy(listaTerritorios[1].nome, "Argentina");
    strcpy(listaTerritorios[1].corExercito, "Azul");
    listaTerritorios[1].quantidadeTropas = 8;

    strcpy(listaTerritorios[2].nome, "Chile");
    strcpy(listaTerritorios[2].corExercito, "Verde");
    listaTerritorios[2].quantidadeTropas = 5;

    strcpy(listaTerritorios[3].nome, "Colombia");
    strcpy(listaTerritorios[3].corExercito, "Azul");
    listaTerritorios[3].quantidadeTropas = 3;

    strcpy(listaTerritorios[4].nome, "Mexico");
    strcpy(listaTerritorios[4].corExercito, "Verde");
    listaTerritorios[4].quantidadeTropas = 20;


    // --- 3. EXECUÇÃO DO JOGO ---

    printf("\n============== INÍCIO DO JOGO ==============\n");

    // Exibir Missões
    for (int i = 0; i < numJogadores; i++) {
        exibirMissao(listaJogadores[i].nome, listaJogadores[i].missao);
    }

    exibirTerritorios(listaTerritorios, numTerritorios);

    // --- 4. VERIFICAÇÃO DE VITÓRIA ---
    printf("\n=============== FASE DE VERIFICAÇÃO DE VITÓRIA ===============\n");

    // Simulação: Modificar o estado para testar a vitória (Ex: Bob conquista 24)
    // Se o México (território 4) tivesse 20 tropas e fosse de Alice (Verde)
    // E, se Alice tivesse 18 territórios.

    // Vamos simular que Alice conquistou o Brasil (10), Chile (5) e México (20), total 3.
    // Para testar a missão de 18 territórios, vamos SIMULAR um território (índice 4)
    // que faz Alice atingir a meta.
    printf("\n--- SIMULANDO VITÓRIA DE ALICE (3/5 territórios, mas vamos testar a lógica) ---\n");

    if (verificarVitoria(listaTerritorios, numTerritorios, &listaJogadores[0])) {
        printf("\n👑 **%s (Verde) VENCEU O JOGO!** 👑\n", listaJogadores[0].nome);
    } else {
        printf("\nO jogo continua.\n");
    }

    // --- 5. LIBERAÇÃO DE MEMÓRIA ---
    for (int i = 0; i < numJogadores; i++) {
        // Liberar a memória alocada dinamicamente para a string da missão de CADA jogador
        if (listaJogadores[i].missao != NULL) {
            free(listaJogadores[i].missao);
        }
    }
    free(listaJogadores);
    free(listaTerritorios);
    printf("\nMemória de jogadores e territórios liberada com sucesso.\n");

    return 0;
}
