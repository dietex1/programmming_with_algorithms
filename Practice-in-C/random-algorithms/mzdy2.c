#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct  kod{
    int count;
    char  name;
    int pocet;
}KOD;


void insert ( KOD ** array , int * index, int * size , char nam ,int cnt)
{
    for ( int i = 0 ; i < (*index) ; i++ )
    {
        if ( nam  == (*array)[i].name)
        {
            (*array)[i].count += cnt;
            (*array)[i].pocet +=1;

            return ;
        }
    }

    if ( index > size )
    {
        (*size) *= 2;
        (*array) = (KOD*)realloc((*array),(*size) * sizeof(KOD));
    }

    (*array)[*index].name = nam;
    (*array)[*index].count = cnt;
    (*array)[*index].pocet =1;
    (*index)++;

}



int main ( void ){

    int  cnt , index = 0 , size =16 ;
    char buffer[84] , znak , nam ;
    KOD * array = (KOD*)malloc(size * sizeof(KOD));

    printf("Zadej:\n");


        if (scanf(" %c", &znak) == 1 && znak == '{')
        {
            while (scanf(" %d %c %c", &cnt, &nam, &znak) == 3)
            {
                insert (&array,&index,&size,nam,cnt);
                if (!isupper(nam) || cnt < 0)
                {
                    free(array);
                    return 1;
                }
                if ( znak == '}')
                    break;
            }
        }




    while (  scanf(" %82s",buffer) != EOF )
    {
        char usedChar[100]= {0};
        int r = 0;
        double res = 0 , kek = 0;
        for (int i = 0; i < strlen(buffer); i++)
        {
            if ( usedChar[r] != buffer[i])
            {
                if (buffer[i] == array[i].name) {
                    res += array[i].count;
                    kek += array[i].pocet;
                    usedChar[r++] = buffer[i];
                }
            }
            else
                i++;
        }
        if ( res == 0 && kek == 0)
            printf("= N/A\n");
        else
            printf(" = %f\n",res / kek);

    }

    free(array);
    return 0;
}
		
