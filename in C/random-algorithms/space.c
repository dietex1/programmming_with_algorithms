#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Product{
    int count;
    char * name;
}KOD;

void insert( KOD ** array , int * index, int * size , char * buffer)
{

    for ( int i = 0 ; i < (*index) ; i++)
        if ( strcmp((*array)[i].name , buffer) == 0)
        {
            (*array)[i].count +=1;
            return;
        }

    if ( index > size)
    {
        (*size)*=2;
        (*array) = (KOD*)realloc((*array),(*size) * sizeof(KOD));
    }

    (*array)[*index].name = (char *)malloc(sizeof(char) * strlen ( buffer)+1);
    strcpy((*array)[*index].name,buffer);
    (*array)[*index].count = 1;
    (*index)++;

}


void invent (KOD ** array , int  * index , char * buffer)
{

    for ( int i = 0 ; i < (*index) ; i++)
       if ( strcmp((*array)[i].name, buffer) == 0)
       {
           (*array)[i].count -=1;
           return;
       }

    (*array)[*index].name = ( char *)malloc(sizeof(char) * strlen(buffer)+1);
    strcpy((*array)[*index].name , buffer);
    (*array)[*index].count = -1;
    (*index)++;
}

void KILL ( KOD * array , int index)
{
    for ( int i = 0 ; i < index ; i ++)
        free(array[i].name);
    free(array);
}

int main (void){
    char buffer[106];
    int  index= 0, size = 16 , nr=0;
    printf("Sklad:\n");
    size_t len = 0;
    char * line = NULL;

    KOD * array = (KOD*)malloc(size*sizeof(KOD));

    while((nr = getline(&line , &len , stdin)) != 1 )
    {
        if( nr == EOF )
        {
            KILL(array,index);
            return 0;
        }

        if ( sscanf(line," %101s",buffer) !=1 || strlen(buffer) < 5 || strlen(buffer) > 100)
       {
           printf("CHYBAAA\n");
           KILL (array , index);
           return 1;
       }
        
        for ( int i = 0 ; i < strlen(buffer) ; i++) 
        {
            if (isalpha(buffer[i])) {
                printf("CHYBAAA\n");
                KILL(array, index);
                return 1;
            }
        }
        
        
        insert(&array,&index,&size,buffer);
        
    }
    printf("Inventura:\n");

    int sc ;
    while ( (sc = scanf(" %101s", buffer)) != EOF ) {

        if (sc != 1 || strlen(buffer) < 5 || strlen(buffer) > 100) {
            printf("CHYBAAA\n");
            KILL(array, index);
            return 1;
        }

        for ( int i = 0 ; i < strlen(buffer) ; i++)
        {
            if (isalpha(buffer[i])) {
                printf("CHYBAAA\n");
                KILL(array, index);
                return 1;
            }
        }

        invent(&array, &index, buffer);

    }
        int pocet = 0;
        printf("Chybi:\n");
        for (int i = 0; i < index; i++)
            if (array[i].count < 0) {
                printf("%s: %dx\n", array[i].name, -(array[i].count));
                pocet += array[i].count;
            }
        printf("Celkem: %d", -pocet);

    KILL (array , index);
    return 0;
}

