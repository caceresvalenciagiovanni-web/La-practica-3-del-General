#include "hoc.h"
#include "y.tab.h"
#include <stdio.h>

/* Se importan las referencias de las funciones desde math.c */
extern Vector *Sin(), *Cos(), *Atan(), *Log(), *Log10(), *Exp(), *Sqrt(), *Integer(), *Abs();

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

/* Diccionario de funciones integradas (built-ins) asociadas a punteros de funciones vectoriales */
static struct {
    char *name;
    Vector *(*func)(Vector *);
} builtins[] = {
    "sin",   Sin,
    "cos",   Cos,
    "atan",  Atan,
    "log",   Log,
    "log10", Log10,
    "exp",   Exp,
    "sqrt",  Sqrt,
    "int",   Integer,
    "abs",   Abs,
    0,       0
};

void init() {
    int i;
    Symbol *s;
    Vector *v;

    /* Se instalan las constantes matemáticas en la tabla de símbolos */
    for (i = 0; consts[i].name; i++) {
        v = creaVector(1);
        v->vec[0] = consts[i].cval;
        install(consts[i].name, VAR, v);
    }
    
    /* Se instalan las funciones integradas en la tabla de símbolos bajo el identificador BLTIN */
    for (i = 0; builtins[i].name; i++) {
        s = install(builtins[i].name, BLTIN, NULL);
        s->u.ptr = builtins[i].func;
    }
}
