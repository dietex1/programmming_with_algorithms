#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ean{
    char * name;
    int count;
}EAN;


void insert ( EAN ** array , int * index , int * size , char * buffer , int cnt) {

    for (int i = 0; i < (*index); i++)
    {
        if ( (strcmp((*array)[i].name, buffer) ) == 0) //check
        {
            (*array)[i].count += cnt;
            printf("%dx\n",(*array)[i].count);
            return;
        }
    }

    if ( index >= size)
    {
        (*size) *= 2;
        (*array) = (EAN*)realloc((*array) , (*size) * sizeof(EAN));
    }

    (*array)[*index].name = (char*)malloc( sizeof(char) * strlen(buffer)+1);
    strcpy((*array)[*index].name,buffer);
    (*array)[*index].count = 0 + cnt;  // += cnt;
    printf("%dx\n",(*array)[*index].count);
    (*index)++;

}


void min (EAN ** array , int  index , char * buffer, int cnt)
{

    for ( int i = 0 ; i < index ; i++)
    {
        if ( (strcmp ((*array)[i].name,buffer)) == 0)
        {
            if ((*array)[i].count >= cnt)
            {
                (*array)[i].count -= cnt;
                printf("%dx\n",(*array)[i].count);
                return;
            }
            else
            {
                printf("Nedostatocne zasoby\n");
                return;
            }
        }
    }

    printf("Nenalezeno\n");


}

void KILL (EAN * array ,int  index)
{
    for ( int i = 0 ; i < index; i++)
        if ( array[i].name )
            free(array[i].name);
    free(array);
}

int main() {
    int  size = 16,index =0 , cnt , cn;
    char buffer[106] , buf[106], znak ;
    printf("Operace:\n");
    int res;
    EAN * array = NULL;
    array = (EAN*)malloc(size * sizeof(EAN));
    while ( ( res = scanf(" %c",&znak) )  != EOF  )
    {

        if (res == 0) {
            printf("Nespravny vstup.\n");
            return 3;
        }
        if ( !(znak == '+' || znak =='-') )
        {
            printf("Nespravny vstup!\n");
            KILL(array,index);
            return 1;
        }

        switch (znak)
        {
            case '+':
                if (scanf(" %dx %102s",&cnt,buffer) !=2 || strlen((char*)buffer) < 5 || strlen((char*)buffer) > 100 || cnt < 0)
                {
                    printf("Nespravny vstup.\n");
                    KILL(array,index);
                    return 1;
                }

                insert(&array,&index,&size,buffer,cnt);

                break;

            case '-':
                if (scanf(" %dx %102s",&cn,buf) !=2 || strlen((char*)buf) < 5 || strlen((char*)buf) > 100 || cn < 0)
                {
                    printf("Nespravny vstup.\n");
                    KILL(array,index);
                    return 1;
                }
                min(&array,index,buf,cn);
                break;


        }


    }

    KILL(array,index);
    return 0;
}

