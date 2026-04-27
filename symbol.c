#include  "hoc.h" 
#include  "y.tab.h"
#include  <string.h>      
#include  <stdlib.h>

void execerror(char *s, char *t);
static Symbol *symlist = 0;    /* tabla de simbolos: lista ligada */
             //char s[]
Symbol *lookup(char *s)
{
    Symbol *sp;
    for (sp = symlist; sp != (Symbol *)0; sp = sp->next) 
        if (strcmp(sp->name, s) == 0) 
            return sp;
    return 0; 
}

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

char *emalloc(unsigned n)
{
    char *p;
    p = malloc(n); 
    if(p == 0)
        execerror("out of memory", (char *) 0); 
    return p; 
}





