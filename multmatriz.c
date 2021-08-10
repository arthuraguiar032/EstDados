#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Verfica se duas matrizes de tamanho n são iguais*/
void verificaIgualdade(int n, int **ma, int **mb){
    int igualdade =1;

    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if (ma[i][j]!=mb[i][j]) {
                igualdade = 0;
            }
        }
    }
    if(igualdade==1){
        printf("\nResultado Correto \n");
    }
}

void imprimeMatriz(int n , int **matriz){
    for(int i =0; i<n; i++){
        for(int j =0; j<n; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*Multiplicacao Tradicional de Matrizes*/
void multTradicional(int n, int **matriza, int **matrizb, int **matrizc){
    int aux =0;
    for(int i =0; i<n;i++){
        for(int j =0; j<n; j++){
			aux=0;
            matrizc[i][j] =0;
            for(int k =0; k<n; k++){
                aux = aux + matriza[i][k] * matrizb[k][j];
            }
            matrizc[i][j]=aux;
        }
    }
}

/*Adiciona ou subtrai matrizes, op=1 para soma e op=-1 para subtracao*/
void operacaoMat(int n, int op, int **A, int **B, int **C){
    if(op==1){
        for(int i =0; i<n; i++){
            for(int j=0; j<n;j++){
                C[i][j]= A[i][j] + B[i][j];
            }
        }
    }else if(op==-1){
        for(int i =0; i<n; i++){
            for(int j=0; j<n;j++){
                C[i][j]= A[i][j] - B[i][j];
            }
        }
    }
}

/*Particionar uma matriz em quatro diferentes*/
void particionaMat(int n, int **mat, int **mat00, int **mat01, int **mat10, int **mat11){
    int m =n/2;

    for(int i =0; i<n; i++){
        for(int j =0; j<n; j++){
            if(i<m&&j<m){
                mat00[i][j]=mat[i][j];
            }

            if(i<m&&j>=m){
                mat01[i][j-m]=mat[i][j];
            }

            if(i>=m&&j<m){
                mat10[i-m][j]=mat[i][j];
            }

            if(i>=m&&j>=m){
                mat11[i-m][j-m]=mat[i][j];
            }
        }
    }
}

/*Concatena 4 matrizes em uma só*/
void concatenaMat(int m, int **mtr00, int **mtr01, int **mtr10, int **mtr11, int **mtr){
    int n =m*2;

    for(int i =0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i<m&&j<m){
                mtr[i][j]=mtr00[i][j];
            }
            if(i<m&&j>=m){
                mtr[i][j]=mtr01[i][j-m];
            }
            if(i>=m&&j<m){
                mtr[i][j]=mtr10[i-m][j];
            }
            if(i>=m&&j>=m){
                mtr[i][j]=mtr11[i-m][j-m];
            }
        }
    }
}

/*Multiplicacao de Strassen de matrizes*/
void multStrassen(int n, int **a, int **b, int **c){
    if(n==2){
        int M1 = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
        int M2 = (a[1][0] + a[1][1]) * (b[0][0]);
        int M3 = (a[0][0]) * (b[0][1] - b[1][1]);
        int M4 = (a[1][1]) * (b[1][0] - b[0][0]);
        int M5 = (a[0][0] + a[0][1]) * (b[1][1]);
        int M6 = (a[1][0] - a[0][0]) * (b[0][0] + b[0][1]);
        int M7 = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);

        c[0][0] = M1 + M4 - M5 + M7;
        c[0][1] = M3 + M5;
        c[1][0] = M2 + M4;
        c[1][1] = M1 - M2 + M3 + M6;

    } else{
        int m = n/2; //tamanho das novas matrizes

        int **a00, **a01, **a10, **a11, **b00, **b01, **b10, **b11;

        /*alocando memoria para as matrizes, que vao ser geradas a partir do particionamento das matrizes A e B*/
        a00 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            a00[i]= (int *)malloc(m*sizeof(int));
        }
        a01 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            a01[i]= (int *)malloc(m*sizeof(int));
        }
        a10 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            a10[i]= (int *)malloc(m*sizeof(int));
        }
        a11 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            a11[i]= (int *)malloc(m*sizeof(int));
        }
        b00 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            b00[i]= (int *)malloc(m*sizeof(int));
        }
        b01 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            b01[i]= (int *)malloc(m*sizeof(int));
        }
        b10 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            b10[i]= (int *)malloc(m*sizeof(int));
        }
        b11 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            b11[i]= (int *)malloc(m*sizeof(int));
        }

        /*Matrizes auxiliares*/
        int **x, **y, **o;

        x = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            x[i]= (int *)malloc(m*sizeof(int));
        }
        y = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            y[i]= (int *)malloc(m*sizeof(int));
        }
        o = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            o[i]= (int *)malloc(m*sizeof(int));
        }
        for(int i =0; i<m; i++){
            for(int j=0; j<m; j++){
                o[i][j] = 0;
            }
        }

        /*Particionando as matrizes*/
        particionaMat(n, a, a00, a01, a10, a11);
        particionaMat(n, b, b00, b01, b10, b11);

        /*M1 = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1])*/
        int **M1;
        M1 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            M1[i]= (int *)malloc(m*sizeof(int));
        }
        operacaoMat(m, 1, a00, a11, x);
        operacaoMat(m, 1, b00, b11, y);
        multStrassen(m, x, y, M1);

        /*M2 = (a[1][0] + a[1][1]) * (b[0][0])*/
        int **M2;
        M2 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            M2[i]= (int *)malloc(m*sizeof(int));
        }
        operacaoMat(m, 1, a10, a11, x);
        multStrassen(m, x, b00, M2);

        /*M3 = (a[0][0]) * (b[0][1] - b[1][1])*/
        int **M3;
        M3 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            M3[i]= (int *)malloc(m*sizeof(int));
        }
        operacaoMat(m, -1, b01, b11, x);
        multStrassen(m, a00, x, M3);

        /*M4 = (a[1][1]) * (b[1][0] - b[0][0])*/
        int **M4;
        M4 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            M4[i]= (int *)malloc(m*sizeof(int));
        }
        operacaoMat(m, -1, b10, b00, x);
        multStrassen(m, a11, x, M4);

        /*M5 = (a[0][0] + a[0][1]) * (b[1][1])*/
        int **M5;
        M5 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            M5[i]= (int *)malloc(m*sizeof(int));
        }
        operacaoMat(m, 1, a00, a01, x);
        multStrassen(m, x, b11, M5);

        /*M6 = (a[1][0] - a[0][0]) * (b[0][0] + b[0][1])*/
        int **M6;
        M6 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            M6[i]= (int *)malloc(m*sizeof(int));
        }
        operacaoMat(m, -1, a10, a00, x);
        operacaoMat(m, 1, b00, b01, y);
        multStrassen(m, x, y, M6);

        /*M7 = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1])*/
        int **M7;
        M7 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            M7[i]= (int *)malloc(m*sizeof(int));
        }
        operacaoMat(m, -1, a01, a11, x);
        operacaoMat(m, 1, b10, b11, y);
        multStrassen(m, x, y, M7);

        /*Libera memoria das matrizes auxiliares criadas, a partir do particionamentos das matrizes A e B*/
        for (int i=0; i < m; i++){
            free(a00[i]) ;
        }
        free(a00);
        for (int i=0; i < m; i++){
            free(a01[i]) ;
        }
        free(a01);
        for (int i=0; i < m; i++){
            free(a10[i]) ;
        }
        free(a10);
        for (int i=0; i < m; i++){
            free(a11[i]) ;
        }
        free(a11);
        for (int i=0; i < m; i++){
            free(b00[i]) ;
        }
        free(b00);
        for (int i=0; i < m; i++){
            free(b01[i]) ;
        }
        free(b01);
        for (int i=0; i < m; i++){
            free(b10[i]) ;
        }
        free(b10);
        for (int i=0; i < m; i++){
            free(b11[i]) ;
        }
        free(b11);
        for (int i=0; i < m; i++){
            free(o[i]) ;
        }
        free(o);

        /*Calculando as 4 partes do resultado da matriz*/
        int **c00;
        c00 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            c00[i]= (int *)malloc(m*sizeof(int));
        }
        int **c01;
        c01 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            c01[i]= (int *)malloc(m*sizeof(int));
        }
        int **c10;
        c10 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            c10[i]= (int *)malloc(m*sizeof(int));
        }
        int **c11;
        c11 = (int **)malloc(m*sizeof(int*));
        for(int i =0; i<m; i++){
            c11[i]= (int *)malloc(m*sizeof(int));
        }

        /*c[0][0] = M1 + M4 - M5 + M7*/
        operacaoMat(m, -1, M7, M5, x);
        operacaoMat(m, 1, M1, M4, y);
        operacaoMat(m, 1, x, y, c00);

        /*c[0][1] = M3 + M5*/
        operacaoMat(m, 1, M3, M5, c01);

        /*c[1][0] = M2 + M4*/
        operacaoMat(m, 1, M2, M4, c10);

        /*c[1][1] = M1 - M2 + M3 + M6*/
        operacaoMat(m, 1, M3, M6, x);
        operacaoMat(m, -1, M1, M2, y);
        operacaoMat(m, 1, y, x, c11);

        /*Liberando memoria das matrizes M's*/
        for (int i=0; i < m; i++){
            free(x[i]) ;
        }
        free(x);
        for (int i=0; i < m; i++){
            free(y[i]) ;
        }
        free(y);

        for (int i=0; i < m; i++){
            free(M1[i]) ;
        }
        free(M1);
        for (int i=0; i < m; i++){
            free(M2[i]) ;
        }
        free(M2);
        for (int i=0; i < m; i++){
            free(M3[i]) ;
        }
        free(M3);
        for (int i=0; i < m; i++){
            free(M4[i]) ;
        }
        free(M4);
        for (int i=0; i < m; i++){
            free(M5[i]) ;
        }
        free(M5);
        for (int i=0; i < m; i++){
            free(M6[i]) ;
        }
        free(M6);
        for (int i=0; i < m; i++){
            free(M7[i]) ;
        }
        free(M7);

        /*concatenando as matrizes resultado*/
        concatenaMat(m, c00, c01, c10, c11, c);

        /*Liberando memoria das matrizes resultado*/
        for (int i=0; i < m; i++){
            free(c00[i]) ;
        }
        free(c00);
        for (int i=0; i < m; i++){
            free(c01[i]) ;
        }
        free(c01);
        for (int i=0; i < m; i++){
            free(c10[i]) ;
        }
        free(c10);
        for (int i=0; i < m; i++){
            free(c11[i]) ;
        }
        free(c11);

    }
}

int main(int argc, char *argv[]){
    /*variaveis*/
    int n =atoi(argv[1]);
    if(n%2!=0&&n<2){
        printf("\nEntre com um numero n>=2, da forma 2^k.");
        exit(0);
    }

    int **A, **B, **Ct, **Cs;

    A = (int **)malloc(n*sizeof(int*));
    for(int i =0; i<n; i++){
        A[i]= (int *)malloc(n*sizeof(int));
    }
    B = (int **)malloc(n*sizeof(int*));
    for(int i =0; i<n; i++){
        B[i]= (int *)malloc(n*sizeof(int));
    }
    Ct = (int **)malloc(n*sizeof(int*));
    for(int i =0; i<n; i++){
        Ct[i]= (int *)malloc(n*sizeof(int));
    }
    Cs = (int **)malloc(n*sizeof(int*));
    for(int i =0; i<n; i++){
        Cs[i]= (int *)malloc(n*sizeof(int));
    }

    /*preencher as matrizes com numeros inteiros aleatorios de -1000 a 1000*/
    srand(time(NULL));
    for(int i =0; i<n; i++){
        for(int j =0; j<n; j++){
            int numAleatorio = (rand() % 2001) - 1000;
            A[i][j]=numAleatorio;
            numAleatorio = (rand() % 2001) - 1000;
            B[i][j]=numAleatorio;
        }
    }

    /*chamada das funcoes de multiplicacao de matrizes, calculando o tempo*/
    clock_t TicksT[2];
    TicksT[0] = clock();
    multTradicional(n, A, B, Ct);
    TicksT[1] = clock();
    double tempoT = (TicksT[1] - TicksT[0]) * 1000.0 / (double)CLOCKS_PER_SEC;

    clock_t TicksS[2];
    TicksS[0] = clock();
    multStrassen(n, A, B, Cs);
    TicksS[1] = clock();
    double tempoS = (TicksS[1] - TicksS[0]) * 1000.0 / (double)CLOCKS_PER_SEC;

    verificaIgualdade(n, Ct, Cs);

    // libera a mem�ria das matrizes
    for (int i=0; i < n; i++){
        free (A[i]) ;
    }
    free (A);
    for (int i=0; i < n; i++){
        free (B[i]) ;
    }
    free (B);
    for (int i=0; i < n; i++){
        free (Ct[i]) ;
    }
    free (Ct);
    for (int i=0; i < n; i++){
        free (Cs[i]) ;
    }
    free (Cs);


    printf("\nO tempo da tradicional: %g ms", tempoT);
    printf("\nO tempo da Strassen: %g ms", tempoS);

    return 0;
}
