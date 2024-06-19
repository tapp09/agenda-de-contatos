#include <stdio.h>
#include <string.h>

#define TAMANHO_CONTATOS 100

typedef struct {
    char nome[50];
    char numero[20];
} Contato;

int main() {
    Contato lista[TAMANHO_CONTATOS];
    int id_contatos = 0;
    FILE *contatos_txt, *contatos_bin;
    char opcao;

    do {
        printf("Escolha a sua opcao:\n");
        printf("1 - Adicionar Contato\n");
        printf("2 - Consultar Contato\n");
        printf("3 - Excluir Contato\n");
        printf("4 - Contatos\n");
        printf("5 - Fim\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);
        fflush(stdin);

        switch (opcao) {
            case '1':
                printf("Digite o nome: ");
                scanf(" %s", lista[id_contatos].nome);

                printf("Digite o numero do contato: ");
                scanf(" %s", lista[id_contatos].numero);

                id_contatos++;
                printf("Contato adicionado com sucesso!\n");
                break;

            case '2':
                if (id_contatos == 0) {
                    printf("Agenda vazia. Nenhum contato para consultar.\n");
                } else {
                    char nome_consulta[50];
                    int encontrado = 0;

                    printf("Digite o nome do contato para consultar: ");
                    scanf(" %s", nome_consulta);

                    for (int i = 0; i < id_contatos; i++) {
                        if (strcmp(lista[i].nome, nome_consulta) == 0) {
                            printf("Nome: %s\nTelefone: %s\n", lista[i].nome, lista[i].numero);
                            encontrado = 1;
                            break;
                        }
                    }

                    if (!encontrado) {
                        printf("Contato nao encontrado.\n");
                    }
                }
                break;

            case '3':
                if (id_contatos == 0) {
                    printf("Agenda vazia. Nenhum contato para excluir.\n");
                } else {
                    char nome_excluir[50];
                    int encontrado = 0;

                    printf("Digite o nome do contato para excluir: ");
                    scanf(" %s", nome_excluir);

                    for (int i = 0; i < id_contatos; i++) {
                        if (strcmp(lista[i].nome, nome_excluir) == 0) {
                            printf("Contato de %s excluido.\n", lista[i].nome);
                            lista[i] = lista[id_contatos - 1];
                            id_contatos--;
                            encontrado = 1;
                            break;
                        }
                    }

                    if (!encontrado) {
                        printf("Contato não encontrado.\n");
                    }
                }
                break;

            case '4':
                contatos_bin = fopen("lista_contatos.bin", "rb");
                if (contatos_bin == NULL) {
                    printf("Erro ao abrir o arquivo binário de registro de contatos.\n");
                } else {
                    Contato contato_bin;

                    printf("Registros de Contatos:\n");
                    while (fread(&contato_bin, sizeof(Contato), 1, contatos_bin) == 1) {
                        printf("Nome: %s | Telefone: %s\n", contato_bin.nome, contato_bin.numero);
                    }

                    fclose(contatos_bin);
                }
                break;

            case '5': // Fim
                printf("Encerrando o programa...\n");
                break;
        }

    } while (opcao != '5');

    contatos_txt = fopen("lista_contatos.txt", "w");
    if (contatos_txt == NULL) {
        printf("Erro ao abrir o arquivo de texto da agenda de contatos.\n");
        return 1;
    }

    for (int i = 0; i < id_contatos; i++) {
        fprintf(contatos_txt, "Nome: %s | Telefone: %s\n", lista[i].nome, lista[i].numero);
    }

    fclose(contatos_txt);

    contatos_bin = fopen("lista_contatos.bin", "wb");
    if (contatos_bin == NULL) {
        printf("Erro ao abrir o arquivo binario de registro de contatos para escrita.\n");
        return 1;
    }

    for (int i = 0; i < id_contatos; i++) {
        fwrite(&lista[i], sizeof(Contato), 1, contatos_bin);
    }

    fclose(contatos_bin);

    return 0;
}
