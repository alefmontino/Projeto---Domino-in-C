#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/ListaDinEncad.h" //inclui os Prot�tipos

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, struct pecadomino *al) {
    if(li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int mat, struct pecadomino *al){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL /*&& no->dados.matricula != mat*/){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int insere_lista_final(Lista* li, struct pecadomino al){
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere in�cio
        *li = no;
    }else{
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct pecadomino al){
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    *li = no;
    return 1;
}

int insere_lista_ordenada(Lista* li, struct pecadomino al){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        Elem *ant, *atual = *li;
        while(atual != NULL /*&& atual->dados.matricula < al.matricula*/){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere in�cio
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_lista(Lista* li, int mat){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem *ant, *no = *li;
    while(no != NULL /*&& no->dados.matricula != mat*/){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//n�o encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *ant, *no = *li;
    while(no->prox != NULL){
        ant = no;
        no = no->prox;
    }

    if(no == (*li))//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}


void imprime_lista(Lista *li) {
  if (li == NULL)
    return;
  Elem *no = *li;
  printf("\n\n");
  while (no != NULL) {
    printf("\033[1;30m\033[47m %d | %d \033[47m\033[0m ", no->dados.lado1, no->dados.lado2);
    no = no->prox;
  }
}

void criar_pecas(Lista *al) {
  // Criação das peças e embaralhamento
  int numeroDePecas = 28; // Dominó padrão

  if(al == NULL){
    al = cria_lista();
  }

  struct pecadomino a/*[numeroDePecas]*/;

  //a[i * 7 + j]

  //Criação da peça, inserindo os dados em uma lista
  for(int i = 0; i < 7; i++){
    for(int j = i; j < 7; j++){
      a.lado1 = i;
      a.lado2 = j;
      insere_lista_final(al, a);
    }
  }
  return;
}


void embaralhar_pecas(Lista *al) {

  int numeroDePecas = 28;
  // Embaralhamento das peças

  srand((unsigned int)time(NULL));

  Elem* inicio = *al; // Mantenha o ponteiro para o início da lista
  Elem* no_i = inicio;

  for (int i = numeroDePecas - 1; i > 0; i--) {
      int j = rand() % (i + 1);

      // Percorre a lista até o elemento i
      for (int k = 0; k < i; k++) {
          no_i = no_i->prox;
      }

      Elem* no_j = inicio; // Reinicia no_j para o início da lista

      // Percorre a lista até o elemento j
      for (int k = 0; k < j; k++) {
          no_j = no_j->prox;
      }

      // Troca os dados dos elementos i e j
      struct pecadomino temp = no_i->dados;
      no_i->dados = no_j->dados;
      no_j->dados = temp;

      // Reinicia no_i para o início da lista para a próxima iteração
      no_i = inicio;
  }

  return;
}


// Função para inserir uma peça de dominó em uma lista representando a mesa do jogo
int insere_peca_mesa(Lista* al, struct pecadomino novaPeca) {

  // Variável temporária para trocar os lados, se necessário
  struct pecadomino aux;

  // Verifica se a lista é NULL
  if(al == NULL){
    return 0; // Retorna 0 para indicar falha
  }

  // Verifica se a lista está vazia
  if(*al == NULL){
    insere_lista_inicio(al, novaPeca); // Se estiver vazia, insere a peça no início da lista
    return 1; // Retorna 1 para indicar sucesso
  }

  Elem *no = *al; // Ponteiro para percorrer a lista

  // Verifica se a nova peça pode ser conectada ao início da lista
  if(novaPeca.lado1 == no->dados.lado1){
    aux.lado1 =  novaPeca.lado1;
    novaPeca.lado1 = novaPeca.lado2;
    novaPeca.lado2 = aux.lado1;
    insere_lista_inicio(al, novaPeca); // Insere a peça no início com os lados trocados, se necessário
    return 1; // Retorna 1 para indicar sucesso
  }
  // Verifica se a nova peça pode ser conectada ao início da lista sem trocar os lados
  else if(novaPeca.lado2 == no->dados.lado1){
    insere_lista_inicio(al, novaPeca); // Insere a peça no início
    return 1; // Retorna 1 para indicar sucesso
  }

  // Percorre a lista para encontrar o final
  while(no->prox != NULL ){
    no = no->prox;
  }

  // Verifica se a nova peça pode ser conectada ao final da lista
  if(novaPeca.lado1 == no->dados.lado2){
    insere_lista_final(al, novaPeca); // Insere a peça no final da lista
    return 1; // Retorna 1 para indicar sucesso
  }
  // Verifica se a nova peça pode ser conectada ao final da lista com os lados trocados
  else if(novaPeca.lado2 == no->dados.lado2){
    aux.lado1 =  novaPeca.lado1;
    novaPeca.lado1 = novaPeca.lado2;
    novaPeca.lado2 = aux.lado1;
    insere_lista_final(al, novaPeca); // Insere a peça no final da lista com os lados trocados
    return 1; // Retorna 1 para indicar sucesso
  }

  printf("\n\nNão foi possivel incluir a peça na mesa...\n");
  return 0; // Retorna 0 se a peça não puder ser inserida
}


