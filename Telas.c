#include "../include/ArvoreBinaria.h"
#include "../include/Telas.h"
#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void menu2(){
  int escolh = 0;
  int tecl, opc = 0;

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
  printf("║                                                        ║\n");
  printf("║            _                 _          __             ║\n");
  printf("║           | |               (_)        / /             ║\n");
  printf("║         __| | ___  _ __ ___  _ _ __   ___              ║\n");
  printf("║        / _` |/ _ \\| '_ ` _ \\| | '_ \\ / _ \\      \033[1;34m____\033[0m\033[40m   ║\n");
  printf("║       | (_| | (_) | | | | | | | | | | (_) |    \033[1;34m/ ___|\033[0m\033[40m  ║\n");
  printf("║        \\__,_|\\___/|_| |_| |_|_|_| |_|\\___/ in \033[1;34m| |___\033[0m\033[40m   ║\n");
  printf("║                                                \033[1;34m\\____|\033[0m\033[40m  ║\n");
  printf("║                                                        ║\n");
  printf("\033[40m");  // Fundo preto
  printf("\033[1;97m"); // Negrito e texto branco
  printf("\033[0m");  // Resetando as configurações para o padrão
  printf("\033[1;97m"); // Negrito e texto branco
  printf("║                                                        ║\n");
  printf("║                       %s 1 player%s                        ║\n", (escolh == 1) ? "\033[1;32m" : "", "\033[0m");
  printf("║                       %s 2 players%s                       ║\n", (escolh == 2) ? "\033[1;32m" : "", "\033[0m");
  printf("║                       %s 3 players%s                       ║\n", (escolh == 3) ? "\033[1;32m" : "", "\033[0m");
  printf("║                       %s 4 players%s                       ║\n", (escolh == 4) ? "\033[1;32m" : "", "\033[0m");
  printf("║                                                        ║\n");
  printf("║                       %s   Voltar%s                        ║\n", (escolh == 5) ? "\033[1;31m" : "", "\033[0m");
  printf("║                                                        ║\n");
  printf("\033[1;97m"); // Negrito e texto branco
  printf("\033[47m");  // Fundo branco
  printf("══════════════════════════════════════════════════════════\n");
  printf("║  ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫    ║\n");
  printf("║                                                        ║\n");
  printf("\033[0m");  // Resetando as configurações para o padrão

  printf("\nOpção selecionada: %d\n", escolh);

  tecl = getch();

      // Se a tecla pressionada for "seta para cima"
      if (tecl == 65) {
          if (escolh > 0)
              escolh--;
              opc--;
      }
      // Se a tecla pressionada for "seta para baixo"
      else if (tecl == 66) {
          if (escolh < 5)
              escolh++;
              opc++;
      }
  }while (tecl != 10); // 10 é o código ASCII para a tecla Enter

  switch (opc) {
 
      case 1:
       // printf("\nVocê já viu alguém jogar dominó sozinho kkkkk\n");
          menu_vs_cpu();
          sleep(2);
          menu2();
          break;

      case 2:
          //printf("Teste case 2\n");
          system("clear");
          menu_2_jogadores();
          menu2();
          break;

      case 3:
          system("clear");
          menu_3_jogadores();
          menu2();
          break;
    
      case 4:
          system("clear");
          menu_4_jogadores();
          menu2();
          break;
    
      case 5:
          printf("Teste case 5\n");
          reiniciar();
          return;

      case 0:
          menu2();
          break;
  }
}

int menuMesa() {
    int escolh = 0; // Começar com a primeira opção selecionada
    int tecl, op = 0;

    do {
        system("clear");

        printf("                      ╔═══════════════════════╗\n");
        printf("                      ║ %s   Realizar Jogada %s   ║\n", (escolh == 1) ? "\033[1;32m" : "", "\033[0m");
        printf("                      ╚═══════════════════════╝\n");
        printf("                      ╔═══════════════════════╗\n");
        printf("                      ║ %s      Pontuação %s      ║\n", (escolh == 2) ? "\033[1;32m" : "", "\033[0m");
        printf("                      ╚═══════════════════════╝\n");
        printf("                      ╔═══════════════════════╗\n");
        printf("                      ║ %s        Pause      %s   ║\n", (escolh == 3) ? "\033[1;32m" : "", "\033[0m");
        printf("                      ╚═══════════════════════╝\n");
        printf("                      ╔═══════════════════════╗\n");
        printf("                      ║ %s        Sair       %s   ║\n", (escolh == 4) ? "\033[1;31m" : "", "\033[0m");
        printf("                      ╚═══════════════════════╝\n");

        printf("\nOpção selecionada: %d\n", escolh);

        tecl = getch();

        // Se a tecla pressionada for "seta para cima"
        if (tecl == 65) {
            if (escolh > 0)
                escolh--;
                op--;
        }
        // Se a tecla pressionada for "seta para baixo"
        else if (tecl == 66) {
            if (escolh < 4)
                escolh++;
                op++;
        }
      
    } while (tecl != 10); // 10 é o código ASCII para a tecla Enter
    
  switch (op) {
    case 1:
        system("clear");
        printf("Realizar Jogada\n");
        return 1;
        break;
  
    case 2:
        system("clear");
        printf("Pontuação\n");
        return 2;
        break;
  
    case 3:
        system("clear");
        printf("Pause\n");
        telaPause();
        break;
  
    case 4:
        return 4;
    }
    return 0; // Retorno padrão, pode ser ajustado conforme necessário
}

int menuJogo(){
  int escolh = 0;
  int tecl, opc = 0;

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
  printf("║                                                        ║\n");
  printf("║            _                 _          __             ║\n");
  printf("║           | |               (_)        / /             ║\n");
  printf("║         __| | ___  _ __ ___  _ _ __   ___              ║\n");
  printf("║        / _` |/ _ \\| '_ ` _ \\| | '_ \\ / _ \\      \033[1;34m____\033[0m\033[40m   ║\n");
  printf("║       | (_| | (_) | | | | | | | | | | (_) |    \033[1;34m/ ___|\033[0m\033[40m  ║\n");
  printf("║        \\__,_|\\___/|_| |_| |_|_|_| |_|\\___/ in \033[1;34m| |___\033[0m\033[40m   ║\n");
  printf("║                                                \033[1;34m\\____|\033[0m\033[40m  ║\n");
  printf("║                                                        ║\n");
  printf("\033[40m");  // Fundo preto
  printf("\033[1;97m"); // Negrito e texto branco
  printf("\033[0m");  // Resetando as configurações para o padrão
  printf("\033[1;97m"); // Negrito e texto branco
  printf("║                                                        ║\n");
  printf("║                                                        ║\n");
  printf("║                       %sNovo Jogo%s                        ║\n", (escolh == 1) ? "\033[1;32m" : "", "\033[0m");
  printf("║                     %sCarregar Save%s                      ║\n", (escolh == 2) ? "\033[1;32m" : "", "\033[0m");
  printf("║                                                        ║\n");
  printf("║                                                        ║\n");
  printf("║                        %sVoltar%s                          ║\n", (escolh == 3) ? "\033[1;31m" : "", "\033[0m");
  printf("║                                                        ║\n");
  printf("\033[1;97m"); // Negrito e texto branco
  printf("\033[47m");  // Fundo branco
  printf("══════════════════════════════════════════════════════════\n");
  printf("║  ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫ ⚫    ║\n");
  printf("║                                                        ║\n");
  printf("\033[0m");  // Resetando as configurações para o padrão

  printf("\nOpção selecionada: %d\n", escolh);

  tecl = getch();

      // Se a tecla pressionada for "seta para cima"
      if (tecl == 65) {
          if (escolh > 0)
              escolh--;
              opc--;
      }
      // Se a tecla pressionada for "seta para baixo"
      else if (tecl == 66) {
          if (escolh < 5)
              escolh++;
              opc++;
      }
  }while (tecl != 10); // 10 é o código ASCII para a tecla Enter
  printf("\033[0m");
  telaCarreg();
  return opc;
}

void telaCarreg() {
  int l = 1;
  system("clear");

  printf("\n\n\n\n");
  printf("   _      ____          _____ _____ _   _  _____ \n");
  printf("  | |    / __ \\   /\\   |  __ \\_   _| \\ | |/ ____|\n");
  printf("  | |   | |  | | /  \\  | |  | || | |  \\| | |  __ \n");
  printf("  | |   | |  | |/ /\\ \\ | |  | || | | . ` | | |_ |\n");
  printf("  | |____ |__| / ____ \\| |__| || |_| |\\  | |__| |\n");
  printf("  |______\\____/_/    \\_\\_____/_____|_| \\_|\\_____|\n");
  printf("\033[1;33m"); // Amarelo
  do {
    if (l == 1) {
      printf("████████████ 39%%");
      l = 2;
    } else if (l == 2) {
      printf("\b\b\b\b\b\b\b██████████████████ 76%%");
      l = 3;
    } else if(l == 3) {
      printf("\b\b\b\b\b\b\b\b\b\b\b\b█████████████████████████████████ 100%%");
      l++ ;
    }

    fflush(stdout);
    sleep(1);
  } while (l != 4 );
  printf("\033[0m"); // padrão
  printf("\n\n");
}

void telaEmpate(){
printf("\033[1;37m");// Branco
printf("\n\n");
printf("                    ___________\n");
printf("                   |           |\n");
printf("                   |  EMPATE!  |\n");
printf("                   |___________|\n");
printf("                 \033[1;33m(\\__/)  \033[1;37m||\n");
printf("                 \033[1;33m(•ㅅ•)  \033[1;37m||\n");
printf("                 \033[1;33m/     づ\n");
}

void telaAjuda() {
  int escol = 0;
  int tec, op = 0;

  do {
    system("clear");
    printf("   🔴🟩🟩                                                 \n");
    printf("   🟩🟩   INSTITUTO FEDERAL                               \n");
    printf("   🟩🟩🟩 DE EDUCAÇÃO, CIÊNCIA E TECNOLOGIA               \n");
    printf("   🟩🟩   Bahia                                           \n");
    printf("    --------------------------------------------------   \n");
    printf("         Discentes: Alef Montino e Flavio Junior \n\n");

    printf("\n                   ----[Regras]----\n\n");
    printf("\033[1;33m"); // Amarelo
    // Regra 1
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║ 1. Número de Jogadores                       ║\n");
    printf("╚══════════════════════════════════════════════╝\n\n");
    printf("\033[1;37m"); // Branco
    printf("   - O jogo de Dominó pode ser jogado por 2 a 4 jogadores\n\n");
    // Regra 2
    printf("\033[1;33m");
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║ 2. Peças de Dominó                           ║\n");
    printf("╚══════════════════════════════════════════════╝\n\n");
    printf("\033[1;37m");
    printf("   - O conjunto padrão de Dominó consiste em 28 "
           "peças,\n\n");
    printf("   cada uma numerada de 0 a 6.\n\n");

    // Regra 3
    printf("\033[1;33m");
    printf("╔══════════════════════════════════════╗\n");
    printf("║ 3. Embaralhamento e Distribuição     ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
    printf("\033[1;37m");
    printf("   - As peças são embaralhadas distribuídas, e destribuidas\n");
    printf("   aleatóriamente entre os jogadores.\n");

    // Regra 4
    printf("\033[1;33m");
    printf("╔══════════════════════════════════════╗\n");
    printf("║ 4. Início do Jogo                    ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
    printf("\033[1;37m");
    printf("   - O jogador 1 inicia o jogo, colocando-a no centro da mesa.\n\n");

    // Regra 5
    printf("\033[1;33m");
    printf("╔══════════════════════════════════════╗\n");
    printf("║ 5. Jogadas Subsequentes              ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
    printf("\033[1;37m");
    printf("   - Os jogadores devem corresponder os números das\n");
    printf("   extremidades das peças na mesa.\n");
    printf("   - Por exemplo, se a extremidade exposta tem um seis,\n");
    printf("   uma peça com um seis deve ser jogada.\n\n");

    // Regra 6
    printf("\033[1;33m");
    printf("╔════════════════════════════════════════╗\n");
    printf("║ 6. Blocos e Pontuações                 ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    printf("\033[1;37m");
    printf("   - Se um jogador jogar uma peça que resulte em ambas as extremidades,\n");
    printf("   ele formará 10 pontos por peça jogada na mesa.\n");

    // Regra 7
    printf("\033[1;33m");
    printf("╔══════════════════════════════════════╗\n");
    printf("║ 7. Vitória da Rodada                 ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
    printf("\033[1;37m");
    printf("   - A rodada termina quando um jogador joga todas as suas peças\n");
    printf("   ou quando nenhum jogador pode fazer uma jogada.\n");
    printf("   - O jogador que tem maior número de pontos ganha, seus pontos são\n");
    printf("   baseados nas suas peças que foram jogadas na mesa.\n\n");

    printf("\033[1;33m");
    printf("╔══════════════════════════════════════╗\n");
    printf("║ 8. Pontuação Final                   ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
    printf("\033[1;37m");
    printf("   - O jogo é jogado por várias rodadas, e a pontuação total é "
           "somada ao longo do tempo.\n");
    printf("   - O jogador com mais pontos no final vence.\n\n");

    printf("                  ╔═══════════════════════╗\n");
    printf("                  ║ %s        Voltar     %s   ║\n", (escol == 1) ? "\033[1;31m" : "", "\033[0m");
    printf("                  ╚═══════════════════════╝\n");

    printf("\nOpção selecionada: %d\n", escol);

    tec = getch();

    // Se a tecla pressionada for "seta para cima"
    if (tec == 65) {
      if (escol > 0)
        escol--;
      op--;
    }
    // Se a tecla pressionada for "seta para baixo"
    else if (tec == 66) {
      if (escol < 1)
        escol++;
      op++;
    }
  } while (tec != 10); // 10 é o código ASCII para a tecla Enter

  if (op == 1) {
    reiniciar();
  }
}

void telaPause() {
  system ("clear");
  printf("\n\n\n\n");
  printf("\033[1;31m"); // vermelho
  printf("                    _ __ __ _ _ _ ___ ___\n");
  printf("                   | '_ \\ / _` | | | /__|/ _\\\n");
  printf("                   | |_) | (_| | |_| \\__ \\ __/\n");
  printf("                   | .__/ \\__,_|\\__,_|___/\\___|\n");
  printf("                   | |\n");
  printf("                   |_|\n\n");

  printf("\033[1;37m"); // BrancoU
  printf("                   ############################        \n");
  printf("                   ############################        \n");
  printf("                     ##                    ##          \n");
  printf("                     ##                    ##          \n");
  printf("                     ##                    ##          \n");
  printf("                      ##\033[1;33m #########    ##\033[1;97m  ##          \n");
  printf("                       ##  \033[1;33m############\033[1;97m  ##            \n");
  printf("                         ##  \033[1;33m########\033[1;97m  ##              \n");
  printf("                           ##  \033[1;33m####\033[1;97m  ##                \n");
  printf("                             ## \033[1;33m## \033[1;97m##                  \n");
  printf("                             ##  \033[1;33m#\033[1;97m  ##                  ""\n");
  printf("                           ##    \033[1;33m#\033[1;97m    ##                ""\n");
  printf("                         ##     \033[1;33m##\033[1;97m     ##              \n");
  printf("                       ##      \033[1;33m####\033[1;97m      ##            \n");
  printf("                      ##   \033[1;33m#############\033[1;97m  ##           \n");
  printf("                     ##  \033[1;33m################\033[1;97m  ##          \n");
  printf("                     ##  \033[1;33m################\033[1;97m  ##          \n");
  printf("                     ##  \033[1;33m################\033[1;97m  ##          \n");
  printf("                   ############################        \n");
  printf("                   ############################        \n");

  // Agora, aguarda até que o usuário pressione Enter para continuar
  printf("\nPressione Enter despausar...");
  if (getchar() == '\n') {
  return;
  }
}

void telaVitoria() {
  printf("\033[1;33m"); // Amarelo
  printf("                                       __\n");
  printf("                                      / /\n ");
  printf("          __      _______ _______ ____  _____  _____          \n");
  printf(
      "           \\ \\    / /_   _|__   __/ __ \\|  __ \\|_   _|   /\\    \n");
  printf(
      "            \\ \\  / /  | |    | | | |  | | |__) | | |    /  \\   \n");
  printf(
      "             \\ \\/ /   | |    | | | |  | |  _  /  | |   / /\\ \\  \n");
  printf(
      "              \\  /   _| |_   | | | |__| | | \\ \\ _| |_ / ____ \\ \n");
  printf("               \\/   |_____|  |_|  \\____/|_|  \\_\\_____/_/    "
         "\\_\\ \n");
  printf("\n\n");
  printf("\033[1;34m"); // Azul
  printf("                 $$$$$$$$$$$$$1              1$$$$$$$$$$$$1\n");
  printf("                 1$$$$$$$$$$$$$1             $$$$$$$$$$$$$\n");
  printf("                  1$$$$$$$$$$$$$            $$$$$$$$$$$$$\n");
  printf("                   1$$$$$$$$$$$$$          1$$$$$$$$$$$$\n");
  printf("                    $$$$$$$$$$$$$1        1$$$$$$$$$$$$1\n");
  printf("                     $$$$$$$$$$$$$        $$$$$$$$$$$$$\n");
  printf("                      $$$$$$$$$$$$$      $$$$$$$$$$$$$\n");
  printf("                      1$$$$$$$$$$$$1    1$$$$$$$$$$$$\n");
  printf("                       $$$$$$$$$$$$$   1$$$$$$$$$$$$1\n");
  printf("                        $$$$$$$$$$$$$ 1$$$$$$$$$$$$1\n");
  printf("                        1$$$$$$$$$$$$1$$$$$$$$$$$$\n");
  printf("                         1$$$$$$$$$$$$$$$$$$$$$$$\n");
  printf("                          $$$$$$$$$$$$$$$$$$$$$$\n");
  printf("                           $$$$$$$$$$$$$$$$$$$$\n");
  printf("                            $$$$$$$$$$$$$$$$$$\n");
  printf("                            $$$$$$$$$$$$$$$$$\n");
  printf("                             $$$$$$$$$$$$$$$\n");
  printf("                              $$$$$$$$$$$$$\n");
  printf("\033[1;37m"); // Branco
  printf("                               11111111111 \n");
  printf("                              11111111111111\n");
  printf("\033[1;33m"); // Amarelo
  printf("                           $$$11111111$$11$$$$$\n");
  printf("                         1$$11111111111$$111111$$\n");
  printf("                        1$$11111111111$$1111111$$1\n");
  printf("                        $$1111111111$$$111111111111\n");
  printf("                       11111$11111111$11$1111111$$$1\n");
  printf("                       $1111$11111      11$11111$$$$\n");
  printf("                       $$111$111  111$$   1$111111$$\n");
  printf("                       11111$$1   11111    1$111$$$1\n");
  printf("                       1$111$$      111     $111$$1\n");
  printf("                        $$111$1     1$1     $$1$$$1\n");
  printf("                        111$11$     $$1    1$1$$$$\n");
  printf("                         1$$1$$$1 1$$$$$1 1$$1$$$\n");
  printf("                          1$$$$$$$111111$$$$$$$$$\n");
  printf("                            1$$$$$$$$$$$$$$$$$\n");
  printf("                               1$$$$$$$$$$11\n");

  printf("\n\n");
  printf("\033[0m"); // padrão
}