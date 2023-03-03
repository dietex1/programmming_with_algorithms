#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
    struct TItem * m_Next;
    int m_Mul;
    int m_Pow;
} TITEM;

TITEM * createItem ( int mul, int pow, TITEM * next )
{
    TITEM * n = (TITEM *) malloc (sizeof ( *n ));
    n -> m_Mul = mul;
    n -> m_Pow = pow;
    n -> m_Next = next;
    return n;
}

void deleteList (TITEM * l)
{
    while (l)
    {
        TITEM * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}

int check ( TITEM * list)
{
    if ( list == NULL)
        return 0;
    TITEM * tmp = list;
    while ( tmp  )
    {
        if ( tmp->m_Next != NULL) {
            if (tmp->m_Pow >= tmp->m_Next->m_Pow)
                return 0;
        }
        tmp = tmp->m_Next;
    }
    return 1;
}



TITEM * addPoly ( TITEM * a , TITEM * b )
{
    TITEM * headA = a;
    TITEM * headB = b;
    if ( check(a) == 0)
        return NULL;
    if ( check(b) == 0)
        return NULL;
    TITEM * res = NULL;
    TITEM * head = res;
    TITEM * tail = NULL;
    while ( headA || headB )
    {
        if ( headA && headB)
        {
            if ( headA->m_Pow == headB->m_Pow)
            {

                if ( headA->m_Mul + headB->m_Mul != 0)
                {
                res = createItem((headA->m_Mul+headB->m_Mul),headA->m_Pow,NULL);
                headA=headA->m_Next;
                headB=headB->m_Next;

                    if ( head == NULL){
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
                else if ( headA->m_Mul + headB->m_Mul == 0)
                {
                    headA=headA->m_Next;
                    headB=headB->m_Next;
                    continue;
                }
            }
            else if ( headA->m_Pow < headB->m_Pow)
            {
                if ( headA->m_Mul != 0 && headA ->m_Pow != 0)
                {
                    res = createItem(headA->m_Mul, headA->m_Pow, NULL);
                    headA = headA->m_Next;

                    if ( head == NULL){
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
                else
                {
                    headA=headA->m_Next;
                }
            }
            else if ( headA->m_Pow > headB->m_Pow)
            {
                if ( headB->m_Mul != 0 && headB->m_Pow != 0) {
                    res = createItem(headB->m_Mul, headB->m_Pow, NULL);
                    headB = headB->m_Next;

                    if ( head == NULL){
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
                else
                {
                    headB=headB->m_Next;
                }
            }
        }
        if ( headA && !headB)
        {
            if ( headA->m_Mul != 0 && headA->m_Pow != 0)
            {
                res = createItem(headA->m_Mul, headA->m_Pow, NULL);
                headA = headA->m_Next;

                if ( head == NULL){
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
            else
            {
                headA=headA->m_Next;
            }
        }
        if ( !headA && headB)
        {
            if ( headB->m_Mul != 0  && headB->m_Pow != 0) {
                res = createItem(headB->m_Mul, headB->m_Pow, NULL);
                headB = headB->m_Next;

                if ( head == NULL){
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
            else
            {
                headB=headB->m_Next;
            }
        }
    }
    if ( head == NULL)
    {
        head = createItem(0,0,NULL);
    }

    return head;
}

void print ( TITEM * list)
{
    TITEM * tmp = list;
    while (tmp)
    {
        printf(" %d^%d ",tmp->m_Mul,tmp->m_Pow);
        tmp = tmp->m_Next;
    }
    printf("\n");
}



int main ( int argc, char * argv [] )
{
    TITEM * a, * b;
    TITEM * res;

    a = createItem (2,1,NULL);
    b = createItem (0,0,NULL);
    res = addPoly(a,b);
    print(res);
    assert ( res -> m_Mul == 2 );
    assert ( res -> m_Pow == 1 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,2,createItem (2,3,createItem(1,0,NULL))));
    res = addPoly(a,b);
    print(res);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,1,NULL));
    res = addPoly(a,b);
    print(res);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (3,0,createItem (2,1,createItem (9,3,NULL)));
    b = createItem (7,0,createItem (4,2,createItem (-1,3,NULL)));
    res = addPoly(a,b);
    print(res);
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (3,0,createItem (2,1,createItem (5,3,NULL)));
    b = createItem (-7,0,createItem (-2,1,createItem (-5,3,NULL)));
    res = addPoly(a,b);
    print(res);
    assert ( res -> m_Mul == -4 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (3,1,createItem (-2,2,createItem (4,3,NULL)));
    b = createItem (-3,1,createItem (2,2,createItem (-4,3,NULL)));
    res = addPoly(a,b);
    print(res);
    assert ( res -> m_Mul == 0 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    return 0;
}
