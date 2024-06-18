#include "../include/Telas.h"
#include "../include/ArvoreBinaria.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

// Função para detectar a tecla pressionada sem a necessidade de pressionar Enter
char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void reiniciar() {
    sleep(1/2);  // Aguarda meio segundo
    main();    // Chama a função main novamente
}

int main() {
    int op = 0, escolha = 0, tecla;
    // Peca *peca;

    // Configuração de cores usando escape ANSI
    printf("\033[1;97m"); // Negrito e texto branco

    do {
        system("clear");
        printf("   🔴🟩🟩                                                 \n");
        printf("   🟩🟩   INSTITUTO FEDERAL                               \n");
        printf("   🟩🟩🟩 DE EDUCAÇÃO, CIÊNCIA E TECNOLOGIA               \n");
        printf("   🟩🟩   Bahia                                           \n");
        printf("    --------------------------------------------------   \n");
        printf("         Discentes: Alef Montino e Flavio Junior \n\n");

        printf("\033[1;97m"); // Negrito e texto branco
        printf("\033[47m");  // Fundo branco
        printf("╔════════════════════════════════════════════════════════╗\n");
        printf("║  ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫    ║\n");
        printf("║                                                        ║\n");
        printf("\033[0m");  // Resetando as configurações para o padrão
        printf("\033[40m");  // Fundo preto
        printf("║            _                 _          __             ║\n");
        printf("║           | |               (_)        / /             ║\n");
        printf("║         __| | ___  _ __ ___  _ _ __   ___              ║\n");
        printf("║        / _` |/ _ \\| '_ ` _ \\| | '_ \\ / _ \\      \033[1;34m____\033[0m\033[40m   ║\n");
        printf("║       | (_| | (_) | | | | | | | | | | (_) |    \033[1;34m/ ___|\033[0m\033[40m  ║\n");
        printf("║        \\__,_|\\___/|_| |_| |_|_|_| |_|\\___/ in \033[1;34m| |___\033[0m\033[40m   ║\n");
        printf("║                                                \033[1;34m\\____|\033[0m\033[40m  ║\n");
        printf("║                                                        ║\n");
        //printf("\033[1;97m"); // Negrito e texto branco
        printf("║                                      ⬜⬜⬜⬜⬜        ║\n");
        printf("║                                      ⬜⬜⬜⬜⬜        ║\n");
        printf("║                                      ⬜⚫⬜⚫⬜        ║\n");
        printf("║                                      ⬜⬜⬜⬜⬜        ║\n");
        printf("║                                      ⬜⬜⬜⬜⬜        ║\n");
        printf("║                                      ⬛⬛⬛⬛⬛        ║\n");
        printf("║     ⬜⬜⬜⬜⬜⬛⬜⬜⬜⬜⬜           ⬜⬜⬜⬜⬜        ║\n");
        printf("║     ⬜⬜⬜⬜⬜⬛⬜⚫⬜⚫⬜           ⬜⚫⬜⚫⬜        ║\n");
        printf("║     ⬜⬜⚫⬜⬜⬛⬜⬜⬜⬜⬜           ⬜⚫⬜⚫⬜        ║\n");
        printf("║     ⬜⬜⬜⬜⬜⬛⬜⚫⬜⚫⬜           ⬜⚫⬜⚫⬜        ║\n");
        printf("║     ⬜⬜⬜⬜⬜⬛⬜⬜⬜⬜⬜           ⬜⬜⬜⬜⬜        ║\n");
        printf("\033[0m");  // Resetando as configurações para o padrão
        printf("\033[1;97m"); // Negrito e texto branco
        printf("║                                                        ║\n");
        printf("║                         %sIniciar%s                        ║\n", (escolha == 1) ? "\033[1;32m" : "", "\033[0m");
        printf("║                         %sAjuda%s                          ║\n", (escolha == 2) ? "\033[1;32m" : "", "\033[0m");
        printf("║                         %sSair%s                           ║\n", (escolha == 3) ? "\033[1;31m" : "", "\033[0m");
        printf("║                                                        ║\n");
        printf("\033[1;97m"); // Negrito e texto branco
        printf("\033[47m");  // Fundo branco
        printf("╔════════════════════════════════════════════════════════╗\n");
        printf("║  ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫    ║\n");
        printf("║                                                        ║\n");
        printf("\033[0m");  // Resetando as configurações para o padrão

        printf("\nOpção selecionada: %d\n", escolha);

        tecla = getch();

        // Se a tecla pressionada for "seta para cima"
        if (tecla == 65) {
            if (escolha > 0)
                escolha--;
                op--;
        }
        // Se a tecla pressionada for "seta para baixo"
        else if (tecla == 66) {
            if (escolha < 3)
                escolha++;
                op++;
        }
    } while (tecla != 10); // 10 é o código ASCII para a tecla Enter

        switch (op) {
          case 0: 
                break;
          
            case 1:
                printf("Teste case 1\n");
                menu2();
                // novo jogo
                break;

            case 2:
                telaAjuda();
                break;

            case 3:
                printf("PROGRAMA ENCERRADO! \n");
                // Código para a opção 4 (Sair)
                break;

            default:
                printf("Opção inválida\n");
                break;
        }
    return 0;
}