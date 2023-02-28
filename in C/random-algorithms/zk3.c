#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct Kod {
    int count;
    char *name;
}KOD;


void insert ( KOD ** array , int * index , int * size , char * buffer)
{

    for ( int i = 0 ; i < (*index) ; i++) {
        if (strcmp((*array)[i].name, buffer) == 0) {
            (*array)[i].count += 1;
            return;
        }
    }


    if ( index > size)
    {
        (*size) *= 2;
        (*array) = (KOD*)realloc((*array),(*size)*sizeof(KOD));
    }


    (*array)[*index].name = (char*)malloc(sizeof(char) * (strlen(buffer)+1));
    strcpy((*array)[*index].name,buffer);
    (*array)[*index].count = 1;
    (*index)++;
}

int compare ( const void * a , const void * b)
{
    const KOD rec1 = *(KOD*) a;
    const KOD rec2 = *(KOD*) b;

    if ( rec1.count > rec2.count )
        return -1;
    else if ( rec1.count < rec2.count)
        return 1;
    else
        return 0;
}

void KILL ( KOD * array , int index)
{
    for ( int i = 0 ; i < index ; i ++)
        free(array[i].name);
    free(array);
}


int main() {
    printf("Zadej vstup:\n");
    int index = 0 , size = 16 ;
//    size_t len = 0;
    char *LINE = NULL, buffer[103] , znak ,*last;
    KOD * array = (KOD*)calloc(  size,   sizeof(KOD));



   while ( scanf(" %100s%c ",buffer,&znak) != EOF)
   {
       if ( znak == ' ')
       {
           insert(&array,&index,&size,buffer);
           //last = buffer;
       }
       else if ( znak == '\n')
       {


       }

   }

   qsort(array,size,sizeof(KOD),compare);
   printf("Pocet : %d\n",array[0].count);

   for ( int i = 0 ; i < index ; i++)
   {
       if ( array[i].count == array[0].count )
       {
           printf("%s\n",array[i].name);
       }
   }

    KILL(array,index);
    return 0;
}

