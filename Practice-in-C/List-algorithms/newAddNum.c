#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>


typedef struct TItem
{
    struct TItem   * m_Next;
    char             m_Digit;
} TITEM;

TITEM * createItem ( char num ,TITEM * next)
{
    TITEM * new = (TITEM*)malloc(sizeof(TITEM));
    new->m_Digit = num;
    new->m_Next = next;
    return new;

}

int numb ( char n)
{
    return n- '0';
}

int check ( TITEM * l)
{
    if ( l == NULL)
        return 0;
    TITEM * tmp = l;

    while ( tmp )
    {
        if ( numb(tmp->m_Digit) < 0 || numb(tmp->m_Digit) > 9)
            return 0;
        if ( tmp ->m_Next != NULL)
        {
            if ( tmp->m_Digit == '0' && tmp->m_Next->m_Digit == '0' && tmp->m_Next->m_Next == NULL)
                return 0;
        }

        tmp = tmp->m_Next;
    }
    return 1;
}


int count ( TITEM * a)
{
    int cnt = 0;
    TITEM * tmp = a;
    while ( tmp )
    {
        cnt++;
        tmp = tmp ->m_Next;
    }
    return cnt;
}

TITEM * addList ( TITEM * a,TITEM * b )
{

    if ( check(a) == 0)
        return NULL;
    if ( check(b) == 0)
        return NULL;

    TITEM * headA = a;
    TITEM * headB = b;
    TITEM * res = NULL;
    TITEM * head = res;
    TITEM * tail = NULL;

    int cntA= count(headA);
    int cnt = 0 , cntB = count(headB);

    if ( cntA >= cntB)
        cnt = cntA;
    else
        cnt = cntB;
    int remainder = 0;
    int num1 = 0 , num2 = 0;
    for ( int i = 0 ; i < cnt + remainder ; i++)
    {

            if ( headA && headB)
            {
                num1 = numb(headA->m_Digit);
                num2 = numb(headB->m_Digit);
                headA=headA->m_Next;
                headB=headB->m_Next;
            }
            else if ( headA && !headB)
            {
                num1 = numb(headA->m_Digit);
                num2 = 0;
                headA=headA->m_Next;

            }
            else if (!headA && headB)
            {
                num2 = numb(headB->m_Digit);
                num1 = 0;
                headB=headB->m_Next;
            }
            else if ( !headA && !headB)
            {
                num1 = num2 = 0;
            }

            int sum = num1 + num2 + remainder;

            if ( sum > 9)
            {
                res = createItem(((sum%10)+'0'),NULL);
                remainder = 1;
            }
            else if ( sum <= 9)
            {
                res = createItem((sum+'0'),NULL);
                remainder = 0;
            }
            if ( head == NULL)
            {
                head = res;
                head->m_Next = NULL;
                tail = res;
                tail->m_Next = NULL;
            }
            else {
                tail->m_Next = res;
                tail = tail->m_Next;
            }
    }
    return head;

}


void deleteList ( TITEM * l)
{
    while ( l )
    {
        TITEM * tmp = l->m_Next;
        free(l);
        l = tmp;
    }
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

    return 0;
}

