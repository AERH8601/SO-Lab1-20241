#include <stdio.h>
#include <stdlib.h>

/*
test
-> 1.desc: toomany command-line arguments
-> 1.run ./reverse in.txt out,txt burguer.txt
-> 1.err. usage: reverse <input> <output
-> 1.out.
*/

// Funcion mani

int main(int argc, char *argv[])
{
    // Verificar si hay más de 3 argumentos (incluyendo el nombre del programa)
    if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    return 0;
}
