#include "fila.h"
#ifndef arvore
#define arvore

// declaração da estrutura


void inicializaArvore(TNo *R);
TNo* inicializaNo(TNo *R);
void preInsercao(TNo *R, TNo *no, Cidade *cid);
TNo* insereArvore(TNo *R, TNo *no);
TNo* insereArvoreAvl(TNo *R, TNo *no);
void insereRecursivo(TNo *rAtual, TNo *novo);
TNo* geraNo(Cidade *cid);
TNo* buscaNo(TNo *R, int cod, int *cont);
int obterAlturaArvore(TNo *R);
int verificaBalanceamento(TNo *R);
int obterFatorBalanceamento(TNo *R);
void rotacaoAEsquerda(TNo *R);
void rotacaoADireita(TNo *R);
void rotacaoDireitaEsquerda(TNo *R);
void rotacaoEsquerdaDireita(TNo *R);
void caminhaEmNivel(TNo **R, char *nomeArq);



#endif // arvore

