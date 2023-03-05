#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


typedef struct Titem {
    struct Titem * m_Next;
    int m_Mul;
    int m_Pow;
}TITEM;

TITEM * create ( int num , int pow ,  TITEM *next)
{
    TITEM * new = (TITEM * )malloc(sizeof(TITEM));
    new ->m_Mul = num;
    new->m_Pow = pow;
    new->m_Next = next;
    return new;
}

void print ( TITEM * x)
{
    TITEM * tmp = x;
    while ( tmp )
    {
        printf(" %d^%d",tmp->m_Mul , tmp->m_Pow);
        tmp = tmp->m_Next;
    }
    printf("\n");
}

int check ( TITEM * x)
{
    TITEM * tmp = x;
    while ( tmp )
    {
        if ( tmp ->m_Next != NULL)
        {
            if ( tmp ->m_Pow > tmp->m_Next->m_Pow )
            {
                return 0;
            }
        }
        tmp=tmp->m_Next;
    }
    return 1;
}


TITEM * addPoly ( TITEM * a , TITEM * b )
{
    TITEM * headA = a;
    TITEM * headB = b;
    TITEM * res = NULL;
    TITEM * head = res;
    TITEM * tail = NULL;

    int flag = 0;
    if ( check(headA) == 0)
        return NULL;
    if (check(headB) == 0)
        return NULL;
    while ( headA || headB)
    {

        if ( headA && headB)
        {
            if (headA->m_Pow == headB->m_Pow)
            {
                if ( headA->m_Mul + headB->m_Mul == 0)
                {
                    headA=headA->m_Next;
                    headB=headB->m_Next;
                    continue;
                }
                else
                {
                    res = create(headA->m_Mul + headB->m_Mul, headA->m_Pow, NULL);
                    headA = headA->m_Next;
                    headB = headB->m_Next;
                }
            }
            else if (headA->m_Pow < headB->m_Pow)
            {
                res = create(headA->m_Mul, headA->m_Pow, NULL);
                headA = headA->m_Next;
                flag = 1;
            }
            else if (headA->m_Pow > headB->m_Pow)
            {
                res = create(headB->m_Mul, headB->m_Pow, NULL);
                headB = headB->m_Next;
                flag = 2;
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

        if ( flag == 1 || !headA)
        {
            res= create(headB->m_Mul , headB->m_Pow,NULL);
            headB=headB->m_Next;
            flag = 0;
            tail ->m_Next = res;
            tail = tail ->m_Next;
        }
        else if ( flag == 2 || !headB)
        {
            res= create(headA->m_Mul , headA->m_Pow,NULL);
            headA= headA->m_Next;
            flag = 0;
            tail ->m_Next = res;
            tail = tail ->m_Next;
        }

    }

    return head;
}



void  delete ( TITEM * x)
{
    while (x)
    {
        TITEM * tmp = x->m_Next;
        free(x);
        x = tmp;
    }
}



int main ( void ){

    TITEM * a = create(0,0,  NULL);
    print(a);
    TITEM * b = create(7,0, create(4,2, create(-1,3,NULL)));
    print(b);
    TITEM * c = addPoly(a,b);
    print(c);
    delete(a);
    delete(b);
    delete(c);
    return 0;
}








