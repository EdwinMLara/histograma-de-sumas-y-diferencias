#ifndef SUMASDIFERENCIAS
#define SUMASDIFERENCIAS
#include <matrix.h>
#include <math.h>
#include <convolucion.h>

typedef struct ta_tag{
    int sumas;
    int restas;
}ta;

int   histograma_sumas(int**m,int *histo,int row,int col, int d){
    int i,k,suma,total;

    total = 0;
    for(i=d;i<row-d;i++){
        for(k=d;k<col-d;k++){
            suma = m[i][k] + m[i][k+d];
            histo[suma]++;
            total++;
        }
    }
    return total;
}

int histograma_restas(int**m,int *histo,int row,int col, int d){
    int i,k,suma,total;
    total = 0;
    for(i=d;i<row-d;i++){
        for(k=d;k<col-d;k++){
            suma = m[i][k] - m[i][k+d];
            histo[suma+255]++;
            total++;
        }
    }
    return total;
}

float* obtener_vec_proba(int *h,int N){
    int i;
    float *his;

    his = crear_vector_float(510);

    for(i=0;i<510;i++)
        his[i] = (float) h[i] / N ;

    return his;
}

float media_mascara(float *p_s,int ta){
    int i;
    float aux;

    aux = 0;
    for(i=0;i<ta;i++)
        aux += (float) i*p_s[i];
    aux = aux/2;

    return aux;
}

float varianza_mascara(float *p_s,float *p_r,float media,int ta){
    int i;
    float aux,aux2,aux3;

    aux = 0;

    for(i=0;i<ta;i++){
        aux2 = i-255;
        aux3 = i-(2*media);
        aux += (pow(aux3,2)*p_s[i]) + (pow(aux2,2)*p_r[i]);
    }
    aux = aux/2;

    return aux;
}

float energia_mascara(float *p_s,float *p_r,int ta){
    int i;
    float aux,aux2;
    aux=0;
    for(i=0;i<ta;i++){
        aux2 = i-255;
        aux += (p_s[i]*pow(i,2))*(pow(aux2,2)*p_r[i]);
    }
    return aux;
}

float correlacion_mascara(float *p_s,float *p_r,float media,int ta){
    int i;
    float aux,aux2,aux3;

    aux=0;
    for(i=0;i<ta;i++){
        aux2 = i-255;
        aux3 = i-(2*media);
        aux += (pow(aux3,2)*p_s[i])-(pow(aux2,2)*p_r[i]);
    }
    aux = aux/2;

    return aux;
}

float entropia_mascara(float *p_s,float *p_r,int ta){
    int i;
    float aux;

    aux=0;
    for(i=0;i<ta;i++){
        if(i==0)
            aux += 0;
        else
            aux -=  (p_s[i]*log2(p_s[i])) - (p_r[i]*log2(p_r[i]));
    }

    return aux;
}

float contraste_mascara(float* p_r,int ta){
   int i;
   float aux,aux2;

    aux=0;
    for(i=0;i<ta;i++){
        aux2 = i-255;
        aux += pow(aux2,2)*p_r[i];
    }
     return aux;
}

float homogeniedad_mascara(float* p_r,int ta){
    int i;
    float aux,aux2;

    aux=0;
    for(i=0;i<ta;i++){
        aux2 =(i-255);
        aux2 = pow(aux2,2);
        aux2 += 1;
        if(aux2 == 0)
            aux2=0;
        else
            aux2 = (1/aux2);
        aux += aux*p_r[i];
    }
    return aux;
}

float* caracteristicas (float *p_s,float* p_r,int ta){
    float *ca,aux,aux2;
    int i;

    ca = (float*)malloc(7*sizeof(float));

    /*media*/
    aux = 0;
    for(i=0;i<ta;i++)
        aux = aux + i*p_s[i];
    aux = aux/2;
    ca[0] = aux;

    /*varianza*/
    aux = 0;
    for(i=0;i<ta;i++){
        aux2 = i-255;
        aux = i-(2*ca[0]);
        aux += (pow(aux,2)*p_s[i]) + (pow(aux2,2)*p_r[i]);
    }
    aux = aux/2;

    ca[1] = aux;

    /*energy*/

    aux=0;
    for(i=0;i<ta;i++){
        aux2 = i-255;
        aux = aux + (p_s[i]*pow(i,2)) * (pow(aux2,2)*p_r[i]);
    }
    aux = aux/2;
    ca[2] = aux;

    /*correlacion*/
    aux=0;
    for(i=0;i<ta;i++){
        aux2 = i-255;
        aux = aux + (pow(i-(2*ca[0]),2)*p_s[i]) -(pow(aux2,2)*p_r[i]);
    }
    aux = aux/2;
    ca[3] = aux;

    /*entropia*/
    aux=0;
    for(i=0;i<ta;i++){
        if(i==0)
            aux = aux + 0;
        else
            aux -= (float) p_s[i]*log2(p_s[i]) - p_r[i]*log2(p_r[i]);
    }
    ca[4] = aux;

    /*contraste*/
    aux=0;
    for(i=0;i<ta;i++){
        aux2 = i-255;
        aux += pow(aux2,2)*p_r[i];
    }
    ca[5] = aux;

    /*homogenedad*/
    aux=0;
    for(i=0;i<ta;i++){
        aux2 = 1+(i-255);
        if(aux2 == 0)
            aux2=0;
        else
            aux2 = (1/aux2);
        aux -= aux*p_r[i];
    }
    ca[6] = aux;

    return ca;
}

void imagen_caracteristica(int **imagen,int **imagen_media,int **imagen_varianza,int **imagen_energia,int **imagen_correlacion,int **imagen_contraste,int **imagen_homegeniedad,int row_ima,int col_ima,int ta_mask){
    int **aux_matrix;
    int *h_sumas,*h_restas;

    float *p_s,*p_r;
    float media,varianza,energia,correlacion,contraste,homogeniedad;
    int i,k,r,fase,aux,aux2,i1,k1;
    ta su_res;
    aux_matrix = crear_matrix(ta_mask,ta_mask);
    fase = obtener_fase_matrix(ta_mask);

    h_sumas = crear_vector(510);
    h_restas = crear_vector(510);

    for(i=fase;i<row_ima-fase;i++){
        for(k=fase;k<col_ima-fase;k++){
            /**guardadon informacion de mascara en matrix auxiliar**/
            i1=0;
            k1=0;
            for(aux=i-fase;aux<=i+fase;aux++){
                for(aux2=k-fase;aux2<=k+fase;aux2++){
                    aux_matrix[i1][k1]=imagen[aux][aux2];
                    k1++;
                }
                k1=0;
                i1++;
            }

            su_res.sumas = histograma_sumas(aux_matrix,h_sumas,ta_mask,ta_mask,1);
            su_res.restas = histograma_restas(aux_matrix,h_restas,ta_mask,ta_mask,1);

            p_s = obtener_vec_proba(h_sumas,su_res.sumas);
            p_r = obtener_vec_proba(h_restas,su_res.restas);

            media = media_mascara(p_s,510);
            varianza = varianza_mascara(p_s,p_r,media,510);
            energia = energia_mascara(p_s,p_r,510);
            correlacion = correlacion_mascara(p_s,p_r,media,510);
            contraste = contraste_mascara(p_s,510);
            homogeniedad = homogeniedad_mascara(p_r,510);


            imagen_media[i][k] = media;
            imagen_varianza[i][k] = varianza;
            imagen_energia[i][k] = energia;
            imagen_correlacion[i][k] = correlacion;
            imagen_contraste[i][k] = contraste;
            imagen_homegeniedad[i][k] = homogeniedad;


            /**se vueleven a inicializar los histogramas para volvelos a llenar**/

            for(r=0;r<510;r++){
                h_sumas[r]=0;
                h_restas[r]=0;
            }
        }

    }

}



#endif // SUMASDIFERENCIAS

