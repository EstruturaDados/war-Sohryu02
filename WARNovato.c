#include <stdio.h>
#include <string.h>

// Definindo a struct Territorio
typedef struct {
    char nome[50];
    char cor_exercito[20];
    int quantidade_tropas;
} Territorio;

// Constante para o número de territórios
#define MAX_TERRITORIOS 5

int main() {
    // Declaração de um array de structs para armazenar os territórios
    Territorio lista_territorios[MAX_TERRITORIOS];
    int i;

    printf("🏰 Cadastro de %d Territórios 🏰\n", MAX_TERRITORIOS);
    printf("--------------------------------------\n");

    // Loop para preencher os dados dos 5 territórios
    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\n--- Território %d ---\n", i + 1);

        // Nome do Território
        printf("Nome do Território: ");
        // O scanf com [^\n]%*c é usado para ler a linha inteira, incluindo espaços,
        // e descartar o caractere de nova linha (\n) restante.
        scanf(" %49[^\n]", lista_territorios[i].nome);

        // Cor do Exército
        printf("Cor do Exército (Ex: Vermelho): ");
        scanf(" %19[^\n]", lista_territorios[i].cor_exercito);

        // Quantidade de Tropas
        printf("Quantidade de Tropas: ");
        // Usamos & para passar o endereço da variável para o scanf
        if (scanf("%d", &lista_territorios[i].quantidade_tropas) != 1) {
            // Caso o usuário insira algo que não seja um número para as tropas
            printf("⚠️ Entrada inválida para a quantidade de tropas. Saindo.\n");
            return 1;
        }

        // Limpa o buffer de entrada (especialmente o \n) após o scanf("%d")
        while (getchar() != '\n');
    }

    printf("\n=====================================\n");
    printf("🛡️ Dados dos Territórios Cadastrados 🛡️\n");
    printf("=====================================\n");

    // Loop para exibir os dados dos 5 territórios
    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\n--- Território %d ---\n", i + 1);
        printf("Nome: %s\n", lista_territorios[i].nome);
        printf("Cor do Exército: %s\n", lista_territorios[i].cor_exercito);
        printf("Tropas: %d\n", lista_territorios[i].quantidade_tropas);
    }

    printf("\nFim do cadastro e exibição.\n");

    return 0;
}
