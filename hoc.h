/* Se define la estructura Vector para que esté disponible en todo el proyecto */
struct vector {
    int n;          /* Cantidad de elementos */
    double *vec;    /* Arreglo dinámico de componentes */
};
typedef struct vector Vector;

/* Se define la entrada de la tabla de símbolos adaptada a vectores */
typedef struct Symbol {
    char   *name;   /* Nombre de la variable (ahora puede ser de más de una letra) */
    short   type;   /* VAR, BLTIN, INDEF */
    union {
        Vector *vec;                /* Si es VAR, se almacena un puntero al objeto Vector */
        Vector *(*ptr)();           /* Si es BLTIN, apunta a una función que retorna un Vector */
    } u;
    struct Symbol   *next;          /* Puntero para la lista ligada de la tabla */
} Symbol;

Symbol *install(char *s, int t, Vector *v); /* Se instala enviando un puntero Vector */
Symbol *lookup(char *s);

/* Prototipos de las operaciones vectoriales (migrados desde hoc1) */
Vector *creaVector(int n); 
double magnitudVector(Vector *v);
void imprimeVector(Vector *a); 
Vector *copiaVector(Vector *a); 
Vector *sumaVector(Vector *a, Vector *b); 
Vector *restaVector(Vector *a, Vector *b); 
Vector *multiVector(Vector *a, Vector *b); 
Vector *productoPunto(Vector *a, Vector *b);
Vector *productoCruz(Vector *a, Vector *b);

