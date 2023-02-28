#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>


typedef struct TItem {
    struct TItem * m_Next;
    char m_Digit;
} TITEM;

TITEM * createItem(char digit, TITEM * next) {
    TITEM *n = (TITEM *) malloc(sizeof(*n));
    n->m_Digit = digit;
    n->m_Next = next;
    return n;
}

void deleteList(TITEM * l) {
    while (l) {
        TITEM *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}


int converte ( char n )
{
    return n-'0';
}

int check( TITEM * l)
{
    if ( l == NULL)
        return 0;
    TITEM * tmp = l;
    while ( tmp )
    {
        int num = converte(tmp->m_Digit);
        if ( num < 0 || num > 9)
            return 0;
        if (  tmp->m_Next != NULL )
        {
            if ( tmp->m_Next->m_Digit == '0' && tmp->m_Next ->m_Next == NULL)
                return 0;
        }
        tmp = tmp->m_Next;
    }
    return 1;
}

int siz ( TITEM * l )
{
    TITEM * tmp = l;
    int cnt = 0;
    while ( tmp )
    {
        cnt++;
        tmp = tmp->m_Next;
    }
    return cnt;
}


TITEM * addList ( TITEM * a,TITEM * b )
{

    TITEM * headA = a;
    TITEM * headB = b;

    if (check(a) == 0)
        return NULL;
    if (check(b) == 0)
        return NULL;
    int numA = 0 , numB = 0,remainder = 0;
    TITEM * res = NULL;
    TITEM * head = res;
    TITEM * tail = NULL;
    int cnA = siz(headA);
    int cnB = siz(headB);
    int cnt = 0;

    if ( cnA > cnB)
        cnt = cnA;
    else
        cnt = cnB;

    for ( int i = 0 ; i < cnt + remainder ; i++)
    {
        if (headA && headB) {
            numA = converte(headA->m_Digit);
            numB = converte(headB->m_Digit);
            headA = headA->m_Next;
            headB = headB->m_Next;
        } else if (headA && !headB) {
            numA = converte(headA->m_Digit);
            headA = headA->m_Next;
            numB = 0;

        } else if (!headA && headB) {
            numB = converte(headB->m_Digit);
            headB = headB->m_Next;
            numA = 0;
        }
        else
        {
            numA =numB = 0;
        }


        int sum = numA+numB + remainder;

        if ( sum > 9)
        {
            sum = sum % 10;
            remainder = 1;
            res = createItem((sum + '0'), NULL);
        }
        else if ( sum < 9)
        {
            res = createItem((sum + '0'), NULL);
            remainder = 0;
        }



        if ( head == NULL)
        {
            head = res;
            head ->m_Next = NULL;
            tail = res;
            tail ->m_Next = NULL;
        }
        else
        {
            tail ->m_Next = res;
            tail = tail->m_Next;
        }




    }

    return head;

}






int main(int argc, char *argv[]) {
    TITEM * a, * b, * res;

    a = createItem('x', NULL);
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);


    a = createItem('5',
                   createItem('0',
                              createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('3',
                   createItem('4',
                              createItem('5', NULL)));
    b = createItem('0', NULL);
    res = addList(a, b);
    assert (res->m_Digit == '3');
    assert (res->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Digit == '5');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('2', createItem('3', createItem('3', NULL)));
    b = createItem('5', createItem('3', createItem('1', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('2', createItem('3', createItem('9', NULL)));
    b = createItem('5', createItem('3', createItem('1', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);


    a = createItem('9', createItem('9', createItem('9', NULL)));
    b = createItem('9', createItem('9', createItem('9', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '8');
    assert (res->m_Next->m_Digit == '9');
    assert (res->m_Next->m_Next->m_Digit == '9');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('9', createItem('9', createItem('9', createItem('9', createItem('9', createItem('9', NULL))))));
    b = createItem('9', createItem('9', createItem('9', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '8');
    assert (res->m_Next->m_Digit == '9');
    assert (res->m_Next->m_Next->m_Digit == '9');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    return 0;
}





