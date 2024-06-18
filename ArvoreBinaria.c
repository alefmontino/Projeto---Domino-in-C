#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include "../include/ArvoreBinaria.h" //inclui os Prot�tipos
#include "../include/Telas.h"


ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada no
    free(raiz);//libera a raiz
}

int insere_ArvBin(ArvBin* raiz, struct pecadomino al) {
  printf("\nEu apareci");
    if (raiz == NULL)
        return 0;

    struct NO* novo = (struct NO*)malloc(sizeof(struct NO));
    if (novo == NULL)
        return 0;

    *novo->peca = al;  // Atribui a peça diretamente ao nó
    novo->dir = NULL;
    novo->esq = NULL;

    if (*raiz == NULL)
        *raiz = novo;
    else {
        struct NO* atual = *raiz;
        struct NO* ant = NULL;

        while (atual != NULL) {
            ant = atual;

            // Comparação deve ser feita com as propriedades da peça
            if (al.lado1 == atual->peca->lado1 && al.lado2 == atual->peca->lado2) {
                free(novo);
                return 0;  // Elemento já existe
            }

            // Modifiquei a comparação para considerar as propriedades da peça
            if (al.lado1 > atual->peca->lado1 || (al.lado1 == atual->peca->lado1 && al.lado2 > atual->peca->lado2))
                atual = atual->dir;
            else
                atual = atual->esq;
        }

        // Modifiquei a comparação para considerar as propriedades da peça
        if (al.lado1 > ant->peca->lado1 || (al.lado1 == ant->peca->lado1 && al.lado2 > ant->peca->lado2))
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}


// Função para carregar dados do jogo a partir de um arquivo
void carregarDadosJogo(const char* nomeArquivo, Lista* lista) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        // Tratar falha na abertura do arquivo, se necessário
        return;
    }

    struct pecadomino peca;
    while (fscanf(arquivo, "%d|%d", &peca.lado1, &peca.lado2) == 2) {
        // Insere na lista
        insere_lista_final(lista, peca);
        // Adiciona na árvore
        //*raiz = adicionarPecaNaArvore(*raiz, peca);
    }

    fclose(arquivo);
}

// Função para salvar a lista em um arquivo
void salvarListaEmArquivo(Lista* li, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        // Tratar falha na abertura do arquivo, se necessário
        return;
    }
    Elem* no = *li;
    while (no != NULL) {
        fprintf(arquivo, "%d|%d\n", no->dados.lado1, no->dados.lado2);
        no = no->prox;
    }

    fclose(arquivo);
}

// Função para salvar os dados da árvore em uma lista
void salvarDadosJogo(ArvBin* raiz, Lista* lista) {
    if (raiz == NULL || *raiz == NULL) {
        return;
    }

    struct pecadomino al;
    al.lado1 = (*raiz)->peca->lado1;
    al.lado2 = (*raiz)->peca->lado2;

    // Adiciona a peça atual na lista
    insere_lista_inicio(lista, al);

    // Chama a função recursivamente para os filhos
    salvarDadosJogo(&((*raiz)->esq), lista);
    salvarDadosJogo(&((*raiz)->dir), lista);
}


int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvBin(&((*raiz)->esq));
    int alt_dir = totalNO_ArvBin(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

int consulta_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%d\n",(*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void emOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->esq));
      printf("\n||%d|%d||", (*raiz)->peca->lado1, (*raiz)->peca->lado2);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz) {
  if (raiz == NULL)
    return;
  if (*raiz != NULL) {
    posOrdem_ArvBin(&((*raiz)->esq));
    printf("  \033[1;30m\033[47m  %d  \033[47m\033[0m\n", (*raiz)->peca->lado1);
    printf("- \033[1;30m\033[47m --- \033[47m\033[0m\n");
    printf("  \033[1;30m\033[47m  %d  \033[47m\033[0m\n\n",(*raiz)->peca->lado2);
        posOrdem_ArvBin(&((*raiz)->dir));
  }
}


ArvBin adicionarPecaNaArvore(ArvBin raiz, struct pecadomino novaPeca) {
  
    if (raiz == NULL) {
        // Aloca um novo nó e uma nova peça, e copia os dados da nova peça para o nó
        struct NO* novoNo = (struct NO*)malloc(sizeof(struct NO));
        novoNo->peca = (struct pecadomino*)malloc(sizeof(struct pecadomino));
        novoNo->peca->lado1 = novaPeca.lado1;
        novoNo->peca->lado2 = novaPeca.lado2;
        novoNo->info = novaPeca.lado1;  // Usa lado1 como chave para a BST
        novoNo->esq = NULL;
        novoNo->dir = NULL;
        //printf("\nNova peça adicionada: [%d|%d]\n", novaPeca.lado1, novaPeca.lado2);
        return novoNo;
    }

    // Compara a chave (lado1) e, se necessário, o lado2 para decidir o lado de inserção na árvore
    if (novaPeca.lado1 < raiz->info || (novaPeca.lado1 == raiz->info && novaPeca.lado2 < raiz->peca->lado2)) {
        raiz->esq = adicionarPecaNaArvore(raiz->esq, novaPeca); // Insere à esquerda
    } else if (novaPeca.lado1 > raiz->info || (novaPeca.lado1 == raiz->info && novaPeca.lado2 > raiz->peca->lado2)) {
        raiz->dir = adicionarPecaNaArvore(raiz->dir, novaPeca); // Insere à direita
    } else {
        // Ambos lado1 e lado2 são iguais; trata como peça repetida
        printf("\nPeça já existe: [%d|%d]\n", novaPeca.lado1, novaPeca.lado2);
    }

    return raiz; // Retorna a raiz atualizada após a inserção
}


// Função para remover um nó atual de uma árvore binária de busca
struct NO* remove_atual(struct NO* atual) {
    // Declarando ponteiros para nós auxiliares
    struct NO *no1, *no2;

    // Verifica se o nó atual não tem subárvore à esquerda
    if(atual->esq == NULL){
        // Nó2 recebe a subárvore à direita do nó atual
        no2 = atual->dir;
        // Libera a memória do nó atual
        free(atual);
        // Retorna a subárvore à direita para ser conectada ao pai do nó atual
        return no2;
    }

    // Inicializa os ponteiros auxiliares no1 e no2
    no1 = atual;
    no2 = atual->esq;

    // Encontra o nó mais à direita na subárvore à esquerda do nó atual
    while(no2->dir != NULL){
        // Atualiza no1 e no2 enquanto percorre a subárvore à direita
        no1 = no2;
        no2 = no2->dir;
    }

    // no2 é o nó anterior a atual na ordem esquerda-atual-direita
    // no1 é o pai de no2

    // Verifica se no1 é diferente de atual (ou seja, no2 não é o filho direito de atual)
    if(no1 != atual){
        // Atualiza o ponteiro do pai (no1) para apontar para a subárvore à esquerda de no2
        no1->dir = no2->esq;
        // Conecta a subárvore à esquerda de no2 à subárvore à esquerda de atual
        no2->esq = atual->esq;
    }

    // Conecta a subárvore à direita de no2 à subárvore à direita de atual
    no2->dir = atual->dir;

    // Libera a memória do nó atual
    free(atual);

    // Retorna o nó no2 para ser conectado ao pai do nó atual
    return no2;
}


// Função principal para remover um nó da árvore binária de busca (BST)
int remove_ArvBin(ArvBin *raiz, struct pecadomino al) {
    if (*raiz == NULL)
        return 0; // Retorna 0 se a árvore está vazia, indicando que a remoção não foi possível

    struct NO* ant = NULL;
    struct NO* atual = *raiz;

    // Procura o nó a ser removido
    while (atual != NULL) {
        if (al.lado1 == atual->info && al.lado2 == atual->peca->lado2) {
            if (atual == *raiz)
                *raiz = remove_atual(atual); // Correção: Adiciona al como segundo argumento
            else {
                if (ant->dir == atual)
                    ant->dir = remove_atual(atual); // Correção: Adiciona al como segundo argumento
                else
                    ant->esq = remove_atual(atual); // Correção: Adiciona al como segundo argumento
            }
            return 1; // Retorna 1 indicando sucesso na remoção
        }

        ant = atual;

        // Decide se deve ir para a subárvore esquerda ou direita com base na comparação de chaves
        if (al.lado1 > atual->info || (al.lado1 == atual->info && al.lado2 > atual->peca->lado2))
            atual = atual->dir; // Vai para a subárvore direita
        else
            atual = atual->esq; // Vai para a subárvore esquerda
    }

    return 0; // Retorna 0 se o nó não foi encontrado na árvore
}


int verif_exist_arv(ArvBin *raiz, struct pecadomino al) {
    if (raiz == NULL || *raiz == NULL)
        return 0; // Retorna 0 se a árvore está vazia ou se atingiu uma folha

    // Percorre a subárvore esquerda em ordem
    if (verif_exist_arv(&((*raiz)->esq), al)) {
        return 1; // Retorna 1 se a peça foi encontrada na subárvore esquerda
    }

    // Verifica se a peça atual é igual à peça desejada
    if (al.lado1 == (*raiz)->info && al.lado2 == (*raiz)->peca->lado2) {
        return 1; // Retorna 1 indicando que a peça foi encontrada
    }

    // Percorre a subárvore direita em ordem
    if (verif_exist_arv(&((*raiz)->dir), al)) {
        return 1; // Retorna 1 se a peça foi encontrada na subárvore direita
    }

    return 0; // Retorna 0 se a peça não foi encontrada na árvore
}


int somarValores(ArvBin *raiz) {
    if (raiz == NULL || *raiz == NULL) {
        return 0;
    }

    int soma_esq = somarValores(&((*raiz)->esq));
    int soma_dir = somarValores(&((*raiz)->dir));

    return soma_esq + soma_dir + (*raiz)->peca->lado1 + (*raiz)->peca->lado2;
}


int verifica_peca(ArvBin *raiz, Lista* al) {
    if (raiz == NULL || *raiz == NULL) {
        return 0;
    }

    // Verifica à esquerda
    if (verifica_peca(&((*raiz)->esq), al)) {
        return 1;
    }
    // Verifica à direita
    if (verifica_peca(&((*raiz)->dir), al)) {
        return 1;
    }

    // Verifica se a lista está vazia
    if (*al == NULL) {
        return 1; // Retorna 1 para indicar sucesso
    }

    Elem *no = *al; // Ponteiro para percorrer a lista

    // Verifica se a peça na arvore pode ser conectada ao início da lista
    if ((*raiz)->peca->lado1 == no->dados.lado1) {
        return 1; // Retorna 1 para indicar sucesso
    }

    // Verifica se a peça na arvore pode ser conectada ao início da lista sem trocar os lados
    else if ((*raiz)->peca->lado2 == no->dados.lado1) {
        return 1; // Retorna 1 para indicar sucesso
    }

    // Percorre a lista para encontrar o final
    while (no->prox != NULL) {
        no = no->prox;
    }

    // Verifica se a peça na arvore pode ser conectada ao final da lista
    if ((*raiz)->peca->lado1 == no->dados.lado2) {
        return 1; // Retorna 1 para indicar sucesso
    }

    // Verifica se a peça na arvore pode ser conectada ao final da lista com os lados trocados
    else if ((*raiz)->peca->lado2 == no->dados.lado2) {
        return 1; // Retorna 1 para indicar sucesso
    }


    return 0; // Retorna 0 se nenhuma condição for satisfeita
}

void menu_vs_cpu() {

    int escolha, cont,cont2, soma, salvar;
    int *opCPU, op, ponto1, ponto2;
    int aux1 = 0;
    struct pecadomino al;

    Lista* carregar = cria_lista();
    Lista* carregar2 = cria_lista();
    Lista* aux = cria_lista();
    Lista* aux2 = cria_lista();
    Lista* li = cria_lista();
    Lista* mesa = cria_lista();
    ArvBin *jogador = cria_ArvBin();
    ArvBin *cpu = cria_ArvBin();

  escolha = menuJogo();
  if(escolha == 1){

    printf("\nCriando peças...\n");
    criar_pecas(li);
    imprime_lista(li);

    printf("\n\nEmbaralhando peças...\n");
    embaralhar_pecas(li);

    embaralhar_pecas(li);

    embaralhar_pecas(li);

    imprime_lista(li);

    Elem *no = *li;

    printf("\n\nJogador 1:\n\n");
    for(int i = 0; i < 7; i++){
    *jogador = adicionarPecaNaArvore(*jogador,no->dados);
    no = no->prox;
    }

    printf("\n\n");
    for(int i = 0; i < 7; i++){
      remove_lista_inicio(li);
    }

    printf("\n\nJogador 2:\n\n");
    no = *li;
    for(int i = 0; i < 7; i++){
      *cpu = adicionarPecaNaArvore(*cpu,no->dados);
      no = no->prox;
    }

    for(int i = 0; i < 7; i++){
      remove_lista_inicio(li);
    }

  }

  else if(escolha == 2){
    printf("\n\nCarregando dados...\n\n");
    carregarDadosJogo("data/jogador_jogadorVScpu", carregar);
    carregarDadosJogo("data/cpu_jogadorVScpu", carregar2);
    carregarDadosJogo("data/mesa_jogadorVScpu", mesa);

    Elem* no1 = *carregar;
    while(no1 != NULL){
      *jogador = adicionarPecaNaArvore(*jogador,no1->dados);
      no1 = no1->prox;
    }

    Elem* no2 = *carregar2;
    while(no2 != NULL){
      *cpu = adicionarPecaNaArvore(*cpu,no2->dados);
      no2 = no2->prox;
    }

  }


  system("clear");
  do {
    do{
      //telaCarreg(); 
      op = menuMesa();

      switch(op){

        case 1:
          system("clear");
          if (verifica_peca(jogador, mesa)) {
            cont = 0;
            printf("\033[1;37m");// Branco
            imprime_lista(mesa);
            printf("\n🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫-MESA-🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫\n");
            printf(" 🟤                                                                                  🟤\n");
            printf(" 🟤                                                                                  🟤\n");
            printf("\033[0m"); //padrão
            printf("\033[1;34m");// Azul
            printf("\n\nVez do jogador 1:\n\n");
            printf("\033[0m"); //padrão

            posOrdem_ArvBin(jogador);
            
            do{
              printf("\n\nEscolha a peça para jogar (Exp: 1 2): ");
              scanf("%d %d", &al.lado1, &al.lado2);
              if (verif_exist_arv(jogador, al)) {
                if (insere_peca_mesa(mesa, al)) {
                  remove_ArvBin(jogador, al);
                  printf("\n\nPeça inserida na mesa...\n\n");
                  imprime_lista(mesa);
                  printf("\nPeças na mesa\n");
                  aux1 = 1;
                } else{
                printf(
                    "\nocorreu um erro, não foi possível inserir os dados na peça");
                  aux1 = 0;
                }
              } else{
                printf(
                    "O jogador 1 não tem a peça que deseja inserir na mesa...\n");
                aux1 = 0;
              }
          }while(aux1 == 0);

          } else {
            cont = 1;
            printf("\nJogador 1,você passou...\n");
            sleep(2);
          }

          if (estaVazia_ArvBin(jogador)) {
            printf("\n\nJogador 1 ganhou...\n\n");
            sleep(2);
            libera_ArvBin(jogador);
            libera_ArvBin(cpu);
            libera_lista(li);
            libera_lista(mesa);
            libera_lista(aux);
            libera_lista(aux2);
            libera_lista(carregar);
            libera_lista(carregar2);

            telaVitoria();
            sleep(2);
            return;
          }
          break;

        case 2:
          system("clear");
           ponto1 = (7 - totalNO_ArvBin(jogador))*10;
           ponto2 = (7 - totalNO_ArvBin(cpu))*10;

            printf("\033[1;33m");// amarelo
            printf("\033[47m");   // Fundo branco
            printf("╔════════════════════════════════════════════════════════╗\n");
            printf("║ ⚫ ⚫      Jogador         ║ Pontuação           ⚫ ⚫ ║\n");
            printf("══════════════════════════════════════════════════════════\n");
            printf("\033[0m");  // Resetando as configurações para o padrão
            printf("          Jogador  1         ║    %d                     \n", ponto1);
            printf("          CPU                ║    %d                     \n", ponto2);
            printf("╚════════════════════════════════════════════════════════╝\n");
            printf("\033[0m");  // Resetando as configurações para o padrão


           sleep(2);
          break;

        case 4:
          printf("\nDeseja salvar o jogo?\n1-Sim\n2-Não\n");
          scanf("%d", &salvar);

          switch(salvar){

            case 1:
              printf("\n1");
             salvarDadosJogo(jogador, aux);
              printf("\n2");
              salvarListaEmArquivo(aux,"data/jogador_jogadorVScpu");

              salvarDadosJogo(cpu,aux2);
              salvarListaEmArquivo(aux2, "data/cpu_jogadorVScpu");

              salvarListaEmArquivo(mesa, "data/mesa_jogadorVscpu");


              //printf("\n3");

              libera_ArvBin(jogador);
              libera_ArvBin(cpu);
              libera_lista(li);
              libera_lista(mesa);
              libera_lista(aux);
              libera_lista(aux2);
              libera_lista(carregar);
              libera_lista(carregar2);
              //return;
              break;

            case 2:
              libera_ArvBin(jogador);
              libera_ArvBin(cpu);
              libera_lista(li);
              libera_lista(mesa);
              libera_lista(aux);
              libera_lista(aux2);
              libera_lista(carregar);
              libera_lista(carregar2);

              //return;
              break;
          }
          break;

        default:
          printf("\nCarregando!\n");
          break;

      }
    }
      while(op != 1);

        // Vez da CPU
        sleep(2);
        system("clear");
        struct pecadomino aux;
    
        printf("\033[1;37m");// Branco
        printf("                     \033[1;34m$$$        \033[1;37m_____________\n");
        printf("                    \033[1;34m$   $      \033[1;37m|             |\n");
        printf("                     \033[1;34m$$$       \033[1;37m| Pensando.   |\n");
        printf("                     \033[1;34m$ $       \033[1;37m|_____________|\n");
        printf("                     \033[1;34m$ $\n");
        printf("                   \033[1;34m$$$ $$$\n");
        printf("                 $$  $$$  $$$\n");
        printf("               $$  $$$$$$$   $\n");
        printf("              $               $\n");
        printf("             $                 $\n");
        printf("             $                 $\n");
        printf("             $     $$$$$$$$$$$$$$$\n");
        printf("             $    $               $\n");
        printf("             $    $   $$$$$$$$$$$$$\n");
        printf("            $   $   $           $$$\n");
        printf("            $   $   $ \033[1;37m$$$   $$$  \033[1;34m$$\n");
        printf("            $   $   $ \033[1;37m$$$   $$$  \033[1;34m$$\n");
        printf("\033[1;34m");// Azul
        printf("            $   $   $           $$$\n");
        printf("            $    $   $$$$$$$$$$$$$\n");
        printf("            $     $$$$$$$$$$$$$$\n");
        printf("            $                 $\n");
        printf("            $    $$$$$$$$$$$$$$\n");
        printf("            $   $  $  $  $  $\n");
        printf("            $  $$$$$$$$$$$$$$\n");
        printf("            $  $   $  $  $  $\n");
        printf("            $   $$$$$$$$$$$$$$$\n");
        printf("           $$$                 $$$\n");
        printf("         $$   $$$         $$$$$   $$\n");
        printf("       $$        $$$$$$$$$          $$$\n");
        printf("      $  $$                     $$$$   $$\n");
        printf("   $$$$$   $$$$$$$$      $$$$$$$       $ $\n");
        printf(" $      $$         $$$$$$              $ $$\n");
        printf("$    $    $                            $ $ $\n");
        printf("$     $   $              $$$$$$$$$$$   $ $ $$\n");
        printf("$$$    $   $  $$$$$$$$$$$$          $   $ $ $$\n");
        printf("$   $$$$    $  $                     $   $ $$ $\n");
        printf("$$$    $   $$  $                     $$  $ $  $\n");
        printf("$   $  $  $$   $                      $  $$$  $\n");
        printf("$     $$ $$    $               $$$    $  $ $  $\n");
        printf("\033[0m");// padrão
    sleep(1);
        system("clear");
        printf("\033[1;37m");// Branco
        printf("                     \033[1;34m$$$        \033[1;37m_____________\n");
        printf("                    \033[1;34m$   $      \033[1;37m|             |\n");
        printf("                     \033[1;34m$$$       \033[1;37m| Pensando..  |\n");
        printf("                     \033[1;34m$ $       \033[1;37m|_____________|\n");
        printf("                     \033[1;34m$ $\n");
        printf("                   \033[1;34m$$$ $$$\n");
        printf("                 $$  $$$  $$$\n");
        printf("               $$  $$$$$$$   $\n");
        printf("              $               $\n");
        printf("             $                 $\n");
        printf("             $                 $\n");
        printf("             $     $$$$$$$$$$$$$$$\n");
        printf("             $    $               $\n");
        printf("             $    $   $$$$$$$$$$$$$\n");
        printf("            $   $   $           $$$\n");
        printf("            $   $   $ \033[1;37m           \033[1;34m$$\n");
        printf("            $   $   $ \033[1;37m$$$   $$$  \033[1;34m$$\n");
        printf("\033[1;34m");// Azul
        printf("            $   $   $           $$$\n");
        printf("            $    $   $$$$$$$$$$$$$\n");
        printf("            $     $$$$$$$$$$$$$$\n");
        printf("            $                 $\n");
        printf("            $    $$$$$$$$$$$$$$\n");
        printf("            $   $  $  $  $  $\n");
        printf("            $  $$$$$$$$$$$$$$\n");
        printf("            $  $   $  $  $  $\n");
        printf("            $   $$$$$$$$$$$$$$$\n");
        printf("           $$$                 $$$\n");
        printf("         $$   $$$         $$$$$   $$\n");
        printf("       $$        $$$$$$$$$          $$$\n");
        printf("      $  $$                     $$$$   $$\n");
        printf("   $$$$$   $$$$$$$$      $$$$$$$       $ $\n");
        printf(" $      $$         $$$$$$              $ $$\n");
        printf("$    $    $                            $ $ $\n");
        printf("$     $   $              $$$$$$$$$$$   $ $ $$\n");
        printf("$$$    $   $  $$$$$$$$$$$$          $   $ $ $$\n");
        printf("$   $$$$    $  $                     $   $ $$ $\n");
        printf("$$$    $   $$  $                     $$  $ $  $\n");
        printf("$   $  $  $$   $                      $  $$$  $\n");
        printf("$     $$ $$    $               $$$    $  $ $  $\n");
        printf("\033[0m");// padrão
    sleep(2);
        system("clear");
        printf("\033[1;37m");// Branco
        printf("                     \033[1;34m$$$        \033[1;37m_____________\n");
        printf("                    \033[1;34m$   $      \033[1;37m|             |\n");
        printf("                     \033[1;34m$$$       \033[1;37m| Pensando... |\n");
        printf("                     \033[1;34m$ $       \033[1;37m|_____________|\n");
        printf("                     \033[1;34m$ $\n");
        printf("                   \033[1;34m$$$ $$$\n");
        printf("                 $$  $$$  $$$\n");
        printf("               $$  $$$$$$$   $\n");
        printf("              $               $\n");
        printf("             $                 $\n");
        printf("             $                 $\n");
        printf("             $     $$$$$$$$$$$$$$$\n");
        printf("             $    $               $\n");
        printf("             $    $   $$$$$$$$$$$$$\n");
        printf("            $   $   $           $$$\n");
        printf("            $   $   $ \033[1;37m$$$   $$$  \033[1;34m$$\n");
        printf("            $   $   $ \033[1;37m$$$   $$$  \033[1;34m$$\n");
        printf("\033[1;34m");// Azul
        printf("            $   $   $           $$$\n");
        printf("            $    $   $$$$$$$$$$$$$\n");
        printf("            $     $$$$$$$$$$$$$$\n");
        printf("            $                 $\n");
        printf("            $    $$$$$$$$$$$$$$\n");
        printf("            $   $  $  $  $  $\n");
        printf("            $  $$$$$$$$$$$$$$\n");
        printf("            $  $   $  $  $  $\n");
        printf("            $   $$$$$$$$$$$$$$$\n");
        printf("           $$$                 $$$\n");
        printf("         $$   $$$         $$$$$   $$\n");
        printf("       $$        $$$$$$$$$          $$$\n");
        printf("      $  $$                     $$$$   $$\n");
        printf("   $$$$$   $$$$$$$$      $$$$$$$       $ $\n");
        printf(" $      $$         $$$$$$              $ $$\n");
        printf("$    $    $                            $ $ $\n");
        printf("$     $   $              $$$$$$$$$$$   $ $ $$\n");
        printf("$$$    $   $  $$$$$$$$$$$$          $   $ $ $$\n");
        printf("$   $$$$    $  $                     $   $ $$ $\n");
        printf("$$$    $   $$  $                     $$  $ $  $\n");
        printf("$   $  $  $$   $                      $  $$$  $\n");
        printf("$     $$ $$    $               $$$    $  $ $  $\n");
        printf("\033[0m");// padrão
    sleep(1);
    
        for(int i = 0; i < 7; i++){
          aux.lado1 = i;
          for(int j = 0; j < 7; j++){
            aux.lado2 = j;
            if(verif_exist_arv(cpu,aux)){
              if(insere_peca_mesa(mesa,aux)){
                remove_ArvBin(cpu,aux);
                i = 7;
                j = 7;
                cont = 1;
              }
        }   
            else {
                cont2 = cont + 1;
               // printf("\nA CPU passou...\n");
            }
      }
    }

        if (estaVazia_ArvBin(cpu)) {
            printf("\n\nA CPU ganhou...\n\n");
            libera_ArvBin(jogador);
            libera_ArvBin(cpu);
            libera_lista(li);
            libera_lista(mesa);
            //libera_lista(aux);
            libera_lista(aux2);
            libera_lista(carregar);
            libera_lista(carregar2);

          telaVitoria();
          sleep(2);
            return;
        }
    } while (cont2 != 2);
  int conta1;
  int conta2;

  conta1 = somarValores(jogador);
  conta2 = somarValores(cpu);

  printf("\nO jogador tem %d\n", conta1);
  printf("\nA CPU tem %d\n", conta2);

  if(conta1 < conta2){
    printf("\n\nO jogador ganhou\n\n");
    sleep(3);

    telaVitoria();
    sleep(3);
  }

  else if(conta1 > conta2){
    printf("\n\nA CPU ganhou\n\n");
    sleep(3);

    telaVitoria();
    sleep(3);
  }

  else{
    printf("\n\nEmpate\n\n");
    telaEmpate();
    sleep(3);
  }
  
  libera_ArvBin(jogador);
  libera_ArvBin(cpu);
  libera_lista(li);
  libera_lista(mesa);
  libera_lista(aux);
  libera_lista(aux2);
  libera_lista(carregar);
  libera_lista(carregar2);
}


void menu_2_jogadores()  {

  int escolha;

  int escolha1, escolha2, cont1,cont2, soma1, soma2;
  int op, op2;
  int pont1 = 0, pont2 = 0;
  int salvar;
  int ponto1;
  int ponto2;
  int sup1 = 0, sup2 = 0;
  struct pecadomino al;

  Lista* carregar = cria_lista();
  Lista* carregar2 = cria_lista();
  Lista* aux = cria_lista();
  Lista* aux2 = cria_lista();
  Lista* li = cria_lista();
  Lista* mesa = cria_lista();
  ArvBin *jogador1 = cria_ArvBin();
  ArvBin *jogador2 = cria_ArvBin();

  escolha = menuJogo();
  if(escolha == 1){

    printf("\nCriando peças...\n");
    criar_pecas(li);
    imprime_lista(li);

    printf("\n\nEmbaralhando peças...\n");
    embaralhar_pecas(li);

    embaralhar_pecas(li);

    embaralhar_pecas(li);

    imprime_lista(li);

    Elem *no = *li;

    printf("\n\nJogador 1:\n\n");
    for(int i = 0; i < 7; i++){
    *jogador1 = adicionarPecaNaArvore(*jogador1,no->dados);
    no = no->prox;
    }

    printf("\n\n");
    for(int i = 0; i < 7; i++){
      remove_lista_inicio(li);
    }

    printf("\n\nJogador 2:\n\n");
    no = *li;
    for(int i = 0; i < 7; i++){
      *jogador2 = adicionarPecaNaArvore(*jogador2,no->dados);
      no = no->prox;
    }

    for(int i = 0; i < 7; i++){
      remove_lista_inicio(li);
    }

  }

  else if(escolha == 2){
    printf("\n\nCarregando dados...\n\n");
    carregarDadosJogo("data/jogador1_2jogadores", carregar);
    carregarDadosJogo("data/jogador2_2jogadores", carregar2);
    carregarDadosJogo("data/mesa_2jogadores", mesa);

    Elem* no1 = *carregar;
    while(no1 != NULL){
      *jogador1 = adicionarPecaNaArvore(*jogador1,no1->dados);
      no1 = no1->prox;
    }

    Elem* no2 = *carregar2;
    while(no2 != NULL){
      *jogador2 = adicionarPecaNaArvore(*jogador2,no2->dados);
      no2 = no2->prox;
    }
  }
  
  system("clear");
  
do{
  
  do{
    //telaCarreg(); 
    op = menuMesa();
    
    switch(op){

      case 1:
        system("clear");
        if (verifica_peca(jogador1, mesa)) {
          cont1 = 0;
          imprime_lista(mesa);
          printf("\n🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫-MESA-🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫\n");
          printf(" 🟤                                                                                  🟤\n");
          printf(" 🟤                                                                                  🟤\n");
          printf("\033[0m"); //padrão
          printf("\033[1;34m");// Azul
          printf("\n\nVez do jogador 1:\n\n");
          printf("\033[0m"); //padrão

          posOrdem_ArvBin(jogador1);
          
          do{
            printf("\n\nEscolha a peça para jogar (Exp: 1 2): ");
            scanf("%d %d", &al.lado1, &al.lado2);
            if (verif_exist_arv(jogador1, al)) {
              if (insere_peca_mesa(mesa, al)) {
                remove_ArvBin(jogador1, al);
                printf("\n\nPeça inserida na mesa...\n\n");
                imprime_lista(mesa);
                printf("\nPeças na mesa\n");
                sleep(2);
                sup1 = 1;
              } else{
              printf(
                  "\nocorreu um erro, não foi possível inserir os dados na peça");
                sleep(2);
                sup1 = 0;
              }
            } else{
              printf(
                  "O jogador 1 não tem a peça que deseja inserir na mesa...\n");
          sleep(2);
              sup1 = 0;
          }
        }  while(sup1 == 0);
        } else {
          cont1++;
          printf("\nJogador 1,você passou...\n");
          sleep(2);
        }

        if (estaVazia_ArvBin(jogador1)) {
          printf("\n\nJogador 1 ganhou...\n\n");
          sleep(2);
          libera_ArvBin(jogador1);
          libera_ArvBin(jogador2);
          libera_lista(li);
          libera_lista(mesa);
          libera_lista(aux);
          libera_lista(aux2);
          libera_lista(carregar);
          libera_lista(carregar2);

          telaVitoria();
          sleep(2);
          return;
        }
        break;

      case 2:
        system("clear");
         ponto1 = (7 - totalNO_ArvBin(jogador1))*10;
         ponto2 = (7 - totalNO_ArvBin(jogador2))*10;
        
          printf("\033[1;33m");// amarelo
          printf("\033[47m");   // Fundo branco
          printf("╔════════════════════════════════════════════════════════╗\n");
          printf("║ ⚫ ⚫      Jogador         ║ Pontuação           ⚫ ⚫ ║\n");
          printf("══════════════════════════════════════════════════════════\n");
          printf("\033[0m");  // Resetando as configurações para o padrão
          printf("          Jogador  1         ║    %d                     \n", ponto1);
          printf("          Jogador  2         ║    %d                     \n", ponto2);
          printf("╚════════════════════════════════════════════════════════╝\n");
          printf("\033[0m");  // Resetando as configurações para o padrão

        
         sleep(2);
        break;

      case 4:
        printf("\nDeseja salvar o jogo?\n1-Sim\n2-Não\n");
        scanf("%d", &salvar);

        switch(salvar){

          case 1:

           salvarDadosJogo(jogador1, aux);
            salvarListaEmArquivo(aux,"data/jogador1_2jogadores");

            salvarDadosJogo(jogador2,aux2);
            salvarListaEmArquivo(aux2, "data/jogador2_2jogadores");

            salvarListaEmArquivo(mesa, "data/mesa_2jogadores");
            
            libera_ArvBin(jogador1);
            libera_ArvBin(jogador2);
            libera_lista(li);
            libera_lista(mesa);
            libera_lista(aux);
            libera_lista(aux2);
            libera_lista(carregar);
            libera_lista(carregar2);
            return;
            break;

          case 2:
            libera_ArvBin(jogador1);
            libera_ArvBin(jogador2);
            libera_lista(li);
            libera_lista(mesa);
            libera_lista(aux);
            libera_lista(aux2);
            libera_lista(carregar);
            libera_lista(carregar2);

            return;
            break;
        }
        break;

      default:
        printf("\nCarregando!\n");
        break;

    }
  }
    while(op != 1);

  
  //inicia as decisões do jogador 2
  do{

    printf("\n\nVez do jogador 2\n\n");
    sleep(2);
    op2 = menuMesa();
    switch(op2){

      case 1:
        // vez do jogador 2
        sleep(2);
        system("clear");
        if (verifica_peca(jogador2, mesa)) {
          cont2 = 0;
          imprime_lista(mesa);
          printf("\n🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫-MESA-🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫\n");
          printf(" 🟤                                                                                  🟤\n");
          printf(" 🟤                                                                                  🟤\n");
          printf("\033[0m"); //padrão
          printf("\033[1;31m");// vermelho
          printf("\n\nVez do jogador 2:\n\n");
          printf("\033[0m"); //padrão
          posOrdem_ArvBin(jogador2);

          do{
            printf("\n\nEscolha a peça para jogar (Exp: 1 2): ");
            scanf("%d %d", &al.lado1, &al.lado2);
            if (verif_exist_arv(jogador2, al)) {
              if (insere_peca_mesa(mesa, al)) {
                remove_ArvBin(jogador2, al);
                printf("\n\nPeça inserida na mesa...\n\n");
                imprime_lista(mesa);
                printf("\n\nPeças na mesa\n\n");
                sleep(2);
                sup2 = 1;
              } else{
                printf("\nocorreu um erro, não foi possível inserir os dados na "
                       "peça");
              sleep(2);
                sup2 = 0;
            }
            } else{
              printf(
                  "O jogador 1 não tem a peça que deseja inserir na mesa...\n");
              sleep(2);
              sup2 = 0;
            }
          }
             while(sup2 == 0);
        }
            else {
          cont2 = cont1 + 1;
          printf("\nJogador 2,você passou...\n");
          sleep(2);
        }

        if (estaVazia_ArvBin(jogador2)) {
          printf("\n\nJogador 2 ganhou...\n\n");
          sleep(2);
          libera_ArvBin(jogador1);
          libera_ArvBin(jogador2);
          libera_lista(li);
          libera_lista(mesa);
          libera_lista(aux);
          libera_lista(aux2);
          libera_lista(carregar);
          libera_lista(carregar2);
          
          telaVitoria();
          sleep(3);
          return;
        }
        break;

      case 2:
        system("clear");
         ponto1 = (7 - totalNO_ArvBin(jogador1))*10;
         ponto2 = (7 - totalNO_ArvBin(jogador2))*10;

          printf("\033[1;33m");// amarelo
          printf("\033[47m");   // Fundo branco
          printf("╔════════════════════════════════════════════════════════╗\n");
          printf("║ ⚫ ⚫      Jogador         ║ Pontuação           ⚫ ⚫ ║\n");
          printf("══════════════════════════════════════════════════════════\n");
          printf("\033[0m");  // Resetando as configurações para o padrão
          printf("          Jogador  1         ║    %d                     \n", ponto1);
          printf("          Jogador  2         ║    %d                     \n", ponto2);
          printf("╚════════════════════════════════════════════════════════╝\n");
          printf("\033[0m");  // Resetando as configurações para o padrão


         sleep(2);
        break;

      case 4:
        printf("\nDeseja salvar o jogo?\n1-Sim\n2-Não\n");
        scanf("%d", &salvar);

        switch(salvar){

          case 1:

             salvarDadosJogo(jogador1, aux);
              salvarListaEmArquivo(aux,"data/jogador1_2jogadores");

              salvarDadosJogo(jogador2,aux2);
              salvarListaEmArquivo(aux2, "data/jogador2_2jogadores");

              salvarListaEmArquivo(mesa, "data/mesa_2jogadores");

              libera_ArvBin(jogador1);
              libera_ArvBin(jogador2);
              libera_lista(li);
              libera_lista(mesa);
              libera_lista(aux);
              libera_lista(aux2);
              libera_lista(carregar);
              libera_lista(carregar2);
            
              return;
              break;
          
          case 2:
            libera_ArvBin(jogador1);
            libera_ArvBin(jogador2);
            libera_lista(li);
            libera_lista(mesa);
            libera_lista(aux);
            libera_lista(aux2);
            libera_lista(carregar);
            libera_lista(carregar2);
            
            return;
            break;
        }
        break;

      default:
        printf("\nCarregando!\n");
        break;

    }
  }
    while(op2 != 1);


}
  while(cont2 != 2);

  soma1 = somarValores(jogador1);
  soma2 = somarValores(jogador2);

  printf("Peças do jogador 1: %d\n", soma1);
  printf("Peças do jogador 2: %d\n", soma2);

  if(soma1 < soma2){
    printf("\n\nParabéns jogador 1 você ganhou!\n\n");
    sleep(2);
    telaVitoria();
  }
  else if(soma1 > soma2){
    printf("\n\nParabéns jogador 2 você ganhou!\n\n");
    sleep(2);
    telaVitoria();
  }  
  else{
    printf("Empate...\n");
    sleep(2);
    telaEmpate();
    sleep(2);
  }  

  libera_ArvBin(jogador1);
  libera_ArvBin(jogador2);
  libera_lista(li);
  libera_lista(mesa);
  libera_lista(aux);
  libera_lista(aux2);
  libera_lista(carregar);
  libera_lista(carregar2);
  
  
  sleep(3);

}

  void menu_3_jogadores() {
    int escolha;
    int cont1, cont2, cont3, soma1, soma2, soma3;
    int op, op2, op3;
    int salvar;
    int ponto1,ponto2, ponto3;

    struct pecadomino al;

    Lista *carregar1 = cria_lista();
    Lista *carregar2 = cria_lista();
    Lista *carregar3 = cria_lista();
    Lista *aux1 = cria_lista();
    Lista *aux2 = cria_lista();
    Lista *aux3 = cria_lista();
    Lista *li = cria_lista();
    Lista *mesa = cria_lista();
    ArvBin *jogador1 = cria_ArvBin();
    ArvBin *jogador2 = cria_ArvBin();
    ArvBin *jogador3 = cria_ArvBin();

    escolha = menuJogo();

    if (escolha == 1) {
      printf("\nCriando peças...\n");
      criar_pecas(li);
     //imprime_lista(li);

      printf("\n\nEmbaralhando peças...\n");
      embaralhar_pecas(li);

      embaralhar_pecas(li);

      embaralhar_pecas(li);

    //imprime_lista(li);

      Elem *no = *li;

      printf("\n\nJogador 1:\n\n");
      for (int i = 0; i < 7; i++) {
        *jogador1 = adicionarPecaNaArvore(*jogador1, no->dados);
        no = no->prox;
      }

      printf("\n\n");
      for (int i = 0; i < 7; i++) {
        remove_lista_inicio(li);
      }

      printf("\n\nJogador 2:\n\n");
      no = *li;
      for (int i = 0; i < 7; i++) {
        *jogador2 = adicionarPecaNaArvore(*jogador2, no->dados);
        no = no->prox;
      }

      for (int i = 0; i < 7; i++) {
        remove_lista_inicio(li);
      }

      printf("\n\nJogador 3:\n\n");
      no = *li;
      for (int i = 0; i < 7; i++) {
        *jogador3 = adicionarPecaNaArvore(*jogador3, no->dados);
        no = no->prox;
      }

      for (int i = 0; i < 7; i++) {
        remove_lista_inicio(li);
      }
    } else if (escolha == 2) {
      printf("\n\nCarregando dados...\n\n");
      carregarDadosJogo("data/jogador1_3jogadores", carregar1);
      carregarDadosJogo("data/jogador2_3jogadores", carregar2);
      carregarDadosJogo("data/jogador3_3jogadores", carregar3);
      carregarDadosJogo("data/mesa_3jogadores", mesa);

      Elem *no1 = *carregar1;
      while (no1 != NULL) {
        *jogador1 = adicionarPecaNaArvore(*jogador1, no1->dados);
        no1 = no1->prox;
      }

      Elem *no2 = *carregar2;
      while (no2 != NULL) {
        *jogador2 = adicionarPecaNaArvore(*jogador2, no2->dados);
        no2 = no2->prox;
      }

      Elem *no3 = *carregar3;
      while (no3 != NULL) {
        *jogador3 = adicionarPecaNaArvore(*jogador3, no3->dados);
        no3 = no3->prox;
      }
    }

    system("clear");
    do{
      
      do{
        op = menuMesa();

        switch(op){

          case 1:
            system("clear");
            if (verifica_peca(jogador1, mesa)) {
              cont1 = 0;
              imprime_lista(mesa);
              printf("\n🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫-MESA-🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫\n");
              printf(" 🟤                                                                                  🟤\n");
              printf(" 🟤                                                                                  🟤\n");
              printf("\033[0m"); //padrão
              printf("\033[1;34m");// Azul
              printf("\n\nVez do jogador 1:\n\n");
              printf("\033[0m"); //padrão

              posOrdem_ArvBin(jogador1);

                printf("\n\nEscolha a peça para jogar (Exp: 1 2): ");
                scanf("%d %d", &al.lado1, &al.lado2);
                if (verif_exist_arv(jogador1, al)) {
                  if (insere_peca_mesa(mesa, al)) {
                    remove_ArvBin(jogador1, al);
                    printf("\n\nPeça inserida na mesa...\n\n");
                    imprime_lista(mesa);
                    printf("\nPeças na mesa\n");
                  } else
                  printf(
                      "\nocorreu um erro, não foi possível inserir os dados na peça");
                } else
                  printf(
                      "O jogador 1 não tem a peça que deseja inserir na mesa...\n");

            } else {
              cont1++;
              printf("\nJogador 1,você passou...\n");
              sleep(2);
            }

            if (estaVazia_ArvBin(jogador1)) {
              printf("\n\nJogador 1 ganhou...\n\n");
              sleep(2);
              libera_ArvBin(jogador1);
              libera_ArvBin(jogador2);
              libera_ArvBin(jogador3);
              libera_lista(li);
              libera_lista(mesa);
              libera_lista(aux1);
              libera_lista(aux2);
              libera_lista(aux3);
              libera_lista(carregar1);
              libera_lista(carregar2);
              libera_lista(carregar3);

              telaVitoria();
              sleep(2);
              return;
            }
            break;

          case 2:
            system("clear");
            ponto1 = (7 - totalNO_ArvBin(jogador1)) * 10;
            ponto2 = (7 - totalNO_ArvBin(jogador2)) * 10;
            ponto3 = (7 - totalNO_ArvBin(jogador3)) * 10;

            printf("\033[1;33m");// amarelo
            printf("\033[47m");   // Fundo branco
            printf("╔════════════════════════════════════════════════════════╗\n");
            printf("║ ⚫ ⚫      Jogador         ║ Pontuação           ⚫ ⚫ ║\n");
            printf("══════════════════════════════════════════════════════════\n");
            printf("\033[0m");  // Resetando as configurações para o padrão
            printf("          Jogador  1         ║    %d                     \n", ponto1);
            printf("          Jogador  2         ║    %d                     \n", ponto2);
            printf("          Jogador  3         ║    %d                     \n", ponto3);
            printf("╚════════════════════════════════════════════════════════╝\n");
            printf("\033[0m");  // Resetando as configurações para o padrão

             sleep(2);
            break;

          case 4:
            printf("\nDeseja salvar o jogo?\n1-Sim\n2-Não\n");
            scanf("%d", &salvar);

            switch(salvar){

              case 1:
                printf("\n1");
                salvarDadosJogo(jogador1, aux1);
                printf("\n2");
                salvarListaEmArquivo(aux1, "data/jogador1_3jogadores");

                salvarDadosJogo(jogador2, aux2);
                salvarListaEmArquivo(aux2, "data/jogador2_3jogadores");

                salvarDadosJogo(jogador3, aux3);
                salvarListaEmArquivo(aux3, "data/jogador3_3jogadores");

                salvarListaEmArquivo(mesa, "data/mesa_3jogadores");

                printf("\n3");

                libera_ArvBin(jogador1);
                libera_ArvBin(jogador2);
                libera_ArvBin(jogador3);
                libera_lista(li);
                libera_lista(mesa);
                libera_lista(aux1);
                libera_lista(aux2);
                libera_lista(aux3);
                libera_lista(carregar1);
                libera_lista(carregar2);
                libera_lista(carregar3);
                return;
                break;

              case 2:
                libera_ArvBin(jogador1);
                libera_ArvBin(jogador2);
                libera_ArvBin(jogador3);
                libera_lista(li);
                libera_lista(mesa);
                libera_lista(aux1);
                libera_lista(aux2);
                libera_lista(aux3);
                libera_lista(carregar1);
                libera_lista(carregar2);
                libera_lista(carregar3);

                return;
                break;
            }
            break;

          default:
            printf("\nCarregando!\n");
            break;

        }
      }
        while(op != 1);


      do{
        //telaCarreg(); 
        op2 = menuMesa();

        switch(op2){

          case 1:
            system("clear");
            if (verifica_peca(jogador2, mesa)) {
              cont1 = 0;
              imprime_lista(mesa);
              printf("\n🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫-MESA-🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫\n");
              printf(" 🟤                                                                                  🟤\n");
              printf(" 🟤                                                                                  🟤\n");
              printf("\033[0m"); //padrão
              printf("\033[1;31m");// vermelho
              printf("\n\nVez do jogador 2:\n\n");
              printf("\033[0m"); //padrão

              posOrdem_ArvBin(jogador2);

                printf("\n\nEscolha a peça para jogar (Exp: 1 2): ");
                scanf("%d %d", &al.lado1, &al.lado2);
                if (verif_exist_arv(jogador2, al)) {
                  if (insere_peca_mesa(mesa, al)) {
                    remove_ArvBin(jogador2, al);
                    printf("\n\nPeça inserida na mesa...\n\n");
                    imprime_lista(mesa);
                    printf("\nPeças na mesa\n");
                  } else
                  printf(
                      "\nocorreu um erro, não foi possível inserir os dados na peça");
                } else
                  printf(
                      "O jogador 2 não tem a peça que deseja inserir na mesa...\n");

            } else {
              cont2 = cont1 + 1;
              printf("\nJogador 2,você passou...\n");
              sleep(2);
            }

            if (estaVazia_ArvBin(jogador2)) {
              printf("\n\nJogador 2 ganhou...\n\n");
              sleep(2);
              libera_ArvBin(jogador1);
              libera_ArvBin(jogador2);
              libera_ArvBin(jogador3);
              libera_lista(li);
              libera_lista(mesa);
              libera_lista(aux1);
              libera_lista(aux2);
              libera_lista(aux3);
              libera_lista(carregar1);
              libera_lista(carregar2);
              libera_lista(carregar3);

              telaVitoria();
              sleep(2);
              return;
            }
            break;

          case 2:
            system("clear");
            ponto1 = (7 - totalNO_ArvBin(jogador1)) * 10;
            ponto2 = (7 - totalNO_ArvBin(jogador2)) * 10;
            ponto3 = (7 - totalNO_ArvBin(jogador3)) * 10;

            printf("\033[1;33m");// amarelo
            printf("\033[47m");   // Fundo branco
            printf("╔════════════════════════════════════════════════════════╗\n");
            printf("║ ⚫ ⚫      Jogador         ║ Pontuação           ⚫ ⚫ ║\n");
            printf("══════════════════════════════════════════════════════════\n");
            printf("\033[0m");  // Resetando as configurações para o padrão
            printf("          Jogador  1         ║    %d                     \n", ponto1);
            printf("          Jogador  2         ║    %d                     \n", ponto2);
            printf("          Jogador  3         ║    %d                     \n", ponto3);
            printf("╚════════════════════════════════════════════════════════╝\n");
            printf("\033[0m");  // Resetando as configurações para o padrão

             sleep(2);
            break;

          case 4:
            printf("\nDeseja salvar o jogo?\n1-Sim\n2-Não\n");
            scanf("%d", &salvar);

            switch(salvar){

              case 1:
                printf("\n1");
                salvarDadosJogo(jogador1, aux1);
                printf("\n2");
                salvarListaEmArquivo(aux1, "data/jogador1_3jogadores");

                salvarDadosJogo(jogador2, aux2);
                salvarListaEmArquivo(aux2, "data/jogador2_3jogadores");

                salvarDadosJogo(jogador3, aux3);
                salvarListaEmArquivo(aux3, "data/jogador3_3jogadores");

                salvarListaEmArquivo(mesa, "data/mesa_3jogadores");

                printf("\n3");

                libera_ArvBin(jogador1);
                libera_ArvBin(jogador2);
                libera_ArvBin(jogador3);
                libera_lista(li);
                libera_lista(mesa);
                libera_lista(aux1);
                libera_lista(aux2);
                libera_lista(aux3);
                libera_lista(carregar1);
                libera_lista(carregar2);
                libera_lista(carregar3);
                return;
                break;

              case 2:
                libera_ArvBin(jogador1);
                libera_ArvBin(jogador2);
                libera_ArvBin(jogador3);
                libera_lista(li);
                libera_lista(mesa);
                libera_lista(aux1);
                libera_lista(aux2);
                libera_lista(aux3);
                libera_lista(carregar1);
                libera_lista(carregar2);
                libera_lista(carregar3);
                return;
                break;
            }
            break;

          default:
            printf("\nCarregando!\n");
            break;

        }
      }
        while(op2 != 1);

      do{
        //telaCarreg(); 
        op3 = menuMesa();

        switch(op3){

          case 1:
            system("clear");
            if (verifica_peca(jogador3, mesa)) {
              cont1 = 0;
              imprime_lista(mesa);
              printf("\n🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫-MESA-🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫\n");
              printf(" 🟤                                                                                  🟤\n");
              printf(" 🟤                                                                                  🟤\n");
              printf("\033[0m"); //padrão
              printf("\033[1;32m");// Verde
              printf("\n\nVez do jogador 3:\n\n");
              printf("\033[0m"); //padrão

              posOrdem_ArvBin(jogador3);

                printf("\n\nEscolha a peça para jogar (Exp: 1 2): ");
                scanf("%d %d", &al.lado1, &al.lado2);
                if (verif_exist_arv(jogador3, al)) {
                  if (insere_peca_mesa(mesa, al)) {
                    remove_ArvBin(jogador3, al);
                    printf("\n\nPeça inserida na mesa...\n\n");
                    imprime_lista(mesa);
                    printf("\nPeças na mesa\n");
                  } else
                  printf(
                      "\nocorreu um erro, não foi possível inserir os dados na peça");
                } else
                  printf(
                      "O jogador 3 não tem a peça que deseja inserir na mesa...\n");

            } else {
              cont3 = cont2 + 1;
              printf("\nJogador 3,você passou...\n");
              sleep(2);
            }

            if (estaVazia_ArvBin(jogador3)) {
              printf("\n\nJogador 3 ganhou...\n\n");
              sleep(2);
              libera_ArvBin(jogador1);
              libera_ArvBin(jogador2);
              libera_ArvBin(jogador3);
              libera_lista(li);
              libera_lista(mesa);
              libera_lista(aux1);
              libera_lista(aux2);
              libera_lista(aux3);
              libera_lista(carregar1);
              libera_lista(carregar2);
              libera_lista(carregar3);

              telaVitoria();
              sleep(2);
              return;
            }
            break;

          case 2:
            system("clear");
            ponto1 = (7 - totalNO_ArvBin(jogador1)) * 10;
            ponto2 = (7 - totalNO_ArvBin(jogador2)) * 10;
            ponto3 = (7 - totalNO_ArvBin(jogador3)) * 10;

            printf("\033[1;33m");// amarelo
            printf("\033[47m");   // Fundo branco
            printf("╔════════════════════════════════════════════════════════╗\n");
            printf("║ ⚫ ⚫      Jogador         ║ Pontuação           ⚫ ⚫ ║\n");
            printf("══════════════════════════════════════════════════════════\n");
            printf("\033[0m");  // Resetando as configurações para o padrão
            printf("          Jogador  1         ║    %d                     \n", ponto1);
            printf("          Jogador  2         ║    %d                     \n", ponto2);
            printf("          Jogador  3         ║    %d                     \n", ponto3);
            printf("╚════════════════════════════════════════════════════════╝\n");
            printf("\033[0m");  // Resetando as configurações para o padrão

             sleep(2);
            break;

          case 4:
            printf("\nDeseja salvar o jogo?\n1-Sim\n2-Não\n");
            scanf("%d", &salvar);

            switch(salvar){

              case 1:
                printf("\n1");
                salvarDadosJogo(jogador1, aux1);
                printf("\n2");
                salvarListaEmArquivo(aux1, "data/jogador1_3jogadores");

                salvarDadosJogo(jogador2, aux2);
                salvarListaEmArquivo(aux2, "data/jogador2_3jogadores");

                salvarDadosJogo(jogador3, aux3);
                salvarListaEmArquivo(aux3, "data/jogador3_3jogadores");

                salvarListaEmArquivo(mesa, "data/mesa_3jogadores");

                printf("\n3");

                libera_ArvBin(jogador1);
                libera_ArvBin(jogador2);
                libera_ArvBin(jogador3);
                libera_lista(li);
                libera_lista(mesa);
                libera_lista(aux1);
                libera_lista(aux2);
                libera_lista(aux3);
                libera_lista(carregar1);
                libera_lista(carregar2);
                libera_lista(carregar3);
                return;
                break;

              case 2:
                libera_ArvBin(jogador1);
                libera_ArvBin(jogador2);
                libera_ArvBin(jogador3);
                libera_lista(li);
                libera_lista(mesa);
                libera_lista(aux1);
                libera_lista(aux2);
                libera_lista(aux3);
                libera_lista(carregar1);
                libera_lista(carregar2);
                libera_lista(carregar3);
                return;
                break;
            }
            break;

          default:
            printf("\nCarregando!\n");
            break;

        }
      }
        while(op3 != 1);
    }
      while(cont3 != 3);

    soma1 = somarValores(jogador1);
    soma2 = somarValores(jogador2);
    soma3 = somarValores(jogador3);

    printf("Peças do jogador 1: %d\n", soma1);
    printf("Peças do jogador 2: %d\n", soma2);
    printf("Peças do jogador 3: %d\n", soma3);

    if (soma1 < soma2 && soma1 < soma3) {
      printf("\n\nParabéns jogador 1 você ganhou!\n\n");
      sleep(2);
      telaVitoria();
    } else if (soma2 < soma1 && soma2 < soma3) {
      printf("\n\nParabéns jogador 2 você ganhou!\n\n");
      sleep(2);
      telaVitoria();
    } else if (soma3 < soma1 && soma3 < soma2) {
      printf("\n\nParabéns jogador 3 você ganhou!\n\n");
      sleep(2);
      telaVitoria();
    } else {
      printf("Empate...\n");
      sleep(2);
      telaEmpate();
      sleep(2);
    }

    libera_ArvBin(jogador1);
    libera_ArvBin(jogador2);
    libera_ArvBin(jogador3);
    libera_lista(li);
    libera_lista(mesa);
    libera_lista(aux1);
    libera_lista(aux2);
    libera_lista(aux3);
    libera_lista(carregar1);
    libera_lista(carregar2);
    libera_lista(carregar3);

    sleep(3);

  }

 void menu_4_jogadores(){

  int escolha;
  int cont1, cont2, cont3, cont4, soma1, soma2, soma3, soma4;
  int op, op2, op3, op4;
  int salvar;
  int ponto1, ponto2, ponto3, ponto4;

   struct pecadomino al;

 Lista *carregar1 = cria_lista();
   Lista *carregar2 = cria_lista();
  Lista *carregar3 = cria_lista();
  Lista *carregar4 = cria_lista();
  Lista *aux1 = cria_lista();
  Lista *aux2 = cria_lista();
   Lista *aux3 = cria_lista();
   Lista *aux4 = cria_lista();
   Lista *li = cria_lista();
  Lista *mesa = cria_lista();
   ArvBin *jogador1 = cria_ArvBin();
   ArvBin *jogador2 = cria_ArvBin();
   ArvBin *jogador3 = cria_ArvBin();
  ArvBin *jogador4 = cria_ArvBin();

   escolha = menuJogo();

   if (escolha == 1) {
     printf("\nCriando peças...\n");
     criar_pecas(li);
     imprime_lista(li);

     printf("\n\nEmbaralhando peças...\n");
     embaralhar_pecas(li);

     embaralhar_pecas(li);

     embaralhar_pecas(li);

     imprime_lista(li);

     Elem *no = *li;

     printf("\n\nJogador 1:\n\n");
     for (int i = 0; i < 7; i++) {
       *jogador1 = adicionarPecaNaArvore(*jogador1, no->dados);
       no = no->prox;
     }

     printf("\n\n");
     for (int i = 0; i < 7; i++) {
       remove_lista_inicio(li);
     }

     printf("\n\nJogador 2:\n\n");
     no = *li;
     for (int i = 0; i < 7; i++) {
       *jogador2 = adicionarPecaNaArvore(*jogador2, no->dados);
       no = no->prox;
     }

     for (int i = 0; i < 7; i++) {
       remove_lista_inicio(li);
     }

     printf("\n\nJogador 3:\n\n");
     no = *li;
     for (int i = 0; i < 7; i++) {
       *jogador3 = adicionarPecaNaArvore(*jogador3, no->dados);
       no = no->prox;
     }

     for (int i = 0; i < 7; i++) {
       remove_lista_inicio(li);
     }

     printf("\n\nJogador 4:\n\n");
     no = *li;
     for (int i = 0; i < 7; i++) {
       *jogador4 = adicionarPecaNaArvore(*jogador4, no->dados);
       no = no->prox;
     }

     for (int i = 0; i < 7; i++) {
       remove_lista_inicio(li);
     }
   } else if (escolha == 2) {
     printf("\n\nCarregando dados...\n\n");
    carregarDadosJogo("data/jogador1_4jogadores", carregar1);
   carregarDadosJogo("data/jogador2_4jogadores", carregar2);
   carregarDadosJogo("data/jogador3_4jogadores", carregar3);
  carregarDadosJogo("data/jogador4_4jogadores", carregar4);  // Load data for player4
  carregarDadosJogo("data/mesa_4jogadores", mesa);

     Elem *no1 = *carregar1;
     while (no1 != NULL) {
       *jogador1 = adicionarPecaNaArvore(*jogador1, no1->dados);
       no1 = no1->prox;
     }

     Elem *no2 = *carregar2;
     while (no2 != NULL) {
       *jogador2 = adicionarPecaNaArvore(*jogador2, no2->dados);
       no2 = no2->prox;
     }

     Elem *no3 = *carregar3;
     while (no3 != NULL) {
       *jogador3 = adicionarPecaNaArvore(*jogador3, no3->dados);
       no3 = no3->prox;
     }

     Elem *no4 = *carregar4;
     while (no4 != NULL) {
       *jogador4 = adicionarPecaNaArvore(*jogador4, no4->dados);
       no4 = no4->prox;
     }
   }
   system("clear");

   do{
     do{
     op = menuMesa();

       switch(op){

         case 1:
           system("clear");
           if (verifica_peca(jogador1, mesa)) {
             cont1 = 0;
             imprime_lista(mesa);
             printf("\n🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫-MESA-🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫\n");
             printf(" 🟤                                                                                  🟤\n");
             printf(" 🟤                                                                                  🟤\n");
             printf("\033[0m"); //padrão
             printf("\033[1;34m");// Azul
             printf("\n\nVez do jogador 1:\n\n");
             printf("\033[0m"); //padrão

             posOrdem_ArvBin(jogador1);

               printf("\n\nEscolha a peça para jogar (Exp: 1 2): ");
               scanf("%d %d", &al.lado1, &al.lado2);
               if (verif_exist_arv(jogador1, al)) {
                 if (insere_peca_mesa(mesa, al)) {
                   remove_ArvBin(jogador1, al);
                   printf("\n\nPeça inserida na mesa...\n\n");
                   imprime_lista(mesa);
                   printf("\nPeças na mesa\n");
                 } else
                 printf(
                     "\nocorreu um erro, não foi possível inserir os dados na peça");
               } else
                 printf(
                     "O jogador 1 não tem a peça que deseja inserir na mesa...\n");

           } else {
             cont1++;
             printf("\nJogador 1,você passou...\n");
             sleep(2);
           }

           if (estaVazia_ArvBin(jogador1)) {
             printf("\n\nJogador 1 ganhou...\n\n");
             sleep(2);
              libera_ArvBin(jogador1);
              libera_ArvBin(jogador2);
              libera_ArvBin(jogador3);
              libera_ArvBin(jogador4);

              libera_lista(li);
              libera_lista(mesa);
              libera_lista(aux1);
              libera_lista(aux2);
              libera_lista(aux3);
              libera_lista(aux4);
              libera_lista(carregar1);
              libera_lista(carregar2);
              libera_lista(carregar3);
              libera_lista(carregar4);

             telaVitoria();
             sleep(2);
             return;
           }
           break;

         case 2:
           system("clear");
           ponto1 = (7 - totalNO_ArvBin(jogador1)) * 10;
           ponto2 = (7 - totalNO_ArvBin(jogador2)) * 10;
           ponto3 = (7 - totalNO_ArvBin(jogador3)) * 10;
           ponto4 = (7 - totalNO_ArvBin(jogador4)) * 10;

           printf("\033[1;33m"); // amarelo
           printf("\033[47m");   // Fundo branco
           printf("╔════════════════════════════════════════════════════════╗\n");
           printf("║ ⚫ ⚫      Jogador         ║ Pontuação           ⚫ ⚫ ║\n");
           printf("══════════════════════════════════════════════════════════\n");
           printf("\033[0m"); // Resetando as configurações para o padrão
           printf("          Jogador  1         ║    %d                     \n", ponto1);
           printf("          Jogador  2         ║    %d                     \n", ponto2);
           printf("          Jogador  3         ║    %d                     \n", ponto3);
           printf("          Jogador  4         ║    %d                     \n", ponto4);
           printf("╚════════════════════════════════════════════════════════╝\n");
           printf("\033[0m"); // Resetando as configurações para o padrão

            sleep(2);
           break;

         case 4:
           printf("\nDeseja salvar o jogo?\n1-Sim\n2-Não\n");
           scanf("%d", &salvar);

           switch(salvar){

             case 1:
               printf("\n1");
               salvarDadosJogo(jogador1, aux1);
               printf("\n2");
               salvarListaEmArquivo(aux1, "data/jogador1_4jogadores");

               salvarDadosJogo(jogador2, aux2);
               salvarListaEmArquivo(aux2, "data/jogador2_4jogadores");

               salvarDadosJogo(jogador3, aux3);
               salvarListaEmArquivo(aux3, "data/jogador3_4jogadores");

               salvarDadosJogo(jogador4, aux4);
               salvarListaEmArquivo(aux4, "data/jogador4_4jogadores");

               salvarListaEmArquivo(mesa, "data/mesa_4jogadores");

               printf("\n3");

               libera_ArvBin(jogador1);
               libera_ArvBin(jogador2);
               libera_ArvBin(jogador3);
               libera_ArvBin(jogador4);

               libera_lista(li);
               libera_lista(mesa);
               libera_lista(aux1);
               libera_lista(aux2);
               libera_lista(aux3);
               libera_lista(aux4);
               libera_lista(carregar1);
               libera_lista(carregar2);
               libera_lista(carregar3);
               libera_lista(carregar4);
               
               return;
               break;

             case 2:
                libera_ArvBin(jogador1);
                libera_ArvBin(jogador2);
                libera_ArvBin(jogador3);
                libera_ArvBin(jogador4);

                libera_lista(li);
                libera_lista(mesa);
                libera_lista(aux1);
                libera_lista(aux2);
                libera_lista(aux3);
                libera_lista(aux4);
                libera_lista(carregar1);
                libera_lista(carregar2);
                libera_lista(carregar3);
                libera_lista(carregar4);

               return;
               break;
           }
           break;

         default:
           printf("\nCarregando!\n");
           break;

       }
     }
       while(op != 1);
     
      do{
      op2 = menuMesa();

        switch(op2){

          case 1:
            system("clear");
            if (verifica_peca(jogador2, mesa)) {
              imprime_lista(mesa);
              printf("\n🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫-MESA-🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫\n");
              printf(" 🟤                                                                                  🟤\n");
              printf(" 🟤                                                                                  🟤\n");
              printf("\033[0m"); //padrão
              printf("\033[1;31m");// Vermelho
              printf("\n\nVez do jogador 2:\n\n");
              printf("\033[0m"); //padrão

              posOrdem_ArvBin(jogador2);

                printf("\n\nEscolha a peça para jogar (Exp: 1 2): ");
                scanf("%d %d", &al.lado1, &al.lado2);
                if (verif_exist_arv(jogador2, al)) {
                  if (insere_peca_mesa(mesa, al)) {
                    remove_ArvBin(jogador2, al);
                    printf("\n\nPeça inserida na mesa...\n\n");
                    imprime_lista(mesa);
                    printf("\nPeças na mesa\n");
                  } else
                  printf(
                      "\nocorreu um erro, não foi possível inserir os dados na peça");
                } else
                  printf(
                      "O jogador 2 não tem a peça que deseja inserir na mesa...\n");

            } else {
              cont2 = cont1 + 1;
              printf("\nJogador 2,você passou...\n");
              sleep(2);
            }

            if (estaVazia_ArvBin(jogador2)) {
              printf("\n\nJogador 2 ganhou...\n\n");
              sleep(2);
               libera_ArvBin(jogador1);
               libera_ArvBin(jogador2);
               libera_ArvBin(jogador3);
               libera_ArvBin(jogador4);

               libera_lista(li);
               libera_lista(mesa);
               libera_lista(aux1);
               libera_lista(aux2);
               libera_lista(aux3);
               libera_lista(aux4);
               libera_lista(carregar1);
               libera_lista(carregar2);
               libera_lista(carregar3);
               libera_lista(carregar4);

              telaVitoria();
              sleep(2);
              return;
            }
            break;

          case 2:
            system("clear");
            ponto1 = (7 - totalNO_ArvBin(jogador1)) * 10;
            ponto2 = (7 - totalNO_ArvBin(jogador2)) * 10;
            ponto3 = (7 - totalNO_ArvBin(jogador3)) * 10;
            ponto4 = (7 - totalNO_ArvBin(jogador4)) * 10;

            printf("\033[1;33m"); // amarelo
            printf("\033[47m");   // Fundo branco
            printf("╔════════════════════════════════════════════════════════╗\n");
            printf("║ ⚫ ⚫      Jogador         ║ Pontuação           ⚫ ⚫ ║\n");
            printf("══════════════════════════════════════════════════════════\n");
            printf("\033[0m"); // Resetando as configurações para o padrão
            printf("          Jogador  1         ║    %d                     \n", ponto1);
            printf("          Jogador  2         ║    %d                     \n", ponto2);
            printf("          Jogador  3         ║    %d                     \n", ponto3);
            printf("          Jogador  4         ║    %d                     \n", ponto4);
            printf("╚════════════════════════════════════════════════════════╝\n");
            printf("\033[0m"); // Resetando as configurações para o padrão

             sleep(2);
            break;

          case 4:
            printf("\nDeseja salvar o jogo?\n1-Sim\n2-Não\n");
            scanf("%d", &salvar);

            switch(salvar){

              case 1:
                printf("\n1");
                salvarDadosJogo(jogador1, aux1);
                printf("\n2");
                salvarListaEmArquivo(aux1, "data/jogador1_4jogadores");

                salvarDadosJogo(jogador2, aux2);
                salvarListaEmArquivo(aux2, "data/jogador2_4jogadores");

                salvarDadosJogo(jogador3, aux3);
                salvarListaEmArquivo(aux3, "data/jogador3_4jogadores");

                salvarDadosJogo(jogador4, aux4);
                salvarListaEmArquivo(aux4, "data/jogador4_4jogadores");

                salvarListaEmArquivo(mesa, "data/mesa_4jogadores");

                printf("\n3");

                libera_ArvBin(jogador1);
                libera_ArvBin(jogador2);
                libera_ArvBin(jogador3);
                libera_ArvBin(jogador4);

                libera_lista(li);
                libera_lista(mesa);
                libera_lista(aux1);
                libera_lista(aux2);
                libera_lista(aux3);
                libera_lista(aux4);
                libera_lista(carregar1);
                libera_lista(carregar2);
                libera_lista(carregar3);
                libera_lista(carregar4);

                return;
                break;

              case 2:
                 libera_ArvBin(jogador1);
                 libera_ArvBin(jogador2);
                 libera_ArvBin(jogador3);
                 libera_ArvBin(jogador4);

                 libera_lista(li);
                 libera_lista(mesa);
                 libera_lista(aux1);
                 libera_lista(aux2);
                 libera_lista(aux3);
                 libera_lista(aux4);
                 libera_lista(carregar1);
                 libera_lista(carregar2);
                 libera_lista(carregar3);
                 libera_lista(carregar4);
                return;
                break;
                return;
                break;
            }
            break;

          default:
            printf("\nCarregando!\n");
            break;

        }
      }
        while(op2 != 1);

     do{
       op3 = menuMesa();

         switch(op3){

           case 1:
             system("clear");
             if (verifica_peca(jogador3, mesa)) {
               imprime_lista(mesa);
               printf("\n🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫-MESA-🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫\n");
               printf(" 🟤                                                                                  🟤\n");
               printf(" 🟤                                                                                  🟤\n");
               printf("\033[0m"); //padrão
               printf("\033[1;32m");// Verde
               printf("\n\nVez do jogador 3:\n\n");
               printf("\033[0m"); //padrão

               posOrdem_ArvBin(jogador3);

                 printf("\n\nEscolha a peça para jogar (Exp: 1 2): ");
                 scanf("%d %d", &al.lado1, &al.lado2);
                 if (verif_exist_arv(jogador3, al)) {
                   if (insere_peca_mesa(mesa, al)) {
                     remove_ArvBin(jogador3, al);
                     printf("\n\nPeça inserida na mesa...\n\n");
                     imprime_lista(mesa);
                     printf("\nPeças na mesa\n");
                   } else
                   printf(
                       "\nocorreu um erro, não foi possível inserir os dados na peça");
                 } else
                   printf(
                       "O jogador 3 não tem a peça que deseja inserir na mesa...\n");

             } else {
               cont3 = cont2 + 1;
               printf("\nJogador 3,você passou...\n");
               sleep(2);
             }

             if (estaVazia_ArvBin(jogador3)) {
               printf("\n\nJogador 3 ganhou...\n\n");
               sleep(2);
                libera_ArvBin(jogador1);
                libera_ArvBin(jogador2);
                libera_ArvBin(jogador3);
                libera_ArvBin(jogador4);

                libera_lista(li);
                libera_lista(mesa);
                libera_lista(aux1);
                libera_lista(aux2);
                libera_lista(aux3);
                libera_lista(aux4);
                libera_lista(carregar1);
                libera_lista(carregar2);
                libera_lista(carregar3);
                libera_lista(carregar4);

               telaVitoria();
               sleep(2);
               return;
             }
             break;

           case 2:
             system("clear");
             ponto1 = (7 - totalNO_ArvBin(jogador1)) * 10;
             ponto2 = (7 - totalNO_ArvBin(jogador2)) * 10;
             ponto3 = (7 - totalNO_ArvBin(jogador3)) * 10;
             ponto4 = (7 - totalNO_ArvBin(jogador4)) * 10;

             printf("\033[1;33m"); // amarelo
             printf("\033[47m");   // Fundo branco
             printf("╔════════════════════════════════════════════════════════╗\n");
             printf("║ ⚫ ⚫      Jogador         ║ Pontuação           ⚫ ⚫ ║\n");
             printf("══════════════════════════════════════════════════════════\n");
             printf("\033[0m"); // Resetando as configurações para o padrão
             printf("          Jogador  1         ║    %d                     \n", ponto1);
             printf("          Jogador  2         ║    %d                     \n", ponto2);
             printf("          Jogador  3         ║    %d                     \n", ponto3);
             printf("          Jogador  4         ║    %d                     \n", ponto4);
             printf("╚════════════════════════════════════════════════════════╝\n");
             printf("\033[0m"); // Resetando as configurações para o padrão

              sleep(2);
             break;

           case 4:
             printf("\nDeseja salvar o jogo?\n1-Sim\n2-Não\n");
             scanf("%d", &salvar);

             switch(salvar){

               case 1:
                 printf("\n1");
                 salvarDadosJogo(jogador1, aux1);
                 printf("\n2");
                 salvarListaEmArquivo(aux1, "data/jogador1_4jogadores");

                 salvarDadosJogo(jogador2, aux2);
                 salvarListaEmArquivo(aux2, "data/jogador2_4jogadores");

                 salvarDadosJogo(jogador3, aux3);
                 salvarListaEmArquivo(aux3, "data/jogador3_4jogadores");

                 salvarDadosJogo(jogador4, aux4);
                 salvarListaEmArquivo(aux4, "data/jogador4_4jogadores");

                 salvarListaEmArquivo(mesa, "data/mesa_4jogadores");

                 printf("\n3");

                 libera_ArvBin(jogador1);
                 libera_ArvBin(jogador2);
                 libera_ArvBin(jogador3);
                 libera_ArvBin(jogador4);

                 libera_lista(li);
                 libera_lista(mesa);
                 libera_lista(aux1);
                 libera_lista(aux2);
                 libera_lista(aux3);
                 libera_lista(aux4);
                 libera_lista(carregar1);
                 libera_lista(carregar2);
                 libera_lista(carregar3);
                 libera_lista(carregar4);

                 return;
                 break;

               case 2:
                  libera_ArvBin(jogador1);
                  libera_ArvBin(jogador2);
                  libera_ArvBin(jogador3);
                  libera_ArvBin(jogador4);

                  libera_lista(li);
                  libera_lista(mesa);
                  libera_lista(aux1);
                  libera_lista(aux2);
                  libera_lista(aux3);
                  libera_lista(aux4);
                  libera_lista(carregar1);
                  libera_lista(carregar2);
                  libera_lista(carregar3);
                  libera_lista(carregar4);
                 return;
                 break;
                 return;
                 break;
             }
             break;

           default:
             printf("\nCarregando!\n");
             break;

         }
       }
         while(op3 != 1);


     do{
        op4 = menuMesa();

          switch(op4){

            case 1:
              system("clear");
              if (verifica_peca(jogador4, mesa)) {
                imprime_lista(mesa);
                printf("\n🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫-MESA-🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫🟫\n");
                printf(" 🟤                                                                                  🟤\n");
                printf(" 🟤                                                                                  🟤\n");
                printf("\033[0m"); //padrão
                printf("\033[1;33m");// Azul
                printf("\n\nVez do jogador 4:\n\n");
                printf("\033[0m"); //padrão

                posOrdem_ArvBin(jogador4);

                  printf("\n\nEscolha a peça para jogar (Exp: 1 2): ");
                  scanf("%d %d", &al.lado1, &al.lado2);
                  if (verif_exist_arv(jogador4, al)) {
                    if (insere_peca_mesa(mesa, al)) {
                      remove_ArvBin(jogador4, al);
                      printf("\n\nPeça inserida na mesa...\n\n");
                      imprime_lista(mesa);
                      printf("\nPeças na mesa\n");
                    } else
                    printf(
                        "\nocorreu um erro, não foi possível inserir os dados na peça");
                  } else
                    printf(
                        "O jogador 4 não tem a peça que deseja inserir na mesa...\n");

              } else {
                cont4 = cont3 + 1;
                printf("\nJogador 4,você passou...\n");
                sleep(2);
              }

              if (estaVazia_ArvBin(jogador4)) {
                printf("\n\nJogador 4 ganhou...\n\n");
                sleep(2);
                 libera_ArvBin(jogador1);
                 libera_ArvBin(jogador2);
                 libera_ArvBin(jogador3);
                 libera_ArvBin(jogador4);

                 libera_lista(li);
                 libera_lista(mesa);
                 libera_lista(aux1);
                 libera_lista(aux2);
                 libera_lista(aux3);
                 libera_lista(aux4);
                 libera_lista(carregar1);
                 libera_lista(carregar2);
                 libera_lista(carregar3);
                 libera_lista(carregar4);

                telaVitoria();
                sleep(2);
                return;
              }
              break;

            case 2:
              system("clear");
              ponto1 = (7 - totalNO_ArvBin(jogador1)) * 10;
              ponto2 = (7 - totalNO_ArvBin(jogador2)) * 10;
              ponto3 = (7 - totalNO_ArvBin(jogador3)) * 10;
              ponto4 = (7 - totalNO_ArvBin(jogador4)) * 10;

              printf("\033[1;33m"); // amarelo
              printf("\033[47m");   // Fundo branco
              printf("╔════════════════════════════════════════════════════════╗\n");
              printf("║ ⚫ ⚫      Jogador         ║ Pontuação           ⚫ ⚫ ║\n");
              printf("══════════════════════════════════════════════════════════\n");
              printf("\033[0m"); // Resetando as configurações para o padrão
              printf("          Jogador  1         ║    %d                     \n", ponto1);
              printf("          Jogador  2         ║    %d                     \n", ponto2);
              printf("          Jogador  3         ║    %d                     \n", ponto3);
              printf("          Jogador  4         ║    %d                     \n", ponto4);
              printf("╚════════════════════════════════════════════════════════╝\n");
              printf("\033[0m"); // Resetando as configurações para o padrão

               sleep(2);
              break;

            case 4:
              printf("\nDeseja salvar o jogo?\n1-Sim\n2-Não\n");
              scanf("%d", &salvar);

              switch(salvar){

                case 1:
                  printf("\n1");
                  salvarDadosJogo(jogador1, aux1);
                  printf("\n2");
                  salvarListaEmArquivo(aux1, "data/jogador1_4jogadores");

                  salvarDadosJogo(jogador2, aux2);
                  salvarListaEmArquivo(aux2, "data/jogador2_4jogadores");

                  salvarDadosJogo(jogador3, aux3);
                  salvarListaEmArquivo(aux3, "data/jogador3_4jogadores");

                  salvarDadosJogo(jogador4, aux4);
                  salvarListaEmArquivo(aux4, "data/jogador4_4jogadores");

                  salvarListaEmArquivo(mesa, "data/mesa_4jogadores");

                  printf("\n3");

                  libera_ArvBin(jogador1);
                  libera_ArvBin(jogador2);
                  libera_ArvBin(jogador3);
                  libera_ArvBin(jogador4);

                  libera_lista(li);
                  libera_lista(mesa);
                  libera_lista(aux1);
                  libera_lista(aux2);
                  libera_lista(aux3);
                  libera_lista(aux4);
                  libera_lista(carregar1);
                  libera_lista(carregar2);
                  libera_lista(carregar3);
                  libera_lista(carregar4);

                  return;
                  break;

                case 2:
                   libera_ArvBin(jogador1);
                   libera_ArvBin(jogador2);
                   libera_ArvBin(jogador3);
                   libera_ArvBin(jogador4);

                   libera_lista(li);
                   libera_lista(mesa);
                   libera_lista(aux1);
                   libera_lista(aux2);
                   libera_lista(aux3);
                   libera_lista(aux4);
                   libera_lista(carregar1);
                   libera_lista(carregar2);
                   libera_lista(carregar3);
                   libera_lista(carregar4);
                  return;
                  break;
                  return;
                  break;
              }
              break;

            default:
              printf("\nCarregando!\n");
              break;

          }
        }
          while(op4 != 1);

   }
     while(cont4 != 4);

   soma1 = somarValores(jogador1);
   soma2 = somarValores(jogador2);
   soma3 = somarValores(jogador3);
   soma4 = somarValores(jogador4);

   printf("Peças do jogador 1: %d\n", soma1);
   printf("Peças do jogador 2: %d\n", soma2);
   printf("Peças do jogador 3: %d\n", soma3);
   printf("Peças do jogador 4: %d\n", soma4);

   if (soma1 < soma2 && soma1 < soma3 && soma1 < soma4) {
     printf("\n\nParabéns jogador 1, você ganhou!\n\n");
     sleep(2);
     telaVitoria();
   } else if (soma2 < soma1 && soma2 < soma3 && soma2 < soma4) {
     printf("\n\nParabéns jogador 2, você ganhou!\n\n");
     sleep(2);
     telaVitoria();
   } else if (soma3 < soma1 && soma3 < soma2 && soma3 < soma4) {
     printf("\n\nParabéns jogador 3, você ganhou!\n\n");
     sleep(2);
     telaVitoria();
   } else if (soma4 < soma1 && soma4 < soma2 && soma4 < soma3) {
     printf("\n\nParabéns jogador 4, você ganhou!\n\n");
     sleep(2);
     telaVitoria();
   } else {
     printf("Empate...\n");
     sleep(2);
     telaEmpate();
     sleep(2);
   }

   libera_ArvBin(jogador1);
   libera_ArvBin(jogador2);
   libera_ArvBin(jogador3);
   libera_ArvBin(jogador4);
   libera_lista(li);
   libera_lista(mesa);
   libera_lista(aux1);
   libera_lista(aux2);
   libera_lista(aux3);
   libera_lista(aux4);
   libera_lista(carregar1);
   libera_lista(carregar2);
   libera_lista(carregar3);
   libera_lista(carregar4);

   sleep(3);

 }