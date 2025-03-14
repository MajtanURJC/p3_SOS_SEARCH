#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <err.h>

struct Entrada {
    int pid;
    char *ruta;
    char *palabra; 
};

typedef struct Entrada Entrada;

struct Procesos {
    Entrada *array;
    int capacidad;
};

typedef struct Procesos Procesos;

int main(int argc, char *argv[]) {
    int i = 0;
    int sts;
    int pid;
    int num = 0;

    argc--;
    argv++;

    Procesos* procesos = malloc(sizeof(Procesos));
    procesos->capacidad = argc;

    procesos->array = malloc(procesos->capacidad * sizeof(Entrada));
    if (argc == 0) {
        fprintf(stderr, "No has introducido ninguna dirección\n");
        exit(EXIT_FAILURE);
    } else if (argc % 2 != 0) {
        fprintf(stderr, "Número de parámetros incorrecto\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < argc; i += 2) {
        pid = fork();
        switch (pid) {
            case -1:
                err(EXIT_FAILURE, "fork failed!");
                break;

            case 0:
                execl("/usr/bin/fgrep", "fgrep", "-q", "-s", argv[i], argv[i + 1], NULL);
                break;

            default:
                procesos->array[num].ruta = argv[i];
                procesos->array[num].palabra = argv[i + 1];
                procesos->array[num].pid = pid;
                num++;
                break;
        }
    }

    while ((pid = wait(&sts)) != -1) {
        int found = 0;
        for (i = 0; i < num; i++) {
            if (procesos->array[i].pid == pid) {
                found = 1;
                if (WIFEXITED(sts) && WEXITSTATUS(sts) == 0) {
                    printf("%s <%s>: yes\n", procesos->array[i].ruta, procesos->array[i].palabra);
                } else {
                    printf("%s <%s>: no\n", procesos->array[i].ruta, procesos->array[i].palabra);
                }
                break;
            }
        }
    }

    free(procesos->array);
    free(procesos);

    return 0;
}
