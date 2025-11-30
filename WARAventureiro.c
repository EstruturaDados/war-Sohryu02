#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Necessário para a semente do rand()

// Constante para o número inicial de territórios (pode ser alterada facilmente)
#define NUM_TERRITORIOS 5

// Definindo a struct Territorio
typedef struct {
    char nome[50];
    char cor_exercito[20];
    int quantidade_tropas;
} Territorio;

// --- Protótipos das Funções ---
void realizar_cadastro(Territorio *lista_territorios, int tamanho);
void exibir_territorios(const Territorio *lista_territorios, int tamanho);
void simular_ataque(Territorio *atacante, Territorio *defensor);
int rolar_dado();

// ----------------------------------------------------------------------
// Função principal (main)
// ----------------------------------------------------------------------
int main() {
    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL));

    // Alocação dinâmica de memória para o array de Territórios
    Territorio *lista_territorios = (Territorio *)malloc(NUM_TERRITORIOS * sizeof(Territorio));

    // Verifica se a alocação foi bem-sucedida
    if (lista_territorios == NULL) {
        printf("Erro na alocação de memória! Saindo.\n");
        return 1;
    }

    printf("🏰 Inicialização do Jogo: Cadastro de %d Territórios 🏰\n", NUM_TERRITORIOS);

    // 1. Cadastro dos Territórios
    realizar_cadastro(lista_territorios, NUM_TERRITORIOS);

    // 2. Exibição dos Territórios
    exibir_territorios(lista_territorios, NUM_TERRITORIOS);

    // ---------------------------------------------------
    // 3. Simulação do Ataque
    // ---------------------------------------------------
    int indice_atacante, indice_defensor;

    printf("\n=====================================\n");
    printf("💥 Simulação de Ataque 💥\n");
    printf("=====================================\n");

    // Seleção do Território Atacante
    do {
        printf("Selecione o número do Território ATACANTE (1 a %d): ", NUM_TERRITORIOS);
        scanf("%d", &indice_atacante);
        indice_atacante--; // Ajusta para o índice do array (0 a N-1)
    } while (indice_atacante < 0 || indice_atacante >= NUM_TERRITORIOS);

    // Seleção do Território Defensor
    do {
        printf("Selecione o número do Território DEFENSOR (1 a %d, diferente do atacante): ", NUM_TERRITORIOS);
        scanf("%d", &indice_defensor);
        indice_defensor--; // Ajusta para o índice do array (0 a N-1)
    } while (indice_defensor < 0 || indice_defensor >= NUM_TERRITORIOS || indice_defensor == indice_atacante);

    // Chamada da função de ataque, passando os endereços de memória (ponteiros)
    simular_ataque(&lista_territorios[indice_atacante], &lista_territorios[indice_defensor]);

    // 4. Exibição dos Territórios após o Ataque
    printf("\n--- Estado Final dos Territórios ---\n");
    exibir_territorios(lista_territorios, NUM_TERRITORIOS);

    // Liberação da memória alocada dinamicamente
    free(lista_territorios);

    return 0;
}

// ----------------------------------------------------------------------
// Funções Auxiliares
// ----------------------------------------------------------------------

/**
 * @brief Realiza o cadastro de N territórios.
 * @param lista_territorios Ponteiro para o primeiro Território.
 * @param tamanho Número de territórios a cadastrar.
 */
void realizar_cadastro(Territorio *lista_territorios, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\n--- Território %d ---\n", i + 1);

        // Nome do Território
        printf("Nome do Território: ");
        scanf(" %49[^\n]", (lista_territorios + i)->nome);

        // Cor do Exército
        printf("Cor do Exército (Ex: Vermelho): ");
        scanf(" %19[^\n]", (lista_territorios + i)->cor_exercito);

        // Quantidade de Tropas
        do {
            printf("Quantidade de Tropas (Mínimo 2 para atacar): ");
            scanf("%d", &(lista_territorios + i)->quantidade_tropas);
            while (getchar() != '\n');
        } while ((lista_territorios + i)->quantidade_tropas < 1);

        // Limpa o buffer de entrada (após scanf("%d"))
        while (getchar() != '\n' && getchar() != EOF);
    }
}

/**
 * @brief Exibe todos os territórios cadastrados.
 * @param lista_territorios Ponteiro constante para o primeiro Território.
 * @param tamanho Número de territórios.
 */
void exibir_territorios(const Territorio *lista_territorios, int tamanho) {
    printf("\n=====================================\n");
    printf("🛡️ Dados Atuais dos Territórios 🛡️\n");
    printf("=====================================\n");
    for (int i = 0; i < tamanho; i++) {
        printf("\n--- Território %d ---\n", i + 1);
        printf("Nome: %s\n", (lista_territorios + i)->nome);
        printf("Cor do Exército: %s\n", (lista_territorios + i)->cor_exercito);
        printf("Tropas: %d\n", (lista_territorios + i)->quantidade_tropas);
    }
}

/**
 * @brief Simula a rolagem de um dado de 6 faces (1 a 6).
 * @return O resultado da rolagem.
 */
int rolar_dado() {
    // Gera um número aleatório entre 1 e 6
    return (rand() % 6) + 1;
}

/**
 * @brief Simula um ataque entre dois territórios.
 * @param atacante Ponteiro para o território atacante.
 * @param defensor Ponteiro para o território defensor.
 */
void simular_ataque(Territorio *atacante, Territorio *defensor) {
    printf("\n--- INÍCIO DO COMBATE ---\n");
    printf("%s (Cor: %s, Tropas: %d) ataca %s (Cor: %s, Tropas: %d)!\n",
           atacante->nome, atacante->cor_exercito, atacante->quantidade_tropas,
           defensor->nome, defensor->cor_exercito, defensor->quantidade_tropas);

    // Regra: Um território precisa de pelo menos 2 tropas para atacar (1 de ataque + 1 de ocupação)
    if (atacante->quantidade_tropas < 2) {
        printf("❌ Ataque cancelado! O território %s precisa de no mínimo 2 tropas para atacar.\n", atacante->nome);
        return;
    }

    // Simulação simplificada de dados (atacante vs defensor)
    int dado_ataque = rolar_dado();
    int dado_defesa = rolar_dado();

    printf("🎲 Rolagens: Atacante (%d) vs Defensor (%d)\n", dado_ataque, dado_defesa);

    // A lógica de vitória/perda é simplificada:
    // Se o dado do atacante for estritamente maior que o do defensor, o atacante ganha.
    if (dado_ataque > dado_defesa) {
        printf("✅ VITÓRIA do ATACANTE! %s venceu a rodada.\n", atacante->nome);

        // Defensor perde 1 tropa
        defensor->quantidade_tropas--;

        // Verifica se o defensor perdeu o território
        if (defensor->quantidade_tropas == 0) {
            printf("🎉 CONQUISTA! O território %s foi tomado!\n", defensor->nome);

            // Defensor perde o controle do território
            // O atacante move 1 tropa para ocupar o novo território
            defensor->quantidade_tropas = 1;

            // Atualiza a cor do exército para a cor do atacante
            strcpy(defensor->cor_exercito, atacante->cor_exercito);

            // Atacante perde a tropa que foi movida
            atacante->quantidade_tropas--;

            printf("🚨 Novo Dono: %s agora pertence ao exército %s com 1 tropa.\n",
                   defensor->nome, defensor->cor_exercito);
        } else {
            printf("📉 %s perdeu 1 tropa. Tropas restantes: %d.\n",
                   defensor->nome, defensor->quantidade_tropas);
        }

    } else { // O defensor ganha ou há empate (que geralmente favorece o defensor)
        printf("🛡️ VITÓRIA da DEFESA! %s defendeu-se com sucesso.\n", defensor->nome);

        // Atacante perde 1 tropa
        atacante->quantidade_tropas--;

        printf("📉 %s perdeu 1 tropa. Tropas restantes: %d.\n",
               atacante->nome, atacante->quantidade_tropas);
    }

    printf("--- FIM DO COMBATE ---\n");
}
