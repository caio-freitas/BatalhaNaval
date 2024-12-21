/***************************************************************/
/**                                                           **/
/**   Caio Victor Gouveia Freitas       Número USP 10773328   **/
/**   Exercício-Programa 03                                   **/
/**   Professor: Cristina Fernandes                           **/
/**   Turma: 01                                               **/
/**                                                           **/
/***************************************************************/


#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAXLINHAS 20
#define MAXCOLUNAS 20
#define MAXNOME 64
#define BARCO         'B'
#define SUBMARINO     'S'
#define DESTROYER     'D'
#define CRUZADOR      'C'
#define PORTA_AVIAO   'P'
#define HIDRO_AVIAO   'H'
#define AGUA          'a'
#define EXPLOSAO      '*'
#define RASTRO        '.'
#define ESQUERDA      'e'
#define BAIXO         'b'
#define DIREITA       'd'
#define CIMA          'c'


/** Função retirada do html da Etapa 3 **/
int no_aleatorio(int n)  //Devolve um número aleatório entre 1 e n
{
  return  1 + (rand()/(RAND_MAX+1.0))*n;
}

/** Função retirada do html da Etapa 3 **/
void sorteie_posicao (int no_linhas, int no_colunas, int *linha, int *coluna) // Usa a no_aleatorio para determinar uma posição
{
  *linha  = no_aleatorio(no_linhas);
  *coluna = no_aleatorio(no_colunas);
}

int acertou_embarcacao(char ch) {
    if(ch==SUBMARINO||ch==DESTROYER||ch==CRUZADOR||ch==PORTA_AVIAO||ch==HIDRO_AVIAO) {
        return TRUE;
    }
    else
        return FALSE;
}


void afunda_embarcacao(int linha, int coluna, int linhas, int colunas, char mapa[MAXLINHAS][MAXCOLUNAS]) {
    int i, j;
    for (i=linha-2; i<=linha+2; i++) {
        for (j=coluna-2; j<=coluna+2; j++) {
            if(i<=linhas&&j<=colunas&&i>0&&j>0) {
                if(mapa[i][j]==mapa[linha][coluna])
                    mapa[i][j]+='a'-'A';
            }
        }
    }
    mapa[linha][coluna]=EXPLOSAO;
}

int tiros (int linhas_mapa, int colunas_mapa, char map[MAXLINHAS][MAXCOLUNAS]) {
    int bombas, linha, coluna, linhas, colunas, barcointeiro;
    linhas=linhas_mapa;
    colunas=colunas_mapa;
    barcointeiro=1;
    for (bombas=0; bombas<3; bombas++) {
        sorteie_posicao(linhas, colunas, &linha, &coluna);
        if(acertou_embarcacao(map[linha][coluna])==TRUE) {
            printf("MSG do QG: embarcacao inimiga destruida em (%2d,%2d).\n", linha, coluna);
            map[linha][coluna]=EXPLOSAO;
            afunda_embarcacao(linha, coluna, linhas, colunas, map);
            barcointeiro&=TRUE;     /** Realiza operação booleana 'and' para informar, ao final da função, se o barco foi atingido ou não **/
        }
        else if(map[linha][coluna]==BARCO){
            printf("MSG do QG: voce foi atingido por fogo amigo!!\n");
            map[linha][coluna]=EXPLOSAO;
            barcointeiro&=FALSE;
        }
        else {
            map[linha][coluna]=AGUA;
            printf("MSG do QG: posicao (%d, %d), CHUA ... AGUA\n", linha, coluna);
            barcointeiro&=TRUE;
        }
    }
    return barcointeiro;
}

void leia_ate_barra_n (FILE *arq){
    char ch;
    fscanf(arq, "%c", &ch);
    while(ch!='\n') {
            fscanf(arq, "%c", &ch);
        }
}

/** Função retirada do html da Etapa 3 **/
void inicializa_gerador(int semente)
{
  srand(semente);
}


 int coluna_inicial_barco(char mapa[MAXLINHAS][MAXCOLUNAS]) {
    int cib=1;
    while(mapa[1][cib]!=BARCO){
        cib++;
    }
    return cib;
}

/** Função retirada do arquivo html da Etapa 3 **/
void leia_mapa (int *no_linhas, int *no_colunas, char mapa[MAXLINHAS][MAXCOLUNAS], int *c_barco)    {
  FILE *arq;   /* arquivo que contem o mapa */
  char nome_arquivo[MAXNOME]; /* nome do arquivo que contem o mapa */
  int no_l;    /* numero de linha do mapa */
  int no_c;    /* numero de colunas do mapa */
  int c_bar;   /* coluna inicial do barco */
  int i;       /* indice de linhas */
  int j;       /* indice de colunas */
  int codigo;  /* semente do gerador de numeros aleatorios */
  printf("MSG do QG: preparando para leitura do mapa.\n");

  /* 1. leia o nome do arquivo */
  printf("MSG do QG: forneca nome do arquivo que contem o mapa: ");
  scanf("%s", nome_arquivo);

  /* 2. abra o arquivo para leitura */
  arq = fopen(nome_arquivo,"r");
  if (arq == NULL)
    {
      printf("MSG do QG: erro na abertura de %s.\n", nome_arquivo);
      printf("MSG do QG: MISSAO ABORTADA!\n\n");
      system("pause"); /* para WINDOWS */
      exit(-1);
    }
  printf("MSG do QG: arquivo %s foi encontrado.\n", nome_arquivo);

  /* 3. leia o numero de linha n e o numero de coluna m do mapa */
  printf("MSG do QG: mapa esta sendo lido do arquivo %s.\n", nome_arquivo);
  fscanf(arq, "%d %d %d", &no_l, &no_c, &codigo);
  leia_ate_barra_n(arq);
  printf("MSG do QG: mapa tem %d linhas e %d colunas.\n", no_l, no_c);
  printf("MSG do QG: codigo de ataque: %d\n", codigo);
   /* 4. inicializa o gerador de numeros aleatorios */
  inicializa_gerador(codigo);
  /* 5. leia o mapa */
  for (i = 1; i <= no_l; i++)
    {
      for (j = 1; j <= no_c; j++)
        {
          fscanf(arq, "%c", &mapa[i][j]);
        }
      leia_ate_barra_n(arq); /* le os caracteres ate' o fim-de-linha*/
    }
  /* 6. determine a posicao inicial do barco */
  c_bar = coluna_inicial_barco(mapa);
   /* voce precisa escrever a funcao acima */
  printf("MSG do QG: posicao inicial do barco e' (1,%d).\n", c_bar);
  /* 7. feche o arquivo */
  fclose(arq);
  printf("MSG do QG: mapa lido com sucesso.\n");
 /* 8. devolva o numero de linhas, colunas e coluna do barco */
  *no_linhas  = no_l;
  *no_colunas = no_c;
  *c_barco    = c_bar;
}

/** Função retirada do html da Etapa 3 **/
void escreva_mapa_arquivo (int no_linhas, int no_colunas, char mapa[MAXLINHAS][MAXCOLUNAS]){
  FILE *arq;
  int i; /* indice de linhas */
  int j; /* indice de colunas */

  /* abra arquivo para escrita */
  arq = fopen("secreto.dat","w");
  if (arq == NULL)
    {
      printf("MSG do QG: erro na criacao do arquivo secreto.dat.\n");
      printf("MSG do QG: MISSAO ABORTADA!\n\n");
      exit(-1);
    }

  /* escreva o cabecalho no arquivo */
  fprintf(arq, "    MAPA SECRETO DA BATALHA\n\n");
  fprintf(arq, "    no. linhas = %d     no. colunas = %d\n\n",
          no_linhas,  no_colunas);

  /* imprime o mapa no arquivo secreto.dat */
  for(i=1; i<=no_linhas; i++) {
    for(j=1; j<=no_colunas; j++) {
        fprintf(arq, "%3c" , mapa[i][j]);
    }
    fprintf(arq, "\n");
  }
  /* feche o arquivo */
  fprintf(arq, "\n\nFIM DO ARQUIVO.");
  fclose(arq);
}


void escreva_mapa_tela (int no_linhas, int no_colunas, char mapa[MAXLINHAS][MAXCOLUNAS]) {
    int i, j;
    for(i=1; i<=no_colunas; i++)
        printf("%4d", i);
    printf("\n");
    for(i=1; i<=no_linhas; i++) {
        printf("%2d ", i);
        for(j=1; j<=no_colunas; j++) {
          if(mapa[i][j]==BARCO||mapa[i][j]==RASTRO||mapa[i][j]==EXPLOSAO||(mapa[i][j]>='a'&&mapa[i][j]<='z'))
            printf("|%2c ", mapa[i][j]);
          else
            printf("|   ");
        }
        printf("|\n   ");
        for(j=0; j<no_colunas; j++)
            printf("+---");         //linha de separação
        printf("+\n");               //fim de linha de separação
    }
}


int movimenta_barco(int *linha_barco, int *coluna_barco, int linhas, int colunas, char mapa[MAXLINHAS][MAXCOLUNAS]) {
    char comando;
    int lb, cb;
    lb=*linha_barco;
    cb=*coluna_barco;
    scanf(" %c", &comando);
    printf("MSG do QG: direcao escolhida: %c\n", comando);
    if(comando==BAIXO) {
        if((lb+1)<=linhas){
            if(acertou_embarcacao(mapa[lb+1][cb])==TRUE){
                printf("MSG do QG: ha uma embarcacao em (%2d,%2d)\n", lb+1, cb);
                return 2;
            }
            else {
                mapa[lb][cb]=RASTRO;
                lb++;
                mapa[lb][cb]=BARCO;
                *linha_barco=lb;
                return 1;
            }
        }
        else
            return 1;
    }
    else if(comando==CIMA){
        if(lb-1==0){
            return 1;
        }
        else {
            if(acertou_embarcacao(mapa[lb-1][cb])==TRUE) {
                    printf("MSG do QG: ha uma embarcacao em (%2d,%2d)\n", lb-1, cb);
                return 2;
            }
            else {
                mapa[lb][cb]=RASTRO;
                lb--;
                mapa[lb][cb]=BARCO;
                *linha_barco=lb;
                return 1;
            }
        }
    }
    else if(comando==DIREITA) {
        if(cb>=colunas){
            return 1;
        }
        else {
            if(acertou_embarcacao(mapa[lb][cb+1])==TRUE) {
                printf("MSG do QG: ha uma embarcacao em (%2d,%2d)\n", lb, cb+1);
                return 2;
            }
            else {
                mapa[lb][cb]=RASTRO;
                cb++;
                mapa[lb][cb]=BARCO;
                *coluna_barco=cb;
                return 1;
            }
        }
    }
    else if (comando==ESQUERDA){
        if(cb-1==0){
            return 1;
        }
        else {
            if(acertou_embarcacao(mapa[lb][cb-1])==TRUE) {
                printf("MSG do QG: ha uma embarcacao em (%2d,%2d)\n", lb, cb-1);
                return 2;
            }
            else {
                mapa[lb][cb]=RASTRO;
                cb--;
                mapa[lb][cb]=BARCO;
                *coluna_barco=cb;
                return 1;
            }
        }
    }
    else if (comando=='f')
        printf("Arregou!!\n");
        return 0;
    return 1;
}


int main() {
    int linhabarco, colunabarco, linhas, colunas;
    int jogocontinua=TRUE;           //Variável booleana que determina o fim do jogo, vale 1
    char MAPA[MAXCOLUNAS][MAXLINHAS];
    linhabarco=1;
    printf("MSG do QG: prepare-se para a missao\n");
    leia_mapa(&linhas, &colunas, MAPA, &colunabarco);    // Lê o mapa da região
    printf("MSG do QG: segue mapa da batalha.\n");
    printf("\n    MAPA DA BATALHA\n  ");
    escreva_mapa_tela(linhas, colunas, MAPA);    // Escreve o mapa na tela
    printf("MSG do QG: preparando artilharia para lhe dar cobertura.\nMSG do QG: cuidado com fogo amigo...\nMSG do QG: preparados para iniciar bombardeio da frota inimiba.\n");
    printf("MSG do QG: permissao para iniciar a missao concedida.\n");
    printf("MSG do QG: a sua posicao e: (%d, %d)\nMSG do QG: boa sorte!\n", linhabarco, colunabarco);
    while(jogocontinua) {
        printf("MSG do QG: escolha movimento ('e'=esquerda,'b'=baixo,'d'=direita,'c'=cima,'f'=fim): ");
        jogocontinua=movimenta_barco(&linhabarco, &colunabarco, linhas, colunas, MAPA);
        if (jogocontinua==2) {
            escreva_mapa_tela(linhas, colunas, MAPA);           // Escreve o mapa na tela
            printf("MSG do QG: voce ficou parado em (%2d,%2d)!\n", linhabarco, colunabarco);
        }
        else {
            printf("MSG do QG: moveu-se para (%2d,%2d)\nMSG do QG: segue mapa da batalha:  \n", linhabarco, colunabarco);
            escreva_mapa_arquivo(linhas, colunas, MAPA);    // Escreve o mapa no arquivo secreto
            escreva_mapa_tela(linhas, colunas, MAPA);           // Escreve o mapa na tela
            if(tiros(linhas, colunas, MAPA)==FALSE) {
                jogocontinua=0;
            }
        }
    }
    printf("MSG do QG: fim de jogo.");
    return 0;
}


