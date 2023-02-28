#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct kod{
    int count;
    char * name;
}KOD;

void insert ( KOD ** array , int * index , int * size , char * buffer , int cnt)
{

    for ( int i = 0 ; i < (*index) ; i++)
    {
        if (strcmp((*array)[i].name, buffer) == 0)
        {
            (*array)[i].count += cnt;
            printf("Pridano.\n");
            return;
        }
    }

    if ( index > size)
    {
        (*size) *= 2;
        (*array)= (KOD*)realloc((*array),(*size) * sizeof(KOD));
    }

    (*array)[*index].name = (char*)malloc(sizeof(char) * strlen(buffer)+1);
    strcpy((*array)[*index].name , buffer);
    (*array)[*index].count =cnt;
    printf("Vytvoreno.\n");
    (*index)++;

}

void minus ( KOD** array , int * index , char * buffer , int cnt )
{

    for ( int i = 0 ; i < (*index) ; i++) {
        if (strcmp((*array)[i].name, buffer) == 0)
        {
            if ( (*array)[i].count >= cnt )
            {
                (*array)[i].count -= cnt;
                printf("Odebrano\n");
                return;
            }
            else {
                printf("Nedostatek zbozi.\n");
                return;
            }
        }
    }
    printf("Nedostatek zbozi.\n");
}

void kolik ( KOD ** array , int  index , char * buffer)
{
    for ( int i = 0 ; i < index ; i++)
        if ( strcmp((*array)[i].name , buffer) == 0)
        {
            printf("Kusu: %d.\n",(*array)[i].count);
            return;
        }
    printf("Kusu: 0.\n");

}

int compare ( const void * a , const void * b)
{
    const KOD rec1 = *(KOD*)a;
    const KOD rec2 = *(KOD*)b;

    if ( rec1.count > rec2.count)
        return -1;
    else if ( rec1.count < rec2.count )
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

    int index=0,size =16, cnt ;
    char znak , buffer[106];
    KOD * array = (KOD*)malloc(size*sizeof(KOD));
    int sc ;

    printf("ZADEJ\n");

    while ( (sc = scanf(" %c",&znak)) != EOF )
    {
        if ( sc != 1 || !(znak == '+' || znak == '-' || znak =='?'))
        {
            printf("Nespravny vstup!\n");
            KILL(array,index);
            return 1;
        }

        switch (znak) {

            case '+':

                if (scanf(" %102s %d", buffer, &cnt) != 2 || strlen(buffer) > 100 || cnt < 0) {
                    printf("Nespravny vstup!\n");
                    KILL(array, index);
                    return 1;
                }

                for (int i = 0; i < strlen(buffer); i++)
                    if (!isdigit(buffer[i])) {
                        printf("Nespravny vstup!\n");
                        KILL(array, index);
                        return 1;
                    }

                insert(&array, &index, &size, buffer, cnt);


                break;


            case '-':
                if (scanf(" %102s %d", buffer, &cnt) != 2 || strlen(buffer) > 100 || cnt < 0) {
                    printf("Nespravny vstup!\n");
                    KILL(array, index);
                    return 1;
                }
                for (int i = 0; i < strlen(buffer); i++)
                    if (!isdigit(buffer[i])) {
                        printf("Nespravny vstup!\n");
                        KILL(array, index);
                        return 1;
                    }

                minus(&array, &index, buffer, cnt);

                break;

            case '?':
                if (scanf(" %102s", buffer) != 1 || strlen(buffer) > 100)
                {
                    printf("Nespravny vstup!\n");
                    KILL(array,index);
                    return 1;
                }
                for ( int i = 0 ; i < strlen(buffer) ; i++)
                {
                    if (!isdigit(buffer[i]))
                    {
                        printf("Nespravny vstup!\n");
                        KILL(array, index);
                        return 1;
                    }
                }
                kolik(&array,index,buffer);
                qsort( array , size , sizeof(KOD) , compare);
                for ( int i = 0 ; i < index ; i++)
                    printf("%s %d\n",array[i].name , array[i].count);

                break;
        }



    }
    KILL(array,index);
    return 0;
}


