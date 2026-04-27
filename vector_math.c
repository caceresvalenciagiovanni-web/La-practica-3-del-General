#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hoc.h"

/* Se declara la función externa de manejo de errores para interrumpir operaciones inválidas. */
extern void execerror(char *s, char *t);

/* Se reserva memoria dinámica tanto para la estructura del vector como para su arreglo de componentes. */
Vector *creaVector(int n) {
    Vector *v = (Vector *)malloc(sizeof(Vector));
    if (v == NULL) execerror("Out of memory", "creaVector");
    
    v->n = n;
    v->vec = (double *)malloc(sizeof(double) * n);
    if (v->vec == NULL) execerror("Out of memory", "creaVector array");
    
    return v;
}

/* Se genera una copia exacta e independiente de un vector existente en un nuevo espacio de memoria. */
Vector *copiaVector(Vector *a) {
    Vector *c = creaVector(a->n);
    int i;
    for(i = 0; i < a->n; i++) {
        c->vec[i] = a->vec[i];
    }
    return c;
}

/* Se imprime el contenido del vector en la salida estándar. 
   Si el vector es de dimensión 1, se imprime como un escalar puro. */
void imprimeVector(Vector *a) {
    int i;
    if (a == NULL) return;
    
    if (a->n == 1) {
        printf("\t%.8g\n", a->vec[0]);
    } else {
        printf("\t[ ");
        for(i = 0; i < a->n; i++) {
            printf("%.8g ", a->vec[i]);
        }
        printf("]\n");
    }
}

/* Se realiza la suma aritmética componente a componente entre dos vectores de igual dimensión. */
Vector *sumaVector(Vector *a, Vector *b) {
    Vector *c;
    int i;
    if (a->n != b->n) execerror("Dimensiones incompatibles", "en suma");
    
    c = creaVector(a->n);
    for(i = 0; i < a->n; i++) c->vec[i] = a->vec[i] + b->vec[i];
    return c;
}

/* Se realiza la resta aritmética componente a componente entre dos vectores de igual dimensión. */
Vector *restaVector(Vector *a, Vector *b) {
    Vector *c;
    int i;
    if (a->n != b->n) execerror("Dimensiones incompatibles", "en resta");
    
    c = creaVector(a->n);
    for(i = 0; i < a->n; i++) c->vec[i] = a->vec[i] - b->vec[i];
    return c;
}

/* Se realiza el producto componente a componente (Hadamard) entre dos vectores. */
Vector *multiVector(Vector *a, Vector *b) {
    Vector *c;
    int i;
    if (a->n != b->n) execerror("Dimensiones incompatibles", "en multiplicacion");
    
    c = creaVector(a->n);
    for(i = 0; i < a->n; i++) c->vec[i] = a->vec[i] * b->vec[i];
    return c;
}

/* Se calcula el producto punto (escalar) y se encapsula el resultado en un vector unidimensional. */
Vector *productoPunto(Vector *a, Vector *b) {
    Vector *c;
    double suma = 0.0;
    int i;
    
    if (a->n != b->n) execerror("Dimensiones incompatibles", "en producto punto");
    for(i = 0; i < a->n; i++) suma += (a->vec[i] * b->vec[i]);
    
    c = creaVector(1);
    c->vec[0] = suma;
    return c;
}

/* Se calcula el producto cruz geométrico. Esta operación está estrictamente limitada a vectores tridimensionales. */
Vector *productoCruz(Vector *a, Vector *b) {
    Vector *c;
    if (a->n != 3 || b->n != 3) execerror("El producto cruz requiere vectores 3D", "");
    
    c = creaVector(3);
    c->vec[0] = a->vec[1] * b->vec[2] - a->vec[2] * b->vec[1];
    c->vec[1] = a->vec[2] * b->vec[0] - a->vec[0] * b->vec[2];
    c->vec[2] = a->vec[0] * b->vec[1] - a->vec[1] * b->vec[0];
    return c;
}

/* Se calcula la norma euclidiana (longitud o magnitud) de un vector. */
double magnitudVector(Vector *v) {
    double suma = 0.0;
    int i;
    for(i = 0; i < v->n; i++) suma += (v->vec[i] * v->vec[i]);
    return sqrt(suma);
}
