# Se definen los archivos generados por YACC como una macro para facilitar su manejo
Gram=y.tab.c y.tab.h

# Objetivo principal: compila el programa final incluyendo el nuevo motor vectorial
all: $(Gram) 
	@gcc -o calc y.tab.c symbol.c init.c math.c vector_math.c -lm
	@echo "Compilación completada exitosamente. Ejecuta ./calc para iniciar."

# Regla para generar el analizador léxico y sintáctico a partir de la gramática
$(Gram): hoc3.y
	@yacc -d hoc3.y

# Objetivo de limpieza: elimina ejecutables y archivos temporales para un reinicio limpio
clean:
	@rm -f *.tab.* calc 
	@echo "Proyecto limpio."
