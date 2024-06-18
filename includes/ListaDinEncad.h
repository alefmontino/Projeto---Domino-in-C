//Arquivo ListaDinEncad.h

struct pecadomino{
  int lado1, lado2;
};

//Defini�o do tipo lista
struct elemento{
    struct pecadomino dados;
    struct elemento *prox;
};

typedef struct elemento* Lista;
typedef struct elemento Elem;

Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, struct pecadomino al);
int insere_lista_inicio(Lista* li, struct pecadomino al);
int insere_lista_ordenada(Lista* li, struct pecadomino al);
int remove_lista(Lista* li, int mat);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
int lista_cheia(Lista* li);
void imprime_lista(Lista* li);
int consulta_lista_mat(Lista* li, int mat, struct pecadomino *al);
int consulta_lista_pos(Lista* li, int pos, struct pecadomino *al);
void criar_pecas(Lista *al);
void embaralhar_pecas(Lista *al);
int insere_peca_mesa(Lista* al, struct pecadomino novaPeca);