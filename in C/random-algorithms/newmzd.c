#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct kod {
    int cena;
    char name;
    int count;
}KOD;


void insert ( KOD ** array, int * index, int * size , char mesto , int cena)
{


        for (int i = 0; i < (*index); i++) {
            if (mesto == (*array)[i].name) {
                (*array)[i].cena += cena;
                (*array)[i].count += 1;
                return;
            }
        }


    if ((*index) > (*size))
    {
        (*size) *=2;
        (*array) = (KOD*)realloc((*array),(*size)*sizeof(KOD));
    }

    (*array)[*index].name = mesto;
    (*array)[*index].count = 1;
    (*array)[*index].cena  = cena;
    (*index)++;


}


void KILL ( KOD * array , int index)
{
    free(array);
}


int main ( void )
{
    int cena , size=16,index = 0 ;
    char  mesto , znak;
    KOD * array = (KOD*)malloc(size*sizeof(KOD));

    if ( scanf (" %c",&znak) == 1 && znak =='{')
    {
        while (scanf(" %d %c %c",&cena,&mesto,&znak) == 3 && cena > 0  )
        {
            insert(&array,&index,&size,mesto,cena);
            if ( znak  == '}')
                break;
        }
    }

    char buffer[83];
    while ( scanf(" %s",buffer) != EOF)
    {
        char usedChar[100]= {0};
        int r = 0;
        double res = 0 , kek = 0;
        for ( int  j = 0 ; j < index ; j++)
        {
            for ( int i = 0 ; i < strlen(buffer) ; i ++)
            {
                if ( array[j].name == buffer[i])
                if ( usedChar[i] !=  array[j].name)
                {
                    usedChar[r++]=array[j].name;
                    res += array[j].cena;
                    kek += array[j].count;
                    break;
                }
            }
        }

        if ( res == 0 && kek == 0)
            printf("N/A\n");
        else
            printf(" = %f\n",res/kek);
    }
    free(array);
    return 0;
}


