#include "hoc.h"
#include "y.tab.h"
#include <math.h>

/* Arreglo de constantes matemáticas */
static struct {
    char *name;
    double cval;
} consts[] = {
    "PI",    3.14159265358979323846,
    "E",     2.71828182845904523536,
    "GAMMA", 0.57721566490153286060,
    "DEG",   57.29577951308232087680,
    "PHI",   1.61803398874989484820,
    0,       0
};

/* Nota: En esta versión inicial, nos enfocaremos en las constantes. 
   Las funciones built-ins (sin, cos, etc.) requieren que sus envoltorios 
   en math.c sean actualizados para retornar un Vector* en lugar de un double.
*/

void init() {
    int i;
    Symbol *s;
    Vector *v;

    /* Se instalan las constantes matemáticas en la tabla de símbolos */
    for (i = 0; consts[i].name; i++) {
        /* Se crea un vector de dimensión 1 para contener el valor escalar */
        v = creaVector(1);
        v->vec[0] = consts[i].cval;
        
        /* Se instala en la tabla como una variable (VAR) inicializada */
        install(consts[i].name, VAR, v);
    }
}









