#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

typedef struct TNode {
    struct TNode * m_Next;
    char m_Value;
}TNODE;


TNODE * create_element(char value, TNODE * next)
{
    TNODE * n = (TNODE *) malloc(sizeof(*n));
    n -> m_Value = value;
    n -> m_Next = next;
    return n;
}

char convert_number_to_char (int x)
{
    switch (x){
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'a';
        case 11:
            return 'b';
        case 12:
            return 'c';
        case 13:
            return 'd';
        case 14:
            return 'e';
        case 15:
            return 'f';
        default:
            return '\0';

    }
}

int convert_char_to_number(char x)
{
    if (isupper(x))
        return -1;
    if (!isupper(x))
    {
        x = toupper(x) ;
    }

    int ten = x - '0';

    switch (ten){
        case 0:
            return 0x0;
        case 1: 
            return 0x1;
        case 2: 
            return 0x2;
        case 3: 
            return 0x3;
        case 4: 
            return 0x4;
        case 5: 
            return 0x5;
        case 6: 
            return 0x6;
        case 7: 
            return 0x7;
        case 8: 
            return 0x8;
        case 9: 
            return 0x9;
        case 17: 
            return 0xa;
        case 18: 
            return 0xb;
        case 19: 
            return 0xc;
        case 20: 
            return 0xd;
        case 21: 
            return 0xe;
        case 22: 
            return 0xf;
        default:
            return -1;
    }
}

TNODE * shiftLeft (TNODE * start, unsigned int shift)
{
    TNODE * res = start;
    if (!start)
        return NULL; 
    int integer = 0;
    int for_next_adding = 0;
    int i = 0;
    TNODE * prev = NULL; // for adding additional elements
    TNODE * tmp; 

    // checking 
    for (tmp = start; tmp; tmp = tmp -> m_Next){
        if ( convert_char_to_number(tmp->m_Value) == -1)
            return NULL;
    }

    for ( tmp = start; tmp; 
        tmp = tmp->m_Next,i++)
    {
        
        integer = convert_char_to_number(tmp->m_Value);
       
        // сдвигаем его
        // записываем сколько нам надо пренести
        // для этого делим на 16, так как мы в 16-ти ричной системе 
        // исчисления  и прибавляем эту цифру к следующему 
        integer = integer << shift; 
        integer += for_next_adding;
        for_next_adding = integer / 16;
        tmp -> m_Value =  convert_number_to_char (integer % 16);
        
        prev = tmp;

    }

    while( tmp  == NULL && for_next_adding != 0)
    {
            i++;
            integer = for_next_adding;
            for_next_adding /= 16 ;
            TNODE * n = (TNODE *) malloc (sizeof(TNODE));
            n -> m_Value = convert_number_to_char (integer % 16);   
            n -> m_Next = NULL;
            prev -> m_Next = n; 
            prev = n;
    }

    return res ;
}

void reverse_list (TNODE ** root)
{
    TNODE * prev = NULL;
    TNODE * next = NULL;
    if (!(*root) || !(*root)->m_Next)
        return;

    for (TNODE * tmp = *root; tmp; tmp = next)
    {
            if ( tmp -> m_Next == NULL)
                *root = tmp;
            next = tmp -> m_Next; 
            tmp -> m_Next = prev; 
            prev = tmp;

    }
}

void show_list(TNODE * start)
{
    //reverse_list(&start);

    printf("LIST:\n");
    for (TNODE * tmp = start; tmp; tmp = tmp ->m_Next)
    {
        printf("%c ", tmp->m_Value);
    }
    printf("\n");

    //reverse_list(&start);

}

void delete_list (TNODE * root)
{
    if (!root)
        return;

    TNODE * tmp;

    while (root)
    {
        tmp = root;
        root  = root -> m_Next;
        free(tmp);
    }

}


int main()
{
    TNODE * list = create_element('1',
                    create_element('1',
                    create_element('1',
                    NULL)));
    show_list(list);
    shiftLeft(list,3);
    show_list(list);    
    delete_list (list);

    return 0;
}