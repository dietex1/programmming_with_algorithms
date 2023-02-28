#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product {
    char * name;
    int count;
} PRODUCT ;


void InsertD (PRODUCT **  array, int* size ,int * index, char * string)
{

    for ( int i = 0 ; i < *index ; i ++)
    {
        //TODO change to strncmp if segfoult
        if ( ( strcmp((*array)[i].name,string) ) == 0 )
        {
            (*array)[i].count++;
            return ;
        }
    }

    if ( index >=  size)
    {
        (*size) *= 2;
        (*array) = (PRODUCT*)realloc((*array), (*size) * sizeof(PRODUCT));
    }


    (*array)[*index].name = (char*) malloc ( sizeof (char) * strlen (string) +1);
    strcpy((*array)[*index].name , string);
    (*array)[*index].count = 1;
    (*index)++;
}



int compare(const void *tov1, const void *tov2 )
{
    const PRODUCT rec1 = *(PRODUCT*)tov1;
    const PRODUCT rec2 = *(PRODUCT*)tov2;

    //printf("1: %s count %d\n", rec1->name, rec1->count);
    //printf("2: %s count %d\n", rec2->name, rec2->count);

    if (rec1.count > rec2.count ) {
        //printf("res: %d", -1);
        return -1;
    }
    else if (rec1.count < rec2.count ) {
        //printf("res: %d", 1);
        return 1;
    }
    else return 0;
}





void KILLF ( PRODUCT * sieve  , int  index)
{
    for ( int i = 0 ; i < index ; i++)
        if ( sieve[i].name )
            free(sieve[i].name);
    free(sieve);
}

int main() {
    int sled ,pocet = 0 , n = 1;
    char znak ;
    printf("Pocet sledovanych:\n");
    if (scanf (" %d",&sled) !=1 || sled < 1)
    {
        printf("Nespravny vstup!\n");
        return 1;
    }

    printf("Pozadavky:\n");

    PRODUCT * array = NULL;
    int Size = 16;
    int Index = 0;
    char buffer[106];
    array = (PRODUCT*) malloc ( Size * sizeof(PRODUCT));
    int sc;
    int SORTED =1;

    while ((sc = scanf (" %c",&znak))  != EOF) {
        if (sc == 0) {
            printf("Nespravny vstup.\n");
            return 3;
        }
        if ( !(znak == '+' || znak == '?' || znak =='#'))
        {
            printf("Nespravny vstup!\n");
            KILLF(array,Index);
            return 1;
        }

        switch ( znak )
        {
            case '+' :

                scanf(" %101s",buffer);
                if ( strlen((char*)buffer) > 99 )
                {
                    printf("Nespravny vstup!\n");
                    KILLF(array,Index);
                    return 1;
                }
                InsertD(&array, &Size , &Index, buffer);
                pocet++;
                SORTED = 0;

                break;

            case '?' :
                printf("Nejprodavanejsi zbozi: prodano %d kusu",pocet);

                break;

            case '#' :
                if ( !SORTED ) {
                    qsort(array, Size, sizeof(PRODUCT), compare);
                    for (int i = 0; i < sled; i++)
                        printf("%d. %s, %dx\n", i+1, array[i].name, array[i].count);
                    printf("Nejprodavanejsi zbozi: prodano %d kusu", pocet);
                }
                break;


        }



    }
    KILLF(array,Index);
    return 0;
}






