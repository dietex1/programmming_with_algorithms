#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>


typedef struct TNode
{
    struct TNode * m_Next;
    char           m_Digit;
} TNODE;

TNODE * createNode ( char digit, TNODE * next )
{
    TNODE * n = (TNODE *) malloc (sizeof ( *n ));
    n -> m_Digit = digit;
    n -> m_Next = next;
    return n;
}

void deleteList (TNODE * l)
{
    while (l)
    {
        TNODE * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}

// todo
int change ( TNODE * a )
{
    TNODE * head = a;
    int i = 0,j=0;
    double dec = 0;

    while ( head )
    {
        i++;
        head =head->m_Next;
    }
    head = a;
    while ( head )
    {
        int tmp;
        if ( head->m_Digit == '0')
            tmp = 0;
        else if ( head->m_Digit == '1')
            tmp = 1;
        else if ( head->m_Digit == '2')
            tmp = 2;
        else if ( head->m_Digit == '3')
            tmp = 3;
        else if ( head->m_Digit == '4')
            tmp = 4;
        else if ( head->m_Digit == '5')
            tmp = 5;
        else if ( head->m_Digit == '6')
            tmp = 6;
        else if ( head->m_Digit == '7')
            tmp = 7;
        else if ( head->m_Digit == '8')
            tmp = 8;
        else if ( head->m_Digit == '9')
            tmp = 9;
        else if ( head->m_Digit == 'A' || head->m_Digit == 'a')
            tmp = 10;
        else if ( head->m_Digit == 'B' || head->m_Digit == 'b')
            tmp = 11;
        else if ( head->m_Digit == 'C' || head->m_Digit == 'c')
            tmp = 12;
        else if ( head->m_Digit == 'D' || head->m_Digit == 'd')
            tmp = 13;
        else if ( head->m_Digit == 'E' || head->m_Digit == 'e')
            tmp = 14;
        else if ( head->m_Digit == 'F' || head->m_Digit == 'f')
            tmp = 15;
        else
            return -1;

        if ( j < i)
        {
            dec += (tmp + 0.0) * pow(16, (j));
            j++;
        }
        head = head->m_Next;

    }
    int size = (int)dec ;

    return size;
}


int  check ( TNODE * x)
{
    TNODE * head = x;

    while ( head) {
        if ( head ->m_Next != NULL)
        {
            if (head->m_Next->m_Digit == 0)
            {
                if (head->m_Next->m_Next == NULL)
                {
                    return 0;
                }
            }
        }
        head = head->m_Next;
    }
    return 1;

}



TNODE * shiftLeft ( TNODE * a, unsigned int shift )
{
    if ( a == NULL)
        return NULL;

    if(check(a) == 0)
        return NULL;
    if ( change(a) == -1)
        return NULL;
    TNODE * headA = a;
    unsigned int dec = change(headA);
    unsigned int sdec = 0;
    sdec = dec << shift;
    char *strpos = (char*) calloc(10, sizeof(char));
    sprintf(strpos, "%x", sdec);
    int len = strlen(strpos);
    for ( int i = 0 ; i < len ; i++)
        printf(" %c ",strpos[i]);
    printf("\n");
    TNODE * res = NULL;
    TNODE * head = res;
    TNODE * tail = NULL;

    for ( int i = len ; i > 0 ; i--)
    {
        res = createNode(strpos[i-1],NULL);
        if ( head == NULL)
        {
            head = res;
            head ->m_Next = NULL;
            tail = res;
            tail ->m_Next = res;
        }
        else
        {
            tail ->m_Next = res;
            tail = tail->m_Next;
        }
    }
    free(strpos);


    return head;

}







int main (int argc, char * argv []) {
    TNODE *a = NULL, *res = NULL;
     a = createNode('3',
                   createNode('2',
                              createNode('1', NULL)));
    res = shiftLeft(a, 1);
    assert (res->m_Digit == '6');
    assert (res->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Digit == '2');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(a);
    deleteList(res);


    a = createNode('f',
                   createNode('a',
                              createNode('1', NULL)));
    res = shiftLeft(a, 3);
    assert (res->m_Digit == '8');
    assert (res->m_Next->m_Digit == '7');
    assert (res->m_Next->m_Next->m_Digit == 'd');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(a);
    deleteList(res);

    a = createNode('c',
                   createNode('5',
                              createNode('4',
                                         createNode('d',
                                                    createNode('1', NULL)))));
    res = shiftLeft(a, 5);
    assert (res->m_Digit == '0');
    assert (res->m_Next->m_Digit == '8');
    assert (res->m_Next->m_Next->m_Digit == 'b');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '8');
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Digit == 'a');
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '3');
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(a);
    deleteList(res);

    a = createNode('a',
                   createNode('w',
                              createNode('0', NULL)));
    res = shiftLeft(a, 12);
    assert (res == NULL);
    deleteList(a);
    deleteList(res);

    a = NULL;
    res = shiftLeft(a, 1);
    assert (res == NULL);
    deleteList(a);
    deleteList(res);

    a = createNode('0',NULL);
    res = shiftLeft(a,1);

    deleteList(a);
   // deleteList(res);
    return 0;
}




