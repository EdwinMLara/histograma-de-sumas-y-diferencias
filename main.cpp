#include <stdio.h>
#include <matrix.h>
#include <imagen.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <math.h>
#include <sumas-diferencias.h>

using namespace std;
using namespace cv;

int main()
{
    cvNamedWindow("Imagen",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Imagen Media",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Imagen Varianza",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Imagen Energia",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Imagen Correlacion",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Imagen Contraste",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Imagen Homogeniedad",CV_WINDOW_AUTOSIZE);

    Mat ima,ima_media,ima_varianza,ima_energia,ima_correlacion,ima_contraste,ima_homogeniedad;
    char nombre[20]="lena2.bmp";
   // ta su_res;
    int **ma_imagen,*h_sumas,*h_restas;
    int **imagen_media,**imagen_varianza,**imagen_energia,**imagen_correlacion,**imagen_contraste,**imagen_homogeniedad;

    int maximo;
    //float *p_s,*p_r,*ca;

    /** se utiliza 510 ya son las posibles sumas que pueden obtenerse atravez
     * de las intesidades 255 **/
    h_sumas = crear_vector(511);
    h_restas = crear_vector(511);

    ima = imread(nombre,CV_LOAD_IMAGE_GRAYSCALE);
    ma_imagen = convertir_vector_imagen_a_matrix(ima);

    imagen_media = crear_matrix(ima.rows,ima.cols);
    imagen_varianza = crear_matrix(ima.rows,ima.cols);
    imagen_energia = crear_matrix(ima.rows,ima.cols);
    imagen_correlacion = crear_matrix(ima.rows,ima.cols);
    imagen_contraste = crear_matrix(ima.rows,ima.cols);
    imagen_homogeniedad = crear_matrix(ima.rows,ima.cols);

/*    su_res.sumas = histograma_sumas(ma_imagen,h_sumas,ima.rows,ima.cols,1);

    p_s = obtener_vec_proba(h_sumas,su_res.sumas);

    su_res.restas = histograma_restas(ma_imagen,h_restas,ima.rows,ima.cols,1);

    p_r = obtener_vec_proba(h_restas,su_res.restas);

    ca = caracteristicas(p_s,p_r,511);
    imprimir_vector_float(ca,7);*/

    imagen_caracteristica(ma_imagen,imagen_media,imagen_varianza,imagen_energia,imagen_correlacion,imagen_contraste,imagen_homogeniedad,ima.rows,ima.cols,7);

    maximo = obtener_maximo_matriix(imagen_media,ima.rows,ima.cols);
    normalizar_matrix(imagen_media,maximo,255,ima.rows,ima.cols);

    maximo = obtener_maximo_matriix(imagen_varianza,ima.rows,ima.cols);
    normalizar_matrix(imagen_varianza,maximo,255,ima.rows,ima.cols);

    maximo = obtener_maximo_matriix(imagen_energia,ima.rows,ima.cols);
    normalizar_matrix(imagen_energia,maximo,255,ima.rows,ima.cols);

    maximo = obtener_maximo_matriix(imagen_correlacion,ima.rows,ima.cols);
    normalizar_matrix(imagen_correlacion,maximo,255,ima.rows,ima.cols);

    maximo = obtener_maximo_matriix(imagen_contraste,ima.rows,ima.cols);
    normalizar_matrix(imagen_contraste,maximo,255,ima.rows,ima.cols);

    maximo = obtener_maximo_matriix(imagen_homogeniedad,ima.rows,ima.cols);
    normalizar_matrix(imagen_homogeniedad,maximo,255,ima.rows,ima.cols);

    ima_media = crear_imagen(imagen_media,ima.rows,ima.cols);
    ima_varianza = crear_imagen(imagen_varianza,ima.rows,ima.cols);
    ima_energia = crear_imagen(imagen_energia,ima.rows,ima.cols);
    ima_correlacion = crear_imagen(imagen_correlacion,ima.rows,ima.cols);
    ima_contraste = crear_imagen(imagen_contraste,ima.rows,ima.cols);
    ima_homogeniedad = crear_imagen(imagen_homogeniedad,ima.rows,ima.cols);

    imshow("Imagen",ima);
    imshow("Imagen Media",ima_media);
    imshow("Imagen Varianza",ima_varianza);
    imshow("Imagen Energia",ima_energia);
    imshow("Imagen Correlacion",ima_correlacion);
    imshow("Imagen Contraste",ima_contraste);
    imshow("Imagen Homogeniedad",ima_homogeniedad);

 /*   imwrite("Media",ima_media);
    imwrite("Variaza",ima_varianza);
    imwrite("Energia",ima_energia);
    imwrite("Correlacion",ima_correlacion);
    imwrite("Contraste",ima_contraste);
    imwrite("Homogeniedad",ima_homogeniedad); */

    cvWaitKey(0);

    liberar_memoria(ma_imagen,ima.rows);
    liberar_memoria(imagen_media,ima.rows);
    liberar_memoria(imagen_varianza,ima.rows);
    liberar_memoria(imagen_energia,ima.rows);
    liberar_memoria(imagen_correlacion,ima.rows);
    liberar_memoria(imagen_contraste,ima.rows);
    liberar_memoria(imagen_homogeniedad,ima.rows);
    free(h_sumas);
    free(h_restas);
    //free(p_s);
    //free(p_r);
    //free(ca);


    return 0;
}
