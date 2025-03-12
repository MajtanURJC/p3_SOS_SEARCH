#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <err.h>

struct Entrada{
    int pid;
    char* ruta;
    char *palabra; 
};

typedef struct Entrada Entrada;

int
main(int argc, char *argv[]){
    int i = 0;
    int sts;
    int pid;

    argc--;
    argv++;

    if(argc == 0){
        fprintf(stderr,"Nos has introducido ninguna dirección");
    } else if(argc % 2 != 0){
        printf("Número de parametros incorrecto");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < argc ; i += 2){
        pid = fork();
        switch pid {
            case -1:

        }
        Entrada* entrada = malloc(sizeof(Entrada));
        entrada->pid = tmp;
        entrada->ruta = argv[i];
        entrada->palabra = argv[i+1];
        execl("/usr/bin/fgrep","fgrep","-q",entrada->direccion,entrada->palabra,NULL);
    }
    while ((pid = wait(&sts)) != -1) {
        if(WIFEXITED(sts) == 0) {
            printf("%s <%s>: yes\n",entrada->ruta,entrada->valor);
        } else {
            printf("%s <%s>: no\n",entrada->ruta,entrada->valor);
        }    
    }

    exit(EXIT_SUCCESS);
}   
