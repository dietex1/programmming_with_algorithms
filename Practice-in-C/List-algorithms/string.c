#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


typedef struct TItem {
    struct TItem * m_Next;
    char *m_Word;
}TITEM;


TITEM * create ( char * buffer ,TITEM * next ) {
    TITEM * new = (TITEM*) malloc ( sizeof(*new) );
    new->m_Word = (char*)malloc(strlen(buffer)+3);
    strcpy(new->m_Word,buffer);
    new->m_Next = next;
    return new;
}


TITEM* StringToList( const char* string )
{
    TITEM * res = NULL;
    TITEM * head = res;
    TITEM * tail = NULL;

    size_t size = strlen(string);

    for ( int i = 0; i < size ; i++)
    {
        int q = 0;
        char * buffer = (char *)calloc((size/2) ,sizeof(char));

        while (isspace(string[i]) && i != size)
            i++;
        while ( !isspace(string[i]) &&  i != size  )
        {
            buffer[q++]= string[i];
            i++;
        }
        res = create(buffer,NULL);
        if ( head == NULL)
        {
            head =res;
            head ->m_Next = NULL;
            tail = res;
            tail ->m_Next = NULL;
        }
        else
        {
            tail ->m_Next = res;
            tail = tail->m_Next;
        }
        free(buffer);
    }
    return head;

}

void FreeList ( TITEM* List )
{
    while ( List)
    {
        TITEM * tmp = List ->m_Next;
        free(List->m_Word);
        free(List);
        List = tmp;
    }
}




int main (void) {
    char input[] = "Welcome     \n TO   \t HELL";
    TITEM *a;
    a = StringToList(input);
    while (a) {
        printf("%s ", a->m_Word);
        a = a->m_Next;
    }
    printf("\n");
    FreeList(a);
    char input2[] = "";
    a = StringToList(input2);
    while (a) {
        printf("%s ", a->m_Word);
        a = a->m_Next;
    }
    FreeList(a);
    char input3[] = "   ";
    a = StringToList(input3);
    while (a) {
        printf("%s ", a->m_Word);
        a = a->m_Next;
    }
    char input4[] = " ho ho hoo o ooo o  ";
    a = StringToList(input4);
    while (a) {
        printf("%s ", a->m_Word);
        a = a->m_Next;
    }
    printf("\n");
    FreeList(a);
    char input5[] = "  Good luck u zkousek      :D ";
    a = StringToList(input5);
    while (a) {
        printf("%s ", a->m_Word);
        a = a->m_Next;
    }
    printf("\n");
    FreeList(a);
    char input6[] = "1\t2\n3 4 \n \n 5 \t 6";
    a = StringToList(input6);
    while (a) {
        printf("%s ", a->m_Word);
        a = a->m_Next;
    }
    printf("\n");
    FreeList(a);


}




