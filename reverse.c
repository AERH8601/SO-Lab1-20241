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

// Funcion principal

int main(int argc, char *argv[])
{
    struct stat input_stat, output_stat;
    FILE *input_file, *output_file;
    char **lines = NULL; // Para almacenar las lineas del archivo
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_count = 0;

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

    // Para test 2 y 3: Si se pasa un archivo de entrada, verificar si existe
    if (argc > 1)
    {
        input_file = fopen(argv[1], "r");
        if (input_file == NULL)
        {
            // Si no se puede abrir el archivo, mostrar un mensaje de error y salir
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }

        // Abrir el archivo de salida
        output_file = fopen(argv[2], "w");
        if (output_file == NULL)
        {
            fprintf(stderr, "reverse: cannot open output file '%s'\n", argv[2]);
            fclose(input_file);
            exit(1);
        }

        // Obtener información del archivo para verificar hardlinks
        if (stat(argv[1], &input_stat) == 0 && stat(argv[2], &output_stat) == 0)
        {
            if (input_stat.st_ino == output_stat.st_ino)
            {
                fprintf(stderr, "reverse: input and output file must differ\n");
                fclose(input_file);
                fclose(output_file);
                exit(1);
            }
        }

        // Leer el archivo de entrada línea por línea, invertir y escribir en el archivo de salida
        while ((read = getline(&line, &len, input_file)) != -1)
        {
            lines = realloc(lines, sizeof(char *) * (line_count + 1));
            lines[line_count] = strdup(line); // Copia la línea
            line_count++;
        }

        // Escribir las líneas en orden inverso en el archivo de salida
        for (int i = line_count - 1; i >= 0; i--)
        {
            fputs(lines[i], output_file);
            free(lines[i]); // Liberar la memoria de la línea
        }

        // Liberar la memoria de las líneas
        free(lines);

        // Cerrar el archivo después de verificar que se abrió correctamente

        fclose(input_file);
        fclose(output_file);

        if (line)
        {
            free(line);
        }
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

    return 0;
}
