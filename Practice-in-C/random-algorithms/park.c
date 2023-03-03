#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct park {
    int day  , minut , inOut;
    char * name;
}PARK;



int timer ( int h , int m )
{
    return ( h * 60) + m;
}


void insert ( PARK ** array , int * index ,int * size , char * buffer , int hour , int minut)
{

    for ( int i = 0 ; i < (*index) ; i++)
    {
        if ( strcmp((*array)[i].name,buffer) == 0)
        {
            if ( (*array)[i].inOut == 1)
            {
                printf("Uz je\n");
                return ;
            }
            else
            {
                (*array)[i].inOut = 1;
                printf("OK\n");
                return ;
            }
        }
    }

    if ( index > size)
    {
        (*size) *= 2;
        (*array)= (PARK*)realloc((*array),(*size) * sizeof(PARK));
    }


    (*array)[*index].name = (char *)malloc ( sizeof(char) * (strlen(buffer) +1));
    strcpy((*array)[*index].name,buffer);
    (*array)[*index].inOut = 1;
    (*array)[*index].minut = timer(hour,minut);
    (*index)++;
    printf("OK\n");

}

int cena (int in,  int out , int day)
{
    int total = day * 1440  + out - in;
    if ( total <= 30) //+day 0
        return 0;
    else if ( total <= 60)
        return 30;
    else if ( total  <= 1440 )
        return (int) ( ceil ( (double) total / 60 ) ) * 40;
    else
        return (int) (ceil ( ( double) total / 1440 ) ) * 1000;
}

void minus ( PARK ** array, int  index,char * buffer, int hour, int minut , int day)
{

    for ( int i = 0 ; i < index ; i++)
    {
        if ( strcmp((*array)[i].name , buffer ) == 0)
        {
            if ((*array)[i].inOut == 1)
            {
                (*array)[i].inOut = 0;
                int res = timer(hour, minut);
                printf("RZ: %s, cena: %d\n", (*array)[i].name, cena((*array)[i].minut, res, (*array)->day));
                return;
            }
            else
            {
                printf("Nenalezeno\n");
                return ;
            }
        }

    }

    printf("Nenalezeno\n");

}


void KILL ( PARK * array , int index )
{
    for ( int i = 0 ; i < index ; i++)
        free(array[i].name);
    free(array);
}


int main ( void ){

    int index = 0 , size = 16 , h,m , res , day = 0;
    char znak , buffer[14] ;
    PARK * array = (PARK*)malloc(size*sizeof(PARK));

    while ( (res = scanf(" %d:%d %c",&h,&m,&znak) ) != EOF  )
    {
        if ( res != 3 || h <  0 || h> 23 || m < 0 || m > 59 || !(znak =='+' || znak == '-' || znak == '=') )
        {
            printf("Nespravny vstup.\n");
            KILL(array, index);
            return 1;
        }

        switch (znak )
        {
            case'+':

                if ( scanf(" %12s",buffer) !=  1 || strlen( buffer ) < 0 || strlen (buffer) > 10)
                {
                    printf("Nespravny vstup.\n");
                    KILL(array, index);
                    return 1;
                }
                insert (&array,&index,&size,buffer,h,m);
                break;


            case '-':
                if ( scanf(" %12s",buffer) !=  1 || strlen( buffer ) < 0 || strlen (buffer) > 10)
                {
                    printf("Nespravny vstup.\n");
                    KILL(array, index);
                    return 1;
                }
                minus(&array,index,buffer,h,m , day);

                break;


            case '=':
                if ( h != 0 || m != 00)
                {
                    printf("Nespravny vstup.\n");
                    KILL(array, index);
                    return 1;
                }
                array->day +=1;
                break;
        }

    }
    int cnt = 0;
    for ( int i = 0 ; i < index ; i++)
    {
        if ( array[i].inOut == 1)
        {
            cnt++;
        }
    }
    printf("Pocet automobilu v garazi: %d\n",cnt);

    KILL(array, index);
    return 0;
}


