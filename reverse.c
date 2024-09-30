#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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
    struct stat input_stat, output_stat;

    // Para test 1: Verificar si hay más de 3 argumentos
    if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    // Para test 4: Verificar si el archivo de entrada y salida tienen el mismo nombre
    if (argc == 3 && strcmp(argv[1], argv[2]) == 0)
    {
        fprintf(stderr, "reverse: input and output file must differ\n");
        exit(1);
    }

    // Obtener información del archivo de entrada
    // Para test 5: Verificar si los archivos de entrada y salida son el mismo archivo físico (hardlinked)
    if (argc == 3)
    {
        if (stat(argv[1], &input_stat) == 0 && stat(argv[2], &output_stat) == 0)
        {
            if (input_stat.st_ino == output_stat.st_ino)
            {
                // Si los inodos son iguales, los archivos son el mismo
                fprintf(stderr, "reverse: input and output file must differ\n");
                exit(1);
            }
        }
    }

    // Para test 2 y 3: Si se pasa un archivo de entrada, verificar si existe
    if (argc > 1)
    {
        FILE *input_file = fopen(argv[1], "file");
        if (input_file == NULL)
        {
            // Si no se puede abrir el archivo, mostrar un mensaje de error y salir
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }

        // Cerrar el archivo después de verificar que se abrió correctamente

        fclose(input_file);
    }

    return 0;
}
