#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct kod{
    int count ;
    char * name;
}KOD;

void insert ( KOD ** array , int * index , int * size , char * buffer )
{

   for ( int i = 0 ; i < (*index) ; i++)
   {
       if ( strcmp((*array)[i].name , buffer) == 0)
       {
           (*array)[i].count +=1;
           return ;
       }
   }

   if ( (*index) >= (*size) )
   {
       (*size) *=2;
       (*array) = (KOD*)realloc((*array),(*size) * sizeof(KOD));
   }

   (*array)[*index].name= (char*)malloc(sizeof(char) * (strlen(buffer) + 3));
   strcpy((*array)[*index].name,buffer);
   (*array)[*index].count = 1;
   (*index)++;



}


int compare ( const void * a , const void * b)
{
    KOD  rec1 = *(KOD*)a;
    KOD rec2 = *(KOD*)b;

    if ( rec1.count > rec2.count )
        return -1;
    else if ( rec1.count < rec2.count)
        return 1;
    return 0;
}

void KILL ( KOD * array , int index)
{
    for ( int i = 0 ; i < index ; i++)
        free(array[i].name);
    free(array);
}


int main ( void ){

    int index = 0 , size = 16  ;
    char  *Line  = NULL;
    size_t lsiz = 0,res;
    KOD * array = (KOD*)malloc(size*sizeof(KOD));

   while ( (res  = getline(&Line,&lsiz,stdin ) ) != EOF)
    {
        size_t ssiz = strlen(Line);
        for ( int i = 0 ; i < ssiz ; i++)
        {
            char buffer[150] = {0};
            int q = 0;

            while( (Line[i] == '\n' || res == EOF)  || !isspace(Line[i]) )
            {
                buffer[q++] = Line[i];
                if ( Line[i] == '\n' )
                    break;
                if ( res == EOF ) {
                    buffer[q] = '\n';
                    break;
                }
                i++;

            }
            if (buffer[strlen(buffer)-1] != '\n' && res != EOF )
            {
                insert(&array,&index,&size,buffer);
            }

            
        }


    }

    qsort(array,size,sizeof(KOD),compare);

    printf("Nejvetsi pocet je : %d\n",array[0].count);

    for ( int i = 0 ; i < index ; i++)
    {
        if ( array[i].count == array[0].count)
        {
            printf(" %s\n",array[i].name);
        }
    }


   KILL(array,index);

    return 0;
}



