#include "hoc.h"
#include "y.tab.h"
#include <math.h>

extern double   Log(), Log10(), Sqrt(), Exp( ) , integer ( ) ;

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

static struct {	/*	Predefinidos */
char *name;
double	(*func)(double);
} builtins[] =	{
"sin",	sin,
"cos" ,	cos,
"atan",	atan,
"log", Log,
"log10", Log10,
"exp", Exp,
"sqrt",	Sqrt,   /*	verifica rango */
"int" ,	integer,
"abs",	fabs,
0,	0
};

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










