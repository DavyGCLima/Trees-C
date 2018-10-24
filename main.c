#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila.h"
#include "arvore.h"
//#ifndef main
//inicia uma strng
void zerarString(char *s){
    int i;
    for(i = 0; i < sizeof(s); i++){
        s[i] = '\0';
    }
}

//lê o arquivo e cria os registros
void lerArquivo(TNo **R, TNo **Ravl){
    clock_t inic = clock();
    FILE *arquivo = fopen("entrada.txt", "r");
    if(!arquivo){
        printf("\n\t Erro ao ler o arquivo");
    }else{
    	while(!feof(arquivo)){
            char linha[40];
            zerarString(linha);
	        Cidade *cidade = (Cidade*)malloc(sizeof(Cidade));
	        char* conteudo = fgets(linha, sizeof(linha), arquivo);
	        if(conteudo != NULL){
                char *resStr = (char*)strtok(conteudo, ";");
                cidade->numero = atoi(resStr);
                char *nom = (char *)malloc(10 * sizeof(char));
                char *nomAux;
                nomAux = strtok(NULL, ";");
                strcpy(nom, nomAux);
                cidade->nome = nom;
                cidade->populacao = atoi(strtok(NULL, ";"));
                //insere nas arvores
                TNo *no = geraNo(cidade);
                TNo *noAvl = geraNo(cidade);
                *R = insereArvore(*R, no);
                *Ravl = insereArvoreAvl(*Ravl, noAvl);
            }//FIM IF
        }//FIM WHILE
    }//FIM ELSE
    clock_t fim = clock();
        printf("\n\t Arquivo lido!");
        double res = (double)(fim - inic)/CLOCKS_PER_SEC;
        printf("\n\t tempo: %f \n",res);
    fclose(arquivo);
}


void lerOperacoes(TNo **R, TNo **Ravl){
    FILE *arquivo = fopen("buscas.txt", "r");
    if(!arquivo){
        printf("\n\t Erro ao ler o arquivo");
    }else{
        FILE *arqTempo = fopen("temposdebusca.txt", "w");
        if(!arqTempo){
            printf("\n\t Erro ao criar arquivo de tempo de busca ");
        }else{
            while(!feof(arquivo)){
                //captura a linha
                char* linhaTempo = (char*)malloc(40*sizeof(char));
                zerarString(linhaTempo);

                //processa a linha, dividindo-a em tokens
                char linha[40];
                zerarString(linha);
                char* conteudo = fgets(linha, sizeof(linha), arquivo);
                char *operacao = strtok(conteudo, ";");
                printf("\n\t ===== OPERACAO: %s ", operacao);

                //verifica o fim a operação pois há uma linha no fim do arquivo
                if(operacao == NULL || strcmp(operacao, "\n") == 0) {
                    printf("\n\t FIM DA EXECUCAO ");
                }else{
                    //caso de inserção
                    if(strcmp(operacao, "I") == 0){
                        printf("\n\t ===== I ");
                        Cidade *cid = (Cidade*)malloc(sizeof(Cidade));
                        cid->numero = atoi(strtok(NULL, ";"));
                        char *nom = (char *)malloc(10 * sizeof(char));
                        char *nomAux;
                        nomAux = strtok(NULL, ";");
                        strcpy(nom, nomAux);
                        cid->nome = nom;
                        cid->populacao = atoi(strtok(NULL, ";"));
                        TNo *no = geraNo(cid);
                        TNo *noAvl = geraNo(cid);
                        *R = insereArvore(*R, no);
                        *Ravl = insereArvoreAvl(*Ravl, noAvl);

                    // caso de busca
                    }else if(strcmp(operacao, "B") == 0){
                        printf("\n\t ===== B ");
                        int cod = atoi(strtok(NULL, ";"));

                        //=============================== busca na arvore binaria
                        int encontrouArvBin = 0;
                        int contArvBin = 0;
                        clock_t inicTempArvBin = clock();
                        TNo *noBusca = buscaNo(*R, cod, &contArvBin);
                        Cidade *busca = NULL;
                        if(noBusca != NULL){
                            busca = noBusca->conteudo;
                        }
                        clock_t fimTempArvBin = clock();
                        double resArvBin = (double)(fimTempArvBin - inicTempArvBin)/CLOCKS_PER_SEC;
                        if(busca != NULL){
                            printf("\n\t\t Busca Arvore Binaria tempo: %f, Cid: %d, %s",resArvBin, busca->numero, busca->nome);
                            encontrouArvBin = 1;
                        }
                        else{
                            printf("\n\t\t Elemnto não encontrado na Arvore Binaria %f, cod: %d", resArvBin, cod);
                        }

                        // ============================== busca na arvore avl
                        int encontrouArvAvl = 0;
                        int contArvAvl = 0;
                        clock_t iniTempArvBin = clock();
                        TNo *noBuscaAvl = buscaNo(*Ravl, cod, &contArvAvl);
                        Cidade *busca2 = NULL;
                        if(noBuscaAvl != NULL)
                            busca2 = noBuscaAvl->conteudo;
                        clock_t fimTtmpArvAvl = clock();
                        double resArvAvl = (double)(fimTtmpArvAvl - iniTempArvBin)/CLOCKS_PER_SEC;
                        if(busca2 != NULL){
                            printf("\n\t\t Busca hash fechada tempo: %f, cid: %d, %s",resArvAvl, busca2->numero, busca2->nome);
                            encontrouArvAvl = 1;
                        }
                        else
                            printf("\n\t\t Elemnto não encontrado em ArvoreAvl %f, cod: %d", resArvAvl, cod);

                        //escreve no arquivo de saida =============================================================================
                        int verificador =  fprintf(arqTempo, "%d;%d;%.2f;%d;%d;%.2f;%d;\n", cod,
                                                  encontrouArvBin, resArvBin, contArvBin,
                                                  encontrouArvAvl, resArvAvl, contArvAvl);
                        if (verificador == EOF)
                            printf("\n\n\t Nao sucedido em escrever linha");
                    }else{
                        printf("\n\t ============ Operacao Ivalida %s =========== ", operacao);
                        system("PAUSE");
                        system("EXIT");
                    }
                }// FIM ELSE OPERAÇÃO
            }//FIM WHILE
        }// FIM ELSE ARQTEMPO
        fclose(arqTempo);
    }//FIM ELSE
    fclose(arquivo);
}//FIM METODO

void main()
{
    TNo *arvoreBin = NULL;
    TNo *arvoreAvl = NULL;
    printf("\n\t Avores criadas");

    lerArquivo(&arvoreBin, &arvoreAvl);
    lerOperacoes(&arvoreBin, &arvoreAvl);

    char *nomeBin = "saidaArvoreBianria.txt";
    char *nomeAvl = "saidaArvoreAvl.txt";
    caminhaEmNivel(&arvoreAvl, nomeBin);
    caminhaEmNivel(&arvoreBin, nomeAvl);

	//system("PAUSE");
    // return 1;
}
//#endif
