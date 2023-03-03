#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

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


void print(TITEM * x)
{
    TITEM * cur = x;
    while ( cur )
    {
        printf(" %c",cur->m_Digit);
        cur=cur->m_Next;
    }
}


int numb ( char n)
{
    return n - '0';
}

int check ( TITEM * x)
{
    int cnt=0;
    if ( x == NULL)
        return 0;

    while ( x )
    {
        if ( numb(x->m_Digit) < 0 ||   numb(x->m_Digit) > 9 )
            return 0;
        if ( x->m_Next == NULL && numb(x->m_Digit) == 0  )
            return 0;
        x = x->m_Next;
        cnt++;
    }
    return cnt;
}

TITEM * addList ( TITEM * a,TITEM * b )
{
    TITEM * headA = a;
    TITEM * headB = b;
    if (check(headA) == 0)
        return NULL;
    if (check(headB) == 0)
        return NULL;

    headA = a;
    headB = b;
    int count = 0;
    if (check(headA) > check(headB))
        count = check(headA);
    else
        count = check(headB);
    headA = a;
    headB = b;

    int digA = 0; //Will keep track of the int value of the digit that a current element holds
    int digB = 0;

    TITEM * res = NULL;
    TITEM * head = res;
    TITEM * tail = NULL;


    int remainder = 0;
    int sum;

    for ( int i = 0 ; i < count + remainder ; i++)
    {

        if ( headA && headB )
        {
            digA = numb(headA->m_Digit);
            digB = numb(headB->m_Digit);
        }
        else if ( headA && !headB)
        {
            digA = numb(headA->m_Digit);
            digB = 0;
        }
        else if ( !headA && headB)
        {
            digB = numb(headB->m_Digit);
            digA = 0;
        }
        else
            digA = digB = 0;

        sum = digA + digB + remainder;

        if ( sum > 9)
        {
            sum = (sum %10 ) + '0';
            res = createItem(sum,NULL);
            remainder = 1;
        }
        else
        {
            res = createItem(sum+'0',NULL);
            remainder = 0;
        }


        if ( head == NULL )
        {
            head = res;
            head->m_Next = NULL;
            tail = res;
            tail ->m_Next = NULL;
        }
        else
        {
            tail->m_Next = res;
            tail = tail->m_Next;
        }


        if ( headA != NULL)
            headA=headA->m_Next;
        if ( headB != NULL)
            headB= headB->m_Next;

    }

    return head;
}



int main(int argc, char *argv[]) {
    TITEM * a, * b, * res;

    a = createItem('9', NULL);
    b = createItem('3', NULL);
    res = addList(a, b);
    print(res);
    printf("\n");

    assert (res->m_Digit == '2');
    assert (res->m_Next->m_Digit == '1');
    deleteList(a);
    deleteList(b);

    a = createItem('5',
                   createItem('0',
                              createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    print(res);
    printf("\n");
    assert (res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('2', createItem('3', createItem('3', NULL)));
    b = createItem('5', createItem('3', createItem('1', NULL)));
    res = addList(a, b);
    print(res);
    printf("\n");
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
    print(res);
    printf("\n");
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);
    return 0;
}
