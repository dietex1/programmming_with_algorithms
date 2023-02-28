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

void print ( TITEM * x)
{
    TITEM * tmp = x;
    while ( tmp)
    {
        printf(" %c\n",tmp->m_Digit);
        tmp = tmp->m_Next;
    }
    printf("\n");
}

int number ( char n)
{
    return n - '0';
}

int check (TITEM * x)
{
    TITEM * tmp = x;
    while ( tmp != NULL)
    {


        if ( number(tmp->m_Digit) > 9 || number(tmp->m_Digit) < 0)
            return 0;
        if ( tmp->m_Digit == '0')
        {
            if (  tmp-> m_Next != NULL && tmp->m_Next ->m_Digit == '0')
            {
                if ( tmp->m_Next->m_Next  == NULL)
                    return 0;
            }
        }
        tmp = tmp->m_Next;
    }
    return 1;
}

TITEM * addList ( TITEM * a,TITEM * b )
{
    TITEM * headA = a;
    TITEM * headB = b;
    if ( headA == NULL)
        return NULL;
    if ( headB == NULL)
        return NULL;
    if (check(headA) == 0)
        return NULL;
    if (check(headB) == 0)
        return NULL;
    headA = a;
    headB = b;
    TITEM * res = NULL;
    TITEM * head = res;
    TITEM * tail = NULL;


    while ( headA || headB)
    {
        int remainder = 0;
        if ( headA && headB)
        {
            int num1 = number(headA->m_Digit);
            int num2 = number(headB->m_Digit);
            int sum = num1 + num2 + remainder;
            if ( remainder == 0){}
            {
                if (sum < 9) {
                    res = createItem((sum + '0'), NULL);
                    headA = headA->m_Next;
                    headB = headB->m_Next;
                    remainder = 0;

                } else if (sum > 9) {
                    sum = sum % 10;
                    res = createItem((sum + '0'), NULL);
                    headA = headA->m_Next;
                    headB = headB->m_Next;
                    remainder = 1;
                }
                if (head == NULL) {
                    head = res;
                    head->m_Next = NULL;
                    tail = res;
                    tail->m_Next = NULL;
                } else {
                    tail->m_Next = res;
                    tail = tail->m_Next;
                }


            }
            if (remainder == 1)
            {
                res = createItem((1+'0'),NULL);
                remainder = 0;
                tail->m_Next = res;
                tail = tail->m_Next;
            }
        }

        else if ( headA && !headB)
        {
            res = createItem((headA->m_Digit ), NULL);
            headA = headA->m_Next;
            if (head == NULL) {
                head = res;
                head->m_Next = NULL;
                tail = res;
                tail->m_Next = NULL;
            } else {
                tail->m_Next = res;
                tail = tail->m_Next;
            }
        }
        else if ( !headA && headB)
        {
            res = createItem((headB->m_Digit ), NULL);
            headB = headB->m_Next;
            if (head == NULL) {
                head = res;
                head->m_Next = NULL;
                tail = res;
                tail->m_Next = NULL;
            } else {
                tail->m_Next = res;
                tail = tail->m_Next;
            }
        }





    }
    return head;

}

int main(int argc, char *argv[]) {
    TITEM *a, *b, *res;

    a = createItem('x', NULL);
    b = createItem('3', NULL);
    res = addList(a, b);
    print(res);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('5',
                   createItem('0',
                              createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    print(res);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);


    a = createItem('3',
                   createItem('4',
                              createItem('5', NULL)));
    b = createItem('0', NULL);
    res = addList(a, b);
    print(res);
    assert (res->m_Digit == '3');
    assert (res->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Digit == '5');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('2',
                   createItem('3',
                              createItem('9', NULL)));
    b = createItem('5',
                   createItem('3',
                              createItem('1', NULL)));
    res = addList(a, b);
    print(res);
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);

    a = createItem('2', createItem('3', createItem('3', NULL)));
    b = createItem('5', createItem('3', createItem('1', NULL)));
    res = addList(a, b);
    print(res);
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




