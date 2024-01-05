#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
#include "dlfcn.h"

int main(int argc, char* argv[]){

    char *s="-s";
    char *a="-a";
    char *j="-j";
    char *d="-d";
    int sflag=0;
    int aflag=0;
    int jflag=0;
    int dflag=0;
    int flag=0;
    

    for(int i=0;i<argc;i++){
        if(strcmp(argv[i],s)==0){sflag=1;}
        if(strcmp(argv[i],a)==0){aflag=1;}
        if(strcmp(argv[i],j)==0){jflag=1;}
        if(strcmp(argv[i],d)==0){dflag=1;}
    }


    if(sflag==1 &&jflag==0){
        printf("%s\n","---Ejercicio 1.1 del Laboratorio 2:---");
        memory_specs(flag);
        printf("%s\n","---Ejercicio 1.2 del Laboratorio 2:---");
        mem_info(flag);
        printf("%s\n","---Ejercicio 1.3 del Laboratorio 2:---");
        cpu_info(flag);
    }
    else if(sflag==1 && jflag==1){
        flag=1;
        printf("%s\n","---Ejercicio 1.1 del Laboratorio 2 en formato JSON:---");
        memory_specs(flag);
        printf("%s\n","---Ejercicio 1.2 del Laboratorio 2 en formato JSON:---");
        mem_info(flag);
        printf("%s\n","---Ejercicio 1.3 del Laboratorio 2: en formato JSON---");
        cpu_info(flag);
    }
    else if(aflag==1 && jflag==0){
        printf("%s\n","---Ejercicio 2 del Laboratorio 2:---");
        version(flag);
    }

    else if(aflag==1 && jflag==1){
        flag=1;
        printf("%s\n","---Ejercicio 2 del Laboratorio 2 en formato JSON:---");
        version(flag);
    }else if(dflag==1){
        printf("%s\n","Filesystems en uso soportados por el Kernel:");
        void* libhandle=dlopen("./dynamic_lib.so",RTLD_LAZY);
        void (*dynamicrun)(void);
        *(void**)(&dynamicrun)=dlsym(libhandle,"filesystems");
        filesystems();
        dlclose(libhandle);
    }

    else{printf("Parámetros invalidos.\n"); return -1;}

   
return 0;
}