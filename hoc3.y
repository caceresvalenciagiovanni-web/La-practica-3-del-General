%{
#include "hoc.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void yyerror (char *s);
int yylex ();
void warning(char *s, char *t);
void execerror(char *s, char *t);
void fpecatch();
void init();
%}

/* Se define la pila de YACC para manejar escalares, símbolos de la tabla y vectores dinámicos. */
%union {
    double val;       /* Para valores escalares provenientes del token NUMBER */
    Symbol *sym;      /* Para los punteros a la tabla de símbolos (VAR, BLTIN, INDEF) */
    Vector *vec;      /* Para el resultado dinámico de las expresiones */
}

/* Se enlazan los tokens con sus respectivos tipos de datos en la pila. */
%token <val> NUMBER
%token <sym> VAR BLTIN INDEF
%type <vec> expr asgn vector_elements

/* Se establecen las reglas de asociatividad y precedencia de operadores. */
%right '='
%left '+' '-'
%left '*' '@' 'X'
%left UNARYMINUS
%right '^'

%% 

/* Regla principal: Manejo de múltiples líneas y evaluación de sentencias. */
list:   
    | list '\n'
    | list asgn '\n'
    | list expr '\n'  { imprimeVector($2); }
    | list error '\n' { yyerrok; } 
    ;

/* Regla de asignación: Se almacena la copia del vector en la memoria del símbolo. */
asgn:
      VAR '=' expr { 
          $1->u.vec = copiaVector($3);
          $1->type = VAR; 
          $$ = $1->u.vec; 
      }
    ;

/* Regla de construcción dinámica: Agrupación de números en arreglos (ej. [1 2 3]). */
vector_elements:
      NUMBER {
          $$ = creaVector(1);
          $$->vec[0] = $1;
      } 
    | vector_elements NUMBER {
          $$ = $1; 
          $$->n = $$->n + 1;
          $$->vec = (double *)realloc($$->vec, sizeof(double) * $$->n);
          $$->vec[$$->n - 1] = $2;
      }
    ;

/* Reglas de evaluación de expresiones matemáticas vectoriales. */
expr:      
      NUMBER { 
          /* Se encapsula el número escalar en un vector unidimensional por compatibilidad. */
          $$ = creaVector(1);
          $$->vec[0] = $1;  
      }
    | VAR { 
          if($1->type == INDEF)
              execerror("variable no definida", $1->name);
          $$ = copiaVector($1->u.vec);
      }
    | asgn { $$ = copiaVector($1); }
    | BLTIN '(' expr ')' { 
          /* Se ejecuta el puntero a la función almacenada en el símbolo pasándole el vector como argumento */
          $$ = (*($1->u.ptr))($3); 
      }
    | '[' vector_elements ']' { $$ = $2; }
    | expr '+' expr { $$ = sumaVector($1, $3); }
    | expr '-' expr { $$ = restaVector($1, $3); }
    | expr '*' expr { $$ = multiVector($1, $3); }
    | expr 'X' expr { $$ = productoCruz($1, $3); }
    | expr '@' expr { $$ = productoPunto($1, $3); }
    | '|' expr '|' {
          /* Cálculo de magnitud (retorna un escalar empaquetado en un vector 1D). */
          double mag = magnitudVector($2);
          $$ = creaVector(1);
          $$->vec[0] = mag;
      }
    | '(' expr ')' { $$ = $2; }
    | '-' expr %prec UNARYMINUS { 
          /* Multiplicación por escalar negativo (negación). */
          int i;
          Vector *temp = creaVector($2->n);
          for(i = 0; i < $2->n; i++) temp->vec[i] = -1.0;
          $$ = multiVector(temp, $2); 
      }
    ;
%%

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf begin;
char *progname;
int lineno = 1;

int main (int argc, char *argv[]){
    progname = argv[0];
    
    printf("---------------------------------------------------------------------------\n");
    printf("                           CALCULADORA VECTORIAL HOC3\n");
    printf("---------------------------------------------------------------------------\n");
    printf("Suma(+) Resta(-) Magnitud(| |) Prod.Cruz(X) Prod.Punto(@) Escalar(*)\n");
    printf("Uso de Variables: var_nombre = [1 2 3]\n");
    printf("---------------------------------------------------------------------------\n");
    
    init();
    setjmp(begin);
    signal(SIGFPE, fpecatch);
    yyparse();
    return 0;
}

void execerror(char *s, char *t){
    warning(s, t);
    longjmp(begin, 0);
}

void fpecatch(){
    execerror("excepcion de punto flotante", (char *)0);
}

/* Analizador léxico: lee la entrada carácter por carácter o agrupa palabras en símbolos. */
int yylex (){
    int c;
    while ((c = getchar ()) == ' ' || c == '\t');
    if (c == EOF)                            
        return 0;
    if (c == '.' || isdigit (c)){
        ungetc (c, stdin);
        scanf ("%lf", &yylval.val); /* Extrae el escalar matemático */
        return NUMBER;
    }
    if(isalpha(c)){
        Symbol *s;
        char sbuf[10000], *p=sbuf;
        do {
            *p++=c;
        } while ((c=getchar())!=EOF && isalnum(c));
        ungetc(c, stdin);
        *p='\0';      
        
        if((s=lookup(sbuf))==(Symbol *)NULL)
            s=install(sbuf, INDEF, NULL);
        
        yylval.sym=s;   
        if(s->type == INDEF){
            return VAR;
        } else {
            return s->type; 
        }
    }
    if(c == '\n'){
        lineno++;
    }
    return c;
}

void yyerror (char *s) 
{
    warning(s, (char *) 0);
}

void warning(char *s, char *t)
{
    fprintf (stderr, "%s: %s", progname, s);
    if(t)
        fprintf (stderr, " %s", t);
    fprintf (stderr, "cerca de la linea %d\n", lineno);
}
