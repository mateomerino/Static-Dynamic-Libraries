#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    char *args1[]={"./1.1",NULL};
    char *args2[]={"./1.2",NULL};
    char *s="-s";
    char *a="-a";

    for(int i=0;i<argc;i++){
        printf("%s%d%s\n","Argumentos: ",i,argv[i]);
    }

    if(strcmp(argv[1],a)){
        printf("%s\n","Se ejecuto con -s ");
        execv(args1[0],args1);
    }

    if(strcmp(argv[1],s)){
        printf("%s\n","Se ejecuto con -a");
        execv(args2[0],args2);
    }

    //int a=strlen(argv[1]);
    //printf("%d",a);
return 0;
}