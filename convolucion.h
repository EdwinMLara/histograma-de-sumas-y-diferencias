#ifndef CONVOLUCION
#define CONVOLUCION
#define pi 3.14159


#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <matrix.h>
#include <imagen.h>
#include <math.h>

using namespace cv;
using namespace std;

int obtener_fase_matrix(int col){
    int fase;
    fase = (col -1)/2;
    return fase;
}

int ** convolucion_filtro_gauseano(int **imagen,int **elemento,int fase,int row_imagen,int col_imagen, int divisor){
    int i,k,i1,k1,aux1,aux2,aux;
    int **matrix;
    matrix = crear_matrix(row_imagen,col_imagen);
    aux=0;

    for(i=fase;i<row_imagen-fase;i++){
        for(k=fase;k<col_imagen-fase;k++){
               i1=0;
               k1=0;
               for(aux1=i-fase;aux1<i+fase;aux1++){
                   for(aux2=k-fase;aux2<k+fase;aux2++){
                       aux = aux + imagen[aux1][aux2]*elemento[i1][k1];
                       k1++;
                   }
                   k1=0;
                   i1++;
               }
               aux = aux/divisor;
               matrix[i][k]=aux;
               aux = 0;
        }
    }

    return matrix;
}

int ** convolucion_con_mascaras(int **imagen,int **elemento,int fase,int row_imagen,int col_imagen){
    int i,k,i1,k1,aux1,aux2,aux;
    int **matrix;

    int ima,ele;
    matrix = crear_matrix(row_imagen,col_imagen);
    aux=0;

    for(i=fase;i<row_imagen-fase;i++){
        for(k=fase;k<col_imagen-fase;k++){
               i1=0;
               k1=0;
               for(aux1=i-fase;aux1<=i+fase;aux1++){
                   for(aux2=k-fase;aux2<=k+fase;aux2++){
                       ima = imagen[aux1][aux2];
                       ele = elemento[i1][k1];
                       aux = aux + ima*ele;
                       k1++;
                   }
                   k1=0;
                   i1++;
               }
               matrix[i][k]=aux;
               aux = 0;
        }
    }

    return matrix;
}

int ** suma_matrices(int** mx,int ** my,int row_imagen,int col_imagen,int *maximo){
    int i,k;
    int **matrix;
    float aux3;
    matrix = crear_matrix(row_imagen,col_imagen);
    *maximo = 0;
    for(i=0;i<row_imagen;i++){
        for(k=0;k<col_imagen;k++){
            aux3 =(float) sqrt( pow(mx[i][k],2) + pow(my[i][k],2));
            matrix[i][k] = (int) aux3;
            if(*maximo<matrix[i][k])
                *maximo = matrix[i][k];
        }
    }
    return matrix;
}



#endif // CONVOLUCION

