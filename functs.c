#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

char* cutarray(char a[],char* arr){

    arr=strchr(a,' ');
    arr=strtok(arr," ");
    return arr;
}

int arraytoint(char* a){
    int mb=0;
    mb=atoi(a);
    return mb/1024;
}

void cpu_info(int flag){

    FILE *p;
    
    p=fopen("/proc/cpuinfo","r");
    char aux[200];
    char *modelname;
    char model_name[50];
    char *cpucores;
    char *siblings;
    int i=0;
    int j=0;
    int k=0;
    

    while(feof(p)==0)
    {

    if(i==1 && j==1 && k==1){break;}

        if(fgets(aux,200,p))
        {
            if(strncmp(aux,"model name",10)==0)
            {
                modelname=strchr(aux,':');
                //printf("%s%s","Modelo del procesador",modelname);
                i=1;
            }else if(strncmp(aux,"cpu cores",9)==0)
            {
                cpucores=strchr(aux,':');
                //printf("%s%s","Cantidad de cores del CPU",cpucores);
                j=1;
            }else if(strncmp(aux,"siblings",8)==0){
                siblings=strchr(aux,':');
                //printf("%s%s","Hilos por CPU",siblings);
                k=1;
            }
        }
    }
    
    if(flag==0){
        printf("%s%s","Modelo del procesador",modelname);
        printf("%s%s","Cantidad de cores del CPU",cpucores);
        printf("%s%s","Hilos por CPU",siblings);
    }
    else{
        cJSON* object= cJSON_CreateObject();
        cJSON_AddStringToObject(object,"Modelo del procesador:",modelname);
        cJSON_AddStringToObject(object,"Cantidad de cores del CPU:",cpucores);
        cJSON_AddStringToObject(object,"Hilos por CPU:",modelname);
        char* string=cJSON_Print(object);
        printf("%s",string);
        cJSON_Delete(object);
    }

    fclose(p);      
}

void mem_info(int flag){

    FILE *p;
    p=fopen("/proc/meminfo","r");
    int i=0;
    int cmp1;
    int cmp2;
    char aux[50];
    char aux2[50];
    char swaptotal[50];
    char swapfree[50];
    char* string1="SwapTotal";
    char* string2="SwapFree";
    char* totalfinal;
    char* freefinal;
    int totalmb;
    int freemb;

    while(feof(p)==0){
        if(fgets(aux,50,p)){
        strcpy(aux2,aux);
        strtok(aux,":");
        cmp1=strcmp(string1,aux);
        cmp2=strcmp(string2,aux);
        if(cmp1==0){strcpy(swaptotal,aux2);}
        else if (cmp2==0){
            strcpy(swapfree,aux2);
            break;
                        }
        else continue;
        }
    }

    fclose(p);
    //printf("%s\n",swaptotal);
    //printf("%s\n",swapfree);

    totalfinal=cutarray(swaptotal,totalfinal);
    freefinal=cutarray(swapfree,freefinal);

    totalmb=arraytoint(totalfinal);
    freemb=arraytoint(freefinal);

    if(flag==0){
        printf("%s%s\n","La memoria Swap Total es: ",totalfinal);
        printf("%s%s\n","La memoria Swap Free es: ",freefinal);
        printf("%s""%d\n","La memoria Swap ocupada en MB es: ", totalmb-freemb);
    }else{
        cJSON* object= cJSON_CreateObject();
        cJSON_AddNumberToObject(object,"La memoria Swap Total es:",totalmb);
        cJSON_AddNumberToObject(object,"La memoria Swap Free es:",freemb);
        cJSON_AddNumberToObject(object,"La memoria Swap Ocupada es:",totalmb-freemb);
        char* string = cJSON_Print(object);
        printf("%s",string);
        cJSON_Delete(object);
    }
    


}

void memory_specs(int flag){

    FILE *p;
    p=fopen("/proc/meminfo","r");
    char* totalfinal=" ";
    char* freefinal=" ";
    char* availablefinal=" ";
    char aux[70];
    char totalaux[70];
    char freeaux[70];
    char availableaux[70];
    int i=0;
    int totalmb,freemb,availablemb;

    if(p==NULL){
        perror("Error en la apertura del archivo");
    }

/*
La siguiente porción de código (lineas 27-35) lo que hacen es leer el archivo y copiar las primeras tres líneas
necesarias en arreglos auxiliares. Una vez que se obtienen dichas líneas se cierra el archivo porque ya no se necesita maś.
*/
    while(feof(p)==0){
        i++;
        if(i==1){if(fgets(aux,70,p)){strcpy(totalaux,aux); continue;}}
        else if(i==2){if(fgets(aux,70,p)){strcpy(freeaux,aux);continue;}}
        else if(i==3){if(fgets(aux,70,p)){strcpy(availableaux,aux);continue;}}
        else break;
        
    }
    
    fclose(p);

//Prints de como quedan los arreglos con las lineas que nos interesan    
    //printf("%s",totalaux);
    //printf("%s",freeaux);
    //printf("%s",availableaux);


    totalfinal=cutarray(totalaux,totalfinal);
    totalmb=arraytoint(totalfinal);

    freefinal=cutarray(freeaux,freefinal);
    freemb=arraytoint(freefinal);

    availablefinal=cutarray(availableaux,availablefinal);
    availablemb=arraytoint(availablefinal);
    
    if(flag==0){
        printf("La memoria total en MB es:%d\n",totalmb);
        printf("La memoria libre en MB es:%d\n",freemb);
        printf("La memoria disponible en MB es:%d\n",availablemb);
    }
    else{
        cJSON* object= cJSON_CreateObject(); 
        cJSON_AddNumberToObject(object,"memTotal: ",totalmb);
        cJSON_AddNumberToObject(object,"memFree: ",freemb);
        cJSON_AddNumberToObject(object,"memAvailable: ",availablemb);
        char* string = cJSON_Print(object);
        printf("%s",string);
        cJSON_Delete(object);
    }
    

}

void version(int flag){

    FILE *p;
    p=fopen("/proc/version","r");
    char *token;
    char *upper;
    char **version;
    char aux[200];
    int len,len2;
    int i=0;
    cJSON* object= cJSON_CreateObject();
    
    //Obtengo el contenido de /proc/version y lo guardo en aux
    fgets(aux,200,p);
    //printf("%s\n",aux);
    //Hago strtok para quedarme con el primer string y con eso aloco memoria
    token=strtok(aux," ");
    len=sizeof(token);
    version=(char**)calloc(len,sizeof(char*));
    //El primer elemento de mi vector es el primer string
    version[i]=token;

    //Sigo obteniendo el resto de los strings, a partir de eso voy realocando memoria y almacenando el string en el array dinamico
    while(token!=NULL){
        i++;
        token=strtok(NULL," ");
        version=(char**)realloc(version,sizeof(char*)*i+1);
        version[i]=token;
    }
 
    //En el primer for guardo los strings en un puntero auxiliar, y en el for interior voy convirtiendo cada char en mayuscula
    for(int j=0;j<i;j++){
        upper=version[j];
        for(int k=0;k<sizeof(upper);k++){
            upper[k]=toupper(upper[k]);
            
            if(flag==0){printf("%c",upper[k]);}
        }
        if(flag==1){cJSON_AddStringToObject(object,"/proc/version: ",upper);}
    }

    if(flag==1){
        char* string=cJSON_Print(object);
        printf("%s",string);
        cJSON_Delete(object);
    }

free(version);
fclose(p);
}