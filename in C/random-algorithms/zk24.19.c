#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct car{
    char * name;
    int inout;
    int day, minutes;
}CAR;

int timer ( int hour , int minut)
{
    return hour * 60 + minut;
}

void insert ( CAR ** array , int * index, int * size , char * buffer , int h , int m)
{

    for ( int i = 0 ; i < (*index) ; i++)
    {
        if ( strcmp((*array)[i].name,buffer) == 0)
        {
            if ( (*array)[i].inout == 0)
            {
                (*array)[i].inout = 1;
                printf("OK\n");
                return ;
            }
        }
    }

    if ( size > index)
    {
        (*size) *= 2;
        (*array) = (CAR*)realloc((*array),(*size) * sizeof(CAR));
    }

    (*array)[*index].name = (char*)malloc(sizeof(char) * (strlen(buffer)+1));
    strcpy((*array)[*index].name,buffer);
    (*array)[*index].inout = 1;
    (*array)[*index].minutes = timer(h,m);
    (*index)++;
    printf("OK\n");

}

int cenik ( int arrival , int depart , int days )
{
    int sum = (depart + days * 1440) - arrival;
    if ( sum <= 30 )
        return 0;
    else if ( sum <= 60)
        return 30;
    else if ( sum <= 1440 )
        return  ( (int)ceil((double) sum/60 ) * 40 );
    else if ( sum > 1440 )
        return ( ( int ) ceil ( (double) sum / 1440) * 1000);
    else
        return 1;
}


void odjezd ( CAR ** array , int index, char * buffer , int h , int m)
{

    for ( int i = 0 ; i < index ; i++)
    {
        if ( strcmp ( (*array)[i].name ,buffer) == 0)
        {
            if ( (*array)[i].inout == 1)
            {
                int cas = h*60 + m;
                (*array)[i].inout = 0;
                printf("RZ: %s, cena: %d\n",(*array)[i].name, cenik((*array)[i].minutes,cas,(*array)->day));
                return;
            }
            else
            {
                printf("Nenalezeno\n");
                return;
            }
        }
    }

    printf("Nenalezeno\n");

}


void KILL ( CAR * array , int index)
{
    for ( int i = 0 ; i < index ; i++)
        free(array[i].name);
    free(array);
}

int main ( void ){

    int index = 0 , size = 16, h , m ,h1 =0 ,m1 = 00, res , pocet = 0;
    char buffer[16],znak ;
    CAR * array = (CAR*)malloc(size * sizeof(CAR));
    printf("Log\n");
    while ( ( res = scanf(" %d:%d %c",&h,&m,&znak)) != EOF )
    {
        if ( res != 3 || !(znak == '+' || znak == '-' || znak == '='))
        {
            printf("Nespravny vstup.\n");
            KILL(array,index);
            return 1;
        }

        switch( znak )
        {
            case '+':

                if ( scanf (" %12s",buffer) != 1 || strlen(buffer) < 1 || strlen(buffer) > 10)
                {
                    printf("Nespravny vstup.\n");
                    KILL(array,index);
                    return 1;
                }


                if ( h1 >= h &&  m1 > m )
                {
                    printf("Nespravny vstup.\n");
                    KILL(array,index);
                    return 1;
                }
                h1 = h;
                m1 = m;
                //TODO kontrol 2 cifry v m a musi byt vysse nez poperedna

                insert(&array,&index,&size,buffer,h,m);

                break;


            case '-':

                if ( scanf (" %12s",buffer) != 1 || strlen(buffer) < 1 || strlen(buffer) > 10)
                {
                    printf("Nespravny vstup.\n");
                    KILL(array,index);
                    return 1;
                }

                if ( h1 >= h &&  m1 > m)
                {
                    printf("Nespravny vstup.\n");
                    KILL(array,index);
                    return 1;
                }
                h1 = h;
                m1 = m;

                odjezd(&array,index,buffer,h,m);

                break;


            case '=':
                if ( h != 0 || m != 00)
                {
                    printf("Nespravny vstup.\n");
                    KILL(array,index);
                    return 1;
                }
                array->day ++;
                h1 = 0;
                m1 = 00;
                break;



        }


    }

    for ( int i = 0 ; i < index ; i++)
    {
        if ( array[i].inout == 1)
        {
            pocet++;
        }
    }
    printf("Pocet automobilu v garazi: %d",pocet);
    KILL(array,index);
    return 0;
}




