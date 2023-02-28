#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef struct Titem{
    struct Titem* next;
    char* word;
}TITEM;


TITEM * create ( char * word  ,TITEM * next)
{
    TITEM * new = (TITEM *)malloc(sizeof(TITEM));
    size_t len = strlen(word);
    new->word = (char*)calloc((len+2),sizeof(char));
    strcpy(new->word,word);
    new->next = next;
    return new;
}


TITEM* StringToList( const char* string )
{
    TITEM * res = NULL;
    TITEM* head = res;
    TITEM * tail = NULL;

    size_t len = strlen(string);

    for ( int i = 0 ; i < len ; i++)
    {
        while (isspace(string[i]) && i != len)
        {
            i++;
        }
        int q = 0;
        char * buffer = (char*)calloc((len+3),(sizeof(char)+3));
        while (!isspace(string[i]) && i != len)
        {
            buffer[q++]=string[i];
            i++;
        }
        res = create(buffer,NULL);
        if ( head == NULL)
        {
            head = res;
            head ->next = NULL;
            tail = res;
            tail->next = NULL;
        }
        else
        {
            tail ->next = res;
            tail = tail->next;
        }
        free(buffer);
    }
    return head;
}




void FreeList ( TITEM* List )
{
    while (List)
    {
        TITEM * tmp =List->next;
        free(List->word);
        free(List);
        List = tmp;
    }
}

int main (void){
    char input[] = "Welcome     \n TO   \t HELL";
    TITEM*a;
    a = StringToList(input);
    while(a){
        printf("%s ",a -> word);
        a = a -> next;
    }
    printf("\n");
    FreeList(a);
    char input2[] = "";
    a = StringToList(input2);
    while(a){
        printf("%s ",a -> word);
        a = a -> next;
    }
    FreeList(a);
    char input3[] = "   ";
    a = StringToList(input3);
    while(a){
        printf("%s ",a -> word);
        a = a -> next;
    }
    FreeList(a);
    char input4[] = " ho ho hoo000sf00sd0fsd0sdfsdjfdjshdfhsdffdsjhfsdhjsdfhjsfdhjfshjsfdhjhjdsfhsfdhjsfdhjsfdhdsdfhsdfhfjdshsfdshjhjsdhfdshsdfhfsdjhsdfjhsfdhfdshjdhsfhjsfdhjsdfhjsdf"
                    "sjfdkkjsfdjkfsdjksdfdfsjfsdkjdsfjkdsfjdfjsdsfj"
                    "dsfdsf"
                    "dsfsdf"
                    "sd"
                    "fsd"
                    "f"
                    "d"
                    "f"
                    "fd"
                    "fd"
                    "f"
                    "d"
                    "fd"
                    "f"
                    "d"
                    "f"
                    "df"
                    "d"
                    "f"
                    "dfd"
                    "fsfhjsfdhfsdhjsdfhjfsdhjfhj o ooo o  ";
    a = StringToList(input4);
    while(a){
        printf("%s ",a -> word);
        a = a -> next;
    }
    printf("\n");
    FreeList(a);
    char input5[] = "  Good luck u zkousek      :D ";
    a = StringToList(input5);
    while(a){
        printf("%s ",a -> word);
        a = a -> next;
    }
    printf("\n");
    FreeList(a);
    char input6[] = "1\t2\n3 4 \n \n 5 \t 6";
    a = StringToList(input6);
    while(a){
        printf("%s ",a -> word);
        a = a -> next;
    }
    printf("\n");
    FreeList(a);
}



