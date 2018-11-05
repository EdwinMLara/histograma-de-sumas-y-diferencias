#ifndef MORFOLOGIA
#define MORFOLOGIA

#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <matrix.h>
#include <imagen.h>

using namespace cv;
using namespace std;


int** crear_mascara(char Name[20],int* row,int *col){

    int **elemento_estructurante;
    int i,k; //variables auxiliares para el ciclos

    FILE *mask;
    mask = fopen(Name,"r");
    if(mask != NULL)
    {
        fscanf(mask,"%d",row);
        fscanf(mask,"%d",col);
        elemento_estructurante = crear_matrix(*row,*col);

        for(i=0;i<*row;i++)
            for(k=0;k<*col;k++){
                 fscanf(mask,"%d",&elemento_estructurante[i][k]);
            }
    }
    else
    {
        printf("Error el archivo no puede abrir");
    }
    fclose(mask);

    return elemento_estructurante;
}

int** dilatacion(int** elemento,int **image,int row,int col){

    int **imagen_dilatada;
    imagen_dilatada = crear_matrix(row,col);
    int i,k,aux1,aux2,i1,k1;

    for(i=2;i<row-2;i++){
        for(k=2;k<col-2;k++){
           if(image[i][k] == elemento[2][2])
           {
               i1=0;
               k1=0;
               for(aux1=i-2;aux1<i+2;aux1++){
                   for(aux2=k-2;aux2<k+2;aux2++){
                       if(elemento[i1][k1] == 255)
                           imagen_dilatada[aux1][aux2] = elemento[i1][k1];
                       else
                           imagen_dilatada[aux1][aux2] = image[aux1][aux2];
                       k1++;
                   }
                   k1=0;
                   i1++;
               }

           }
           imagen_dilatada[i][k] = image[i][k];
        }
    }

    return imagen_dilatada;
}


int** erosion(int** elemento,int **image,int row,int col){

    int **imagen_erocion;
    imagen_erocion = crear_matrix(row,col);
    int i,k,caso,i1,k1,aux1,aux2;
    caso = 0;
    for(i=2;i<row-2;i++){
        for(k=2;k<col-2;k++){

               i1=0;
               k1=0;
               for(aux1=i-2;aux1<i+2;aux1++)
               {
                 for(aux2=k-2;aux2<k+2;aux2++)
                 {
                    if(elemento[i1][k1]==255){
                        if(image[aux1][aux2] != elemento[i1][k1]){
                            caso = 1;
                            break;
                        }
                    }
                    k1++;
                 }
                 if(caso==1)
                     break;
                 k1=0;
                 i1++;
              }

              if(caso == 0)
                  imagen_erocion[i][k] = 255;
              caso = 0;
         }
     }
    return imagen_erocion;
}

int** apertura(int** elemento,int **imagen,int row,int col){
    int **aper,**er;
    aper = crear_matrix(row,col);
    er = erosion(elemento,imagen,row,col);
    aper = dilatacion(elemento,er,row,col);
    liberar_memoria(er,row);
    return aper;
}

int** cerradura(int** elemento,int **imagen,int row,int col){
    int **cerra,**di;
    cerra = crear_matrix(row,col);
    di = dilatacion(elemento,imagen,row,col);
    cerra = erosion(elemento,di,row,col);
    liberar_memoria(di,row);
    return cerra;
}



#endif // MORFOLOGIA

