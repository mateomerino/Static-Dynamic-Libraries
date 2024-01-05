#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
#include "cJSON.h"

void filesystems(){

    FILE *p;
    p=fopen("/proc/filesystems","r");
    char aux[200];
    char* nodev="nodev";
    char* token;
    int i=0;
    cJSON* object=cJSON_CreateObject();

    while(feof(p)==0){
        fgets(aux,200,p);
        if(strncmp(aux,nodev,5)!=0){
            cJSON_AddStringToObject(object,"Filesystem:",aux); 
        }
    }

    char* string=cJSON_Print(object);
    printf("%s",string);
    cJSON_Delete(object);
    
    fclose(p);

}

