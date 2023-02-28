#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct kod{
    int count;
    char * name;
}KOD;


void insert ( KOD ** array , int * index , int * size, char * buffer , int cnt)
{

  if ( index > size )
  {
      (*size) *= 2;
      (*array) = (KOD*)realloc((*array),(*size)*sizeof(KOD));
  }

  (*array)[*index].name = (char*)malloc(sizeof(char)* (strlen(buffer) + 1));
  strcpy((*array)[*index].name,buffer);
  (*array)[*index].count += cnt;
  (*index)++;

}

void KILL ( KOD * array , int index)
{
    for ( int i = 0 ; i < index ; i++)
        free(array[i].name);
    free(array);
}

int  minus ( KOD ** array , int index , char * buffer ,  int * x )
{
    for ( int i = 0 ; i < index ; i++)
    {
        if ( strcmp((*array)[i].name,buffer) == 0)
        {
            (*x) += ( *array)[i].count ;
            return 1;
        }
    }


    return 0;
}




int main ( void ){

    int index = 0 , size = 16 , res ,  cnt ,allin ;
    char buffer[106] ,*line = NULL;
    size_t len = 0;
    KOD * array = (KOD*)malloc(size*sizeof(KOD));
    printf("Cenik:\n");

    while ( getline(&line,&len,stdin) != 1)
    {
       if ( sscanf(line," %102s => %d",buffer,&cnt) != 2 || cnt < 0 || strlen(buffer)>100 || strlen(buffer) < 5)
       {
           printf("Nespravny vstup.\n");
           KILL(array,index);
           return 1;
       }
        for ( int i = 0 ; i < strlen(buffer) ; i++)
        {
            if (!isdigit(buffer[i]))
            {
                printf("Nespravny vstup.\n");
                KILL(array, index);
                return 1;
            }
        }

       insert(&array,&index,&size,buffer,cnt);


    }

    while ( !feof(stdin))
    {
        printf("Ucet:\n");
        allin = 0;
        while ( getline (&line,&len,stdin) != 1)
        {
            res = sscanf(line," %102s", buffer);
            if (res != 1 || strlen(buffer) > 100 || strlen(buffer) < 5)
            {
                printf("Nespravny vstup.\n");
                KILL(array, index);
                return 1;
            }

            for ( int i = 0 ; i < strlen(buffer) ; i++)
            {
                if (!isdigit(buffer[i]))
                {
                    printf("Nespravny vstup.\n");
                    KILL(array, index);
                    return 1;
                }
            }

            if (!minus(&array, index, buffer,  &allin))
            {
                printf("Nespravny vstup.\n");
                KILL(array, index);
                return 1;
            }
        }

        printf("CELKEM: %d\n",allin);
       // allin = 0;

    }

    KILL(array,index);

    return 0;
}



