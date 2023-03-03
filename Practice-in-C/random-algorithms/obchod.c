#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct ean {
    char *name;
    int cena;
}EAN;


void insert ( EAN ** array , int * index , int * size , char * buffer , int cena)
{

    if ( index > size )
    {
        (*size) *= 2;
        (*array) = (EAN*)realloc((*array),(*size) * sizeof(EAN));
    }

    (*array)[*index].name = (char *)malloc(sizeof(char) * (strlen(buffer)+1));
    strcpy((*array)[*index].name,buffer);
    (*array)[*index].cena = cena;
    (*index)++;

}


int ucet ( EAN ** array , int index , char * buffer , int * result)
{

    for ( int i = 0 ; i < index ; i++)
    {
        if ( strcmp((*array)[i].name,buffer) == 0)
        {
            (*result) += (*array)[i].cena;
            return 0;
        }
    }
    return 1;
}


/*
 12345 => 10
11111 => 5
22222 => 300

 12345
12345
12345
11111
12345
12345

 */



void KILL ( EAN * array , int index)
{
    for ( int i = 0 ; i < index ; i++)
        free(array[i].name);
    free(array);
}


int main ( void ){

    int index = 0 , size = 16 , cena ,res ;
    char buffer[106] ,* line = NULL ;
    printf("Cenik:\n");
    size_t  len = 0;
    EAN * array = (EAN*)malloc(size * sizeof(EAN));

    while ( getline(&line,&len,stdin) != 1)
    {
        if ( sscanf(line," %102s => %d",buffer,&cena) != 2 || cena <= 0 || strlen(buffer) > 100 || strlen(buffer) < 5)
        {
            printf("Nespravny vstup.\n");
            KILL(array,index);
            return 1;
        }

        insert(&array,&index,&size,buffer,cena);

    }

    while ( !feof(stdin ))
    {
        printf("Ucet:\n");
        int result = 0;
        while ((res = getline(&line, &len, stdin)) != 1 && res != EOF)
        {
            if ( sscanf(line," %102s",buffer) != 1  || strlen(buffer) > 100 || strlen(buffer) < 5)
            {
                printf("Nespravny vstup.\n");
                KILL(array,index);
                return 1;
            }
            if (ucet(&array, index, buffer , &result) == 1) {
                printf("Nespravny vstup.\n");
                KILL(array, index);
                return 1;
            }

        }
        printf("Celkem: %d\n",result);

    }

    KILL(array,index);
    return 0;
}



