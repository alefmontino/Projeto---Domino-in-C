#include "ListaDinEncad.h"

struct NO{
    int info;
    struct pecadomino* peca;
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO* ArvBin;

/*
struct Jogador {
  ArvBin* raizArvore;
};
*/


ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int remove_ArvBin(ArvBin *raiz, struct pecadomino al);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, int valor);
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);
ArvBin adicionarPecaNaArvore(ArvBin raiz, struct pecadomino novaPeca);
int verif_exist_arv(ArvBin *raiz, struct pecadomino al);
void menu_2_jogadores();
void menu_3_jogadores();
void menu_4_jogadores();
int somarValores(ArvBin *raiz);
int  verifica_peca(ArvBin *raiz, Lista* al);
void menu_vs_cpu();