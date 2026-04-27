#include <string.h>
#include <stdlib.h>
#include "hoc.h"
#include "y.tab.h"

/* Se declara la función de error para evitar advertencias de compilación */
void execerror(char *s, char *t);

/* Tabla de símbolos: lista ligada de estructuras Symbol */
static Symbol *symlist = 0;

/**
 * Busca un nombre en la tabla de símbolos.
 * @param s Cadena de texto con el nombre a buscar.
 * @return Puntero al símbolo encontrado o 0 si no existe.
 */
Symbol *lookup(char *s)
{
    Symbol *sp;
    for (sp = symlist; sp != (Symbol *)0; sp = sp->next) 
        if (strcmp(sp->name, s) == 0) 
            return sp;
    return 0; 
}

/**
 * Instala un nuevo símbolo en la tabla.
 * @param s Nombre del símbolo.
 * @param t Tipo (VAR, BLTIN, INDEF).
 * @param v Puntero al objeto Vector inicial.
 * @return Puntero al símbolo recién creado e instalado.
 */
Symbol *install(char *s, int t, Vector *v)
{
    Symbol *sp;
    char *emalloc();

    sp = (Symbol *) emalloc(sizeof(Symbol));
    sp->name = emalloc(strlen(s) + 1); /* +1 para el carácter nulo '\0' */
    strcpy(sp->name, s);
    sp->type = t;
    sp->u.vec = v;      /* CAMBIO CLAVE: Se almacena el puntero al vector */
    sp->next = symlist; /* Se inserta al inicio de la lista ligada */
    symlist = sp; 
    return sp; 
}

/**
 * Envoltorio para malloc que verifica la disponibilidad de memoria.
 * @param n Cantidad de bytes a reservar.
 * @return Puntero a la memoria reservada.
 */
char *emalloc(unsigned n)
{
    char *p;
    p = malloc(n); 
    if(p == 0)
        execerror("out of memory", (char *) 0); 
    return p; 
}




