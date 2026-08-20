#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 11 // definindo o tamanho da matriz que vai ser o mapa

void naviosnomapa(char mapa[TAM][TAM],int quant,int tamN)
{
    int linha,coluna,VouH,pode,i,j; // variaveis de controle para definir se vai ser vertical ou horizontal e se pode colocar um navio ou nao
    for (i=0;i<quant;i++)
    {
        do
       {
        linha = rand()%(TAM-1)+1;// resto da divisao pelo tamanho da matriz menos uma pra ser entre 0 e 10, mas como na matriz de jogo nao pode ter barco na linha e coluna 0, soma-se +1 para que isso nao ocorra
        coluna = rand()%(TAM-1)+1;
        VouH = rand()%2; // sortear se vai ser horizontal ou vertical, sendo 0 para vertical e 1 para horizontal
        pode=1; //definindo se pode colocar um navio
           for(j=0;j<tamN;j++)
           {
               if(VouH==1)// caso deu horizontal
               {
                   if(linha+j>=TAM || mapa[linha+j][coluna]!='-') // verificando se cabe na coluna do mapa
                   {
                       pode=0; // retornando o 0 para o fim do looping
                   }
               }else // caso deu vertical
                {
                   if (coluna+j>=TAM|| mapa[linha][coluna+j]!='-') // verificando se cabe na linha do mapa
                   {
                        pode=0;
                   }
                }
           }
       }while(pode==0);
          for(j=0;j<tamN;j++) // resetando o indice j para colocar os navios de acordo com oq foi sorteado
          {
             if(VouH==1)// colocando na vertical
             {
                  mapa[linha+j][coluna]='W';
             }else
              {
                  mapa[linha][coluna+j]='W'; // colocando na horizontal
              }
          }
    }
}

void mostrarmapa(char mapa[TAM][TAM]) // funcao para imprimir o mapa durante o jogo
{
   int i,j;
   char l='A',n='1';
   for (i=0;i<TAM;i++)
   {
    mapa[i+1][0]=l++; // fazendo a coluna das letras
        for(j=0;j<TAM;j++)
        {
            if (i==1 && j==0) // if para corrigir o A e o 10
            {
                mapa[i][j]='A';
            }
            if(i==0 && j==10)
            {
                mapa[i][j]='10';
            }
            mapa[0][j+1]=n++; // fazendo a linha dos numeros
            if (mapa[i][j]=='W') // caso haja com navio na posicao, censura ele com agua ma hora de aparecer na tela
            {
                printf("- ");
            }else
             {
                printf("%c ",mapa[i][j]); // preeche o mapa com a agua ou com o elemento do tiro (X ou O)
             }
        }
    printf("\n");
   }
}

void mostrarmapafinal(char mapa[TAM][TAM]) // funcao para imprimir o mapa no final do jogo mostrando todos os elementos, navios,acertos,erros e agua
{
   int i,j;
   char l='A',n='1';
   for (i=0;i<TAM;i++)
   {
    mapa[i+1][0]=l++; // fazendo a coluna das letras
        for(j=0;j<TAM;j++)
        {
            if (i==1 && j==0) // if para corrigir o A e o 10
            {
                mapa[i][j]='A';
            }
            if(i==0 && j==10)
            {
                mapa[i][j]='10';
            }
            mapa[0][j+1]=n++; // fazendo a linha dos numeros
            printf("%c ",mapa[i][j]); // preeche o mapa
        }
    printf("\n");
   }
}

int acertoerro(char mapa[11][11],char linhat,int colunat) // funcao para verificar se houve um acerto no navio, na agua, ou coordenadas ja jogadas ou invalidas
{
    int x=64;
    if(mapa[linhat-x][colunat] == 'W') // acertou um navio
    {
         return 1;
    }else if(mapa[linhat-x][colunat]=='X' || mapa[linhat-x][colunat]=='O') // repetiu a coordenada
     {
         return 2;
     }else if(linhat>74 || linhat<65 || linhat==0 || colunat==0 || colunat>10)// coordenadas invalidas
      {
         return 3;
      }else // errou, acertou agua
       {
         return 4;
       }
}

int ganhou(int tiros,int acertos) // funcao para verificar se acabou os tiros ou o jogador acertou todos os navios
{
    if(acertos==17) // acertou todos os navios ganhou
    {
        printf("\nSeus Tiros foram muitos precisos e afundou toda a frota inimiga Voce venceu!!!\n");
        return 0;
    }
    if(tiros==0) // acabou os tiros perdeu
    {
        printf("\nSeus Tiros Acabaram e nao afundou toda a tropa de navios inimiga Voce perdeu!!!\n");
        return 0;
    }
}

int main()
{
    char mapa[TAM][TAM]; // 11 por 11 pq as coordenadas ja estao na matriz
    char linhat; // linha do tiro
    int i,j,tiros=25,colunat,acertos=0;
    int x=64;// 64 pois e o valor de A na tabela Ascii menos um por conta do tamanho da matriz

    srand(time(NULL)); // setando a seed para gerar numeros aleatorios

    for(i=0;i<TAM;i++) // inicializando o mapa com agua
    {
       for(j=0;j<TAM;j++)
       {
           mapa[0][0]=' ';
           mapa[i][j]='-';
       }
    }
   naviosnomapa(mapa,1,4); // setando aleatoriamente a posicao dos navios com a funcao
   naviosnomapa(mapa,2,3);
   naviosnomapa(mapa,1,2);
   naviosnomapa(mapa,5,1);

    while(tiros<=25) // looping que roda os 25 tiros
   {
      mostrarmapa(mapa);
      printf("Digite a coordenada do tiro: ");
      scanf("%c %d",&linhat,&colunat);
      fflush(stdin);
      system("clear"); // limpando a tela a cada coordenada escolhida no Linux
      //system("cls"); // limpando a tela a cada coordenada escolhida no Windows
      if (acertoerro(mapa,linhat,colunat)== 1) // chamando a funcao para verificar se acertou um navio ou nao
      {
           printf("\nACERTOU um navio inimigo!\n");
           mapa[linhat-x][colunat]='x'; // atualizando o char referente ao tiro
           tiros--;
           acertos++;

      }else if(acertoerro(mapa,linhat,colunat)==2)
       {
            printf("\nVoce ja atirou aqui!\n");
            tiros=tiros;
            acertos=acertos;
       }else if(acertoerro(mapa,linhat,colunat)==3)
        {
             printf("\nCoordenadas Invalidas!Digite outra!\n");
             tiros=tiros;
             acertos=acertos;
        }else
         {
             printf("\nNao acertou nada!\n");
             mapa[linhat-x][colunat]='o';
             tiros--;
             acertos=acertos;

         }
     if(ganhou(tiros,acertos)==0) // verificando se o jogagor ganhou ou perdeu chamando a funcao
     {
         mostrarmapafinal(mapa); // chamando a funcao que mostra o mapa com todos os elementos
         return 0; // encerrando o jogo
     }
     printf("\nTiros que ainda possui: %d\n",tiros); // imprimindo os tiros restantes
     printf("\n");
   }

}
