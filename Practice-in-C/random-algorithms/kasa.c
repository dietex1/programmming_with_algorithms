#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef struct kod{
    int count ;
    char * name;
}KOD;


void insert ( KOD** array , int * index, int * size, char * buffer)
{

    for ( int i = 0 ; i < (*index) ; i++)
    {
        if ( strcmp((*array)[i].name,buffer) == 0)
        {
            (*array)[i].count +=1;
            return;
        }
    }

    if ( (*index) >= (*size) )
    {
        (*size) *= 2;
        (*array) = (KOD*)realloc((*array),(*size)*sizeof(KOD));
    }

    (*array)[*index].name = (char*)malloc(sizeof(char)*(strlen(buffer) +3));
    strcpy((*array)[*index].name,buffer);
    (*array)[*index].count = 1;
    (*index)++;
}


void invent ( KOD ** array , int * index, int * size, char * buffer)
{
    for ( int i = 0 ; i < (*index) ; i ++)
    {
        if ( strcmp((*array)[i].name,buffer) == 0)
        {
            (*array)[i].count -=1;
            return;
        }
    }

    if ((*index) >= (*size))
    {
        (*size) *= 2;
        (*array)= (KOD*)realloc((*array),(*size)*sizeof(KOD));
    }

    (*array)[*index].name = (char*)malloc(sizeof(char*)*(strlen(buffer)+3));
    strcpy((*array)[*index].name,buffer);
    (*array)[*index].count = -1;
    (*index)++;

}

void kil ( KOD * array , int index)
{
    for ( int i = 0 ; i < index; i++)
        free(array[i].name);
    free(array);
}

int main ( void ){

    int index = 0 , size  = 16 ,res ;
    char * Line = NULL , buffer[104];
    size_t len;

    printf("Sklad:\n");
    KOD * array = (KOD*)malloc(size*sizeof(KOD));
    while ( getline(&Line,&len,stdin) != 1)
    {
        if ( sscanf(Line," %102s",buffer) != 1 || strlen(buffer) > 100 || strlen(buffer) < 5)
        {
            printf("Nespravny vstup.\n");
            kil(array,index);
            return 1;
        }
        insert(&array,&index,&size,buffer);
    }

    printf("Inventura:\n");
    while ( ( res =  scanf(" %102s",buffer)) != EOF)
    {
        if ( res != 1 || strlen(buffer) > 100 || strlen(buffer) < 5)
        {
            printf("Nespravny vstup.\n");
            kil(array,index);
            return 1;
        }
        invent(&array,&index,&size,buffer);
    }
    int pocet = 0;
    printf("Chybi:\n");
    for ( int i = 0 ; i < index; i++)
    {
        if ( array[i].count < 0) {
            printf("%s: %d x\n", array[i].name, (-array[i].count));
            pocet += array[i].count;
        }
    }
    printf("Celkem: %d\n",-pocet);


    kil(array,index);
    return 0;
}



