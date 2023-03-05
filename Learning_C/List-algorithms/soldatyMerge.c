#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TSoldier
{
    struct TSoldier   * m_Next;
    int                 m_PersonalID;
    char                m_SecretRecord[64];
} TSOLDIER;


TSOLDIER * create  (int id , TSOLDIER * next)
{
    TSOLDIER * new = (TSOLDIER*)malloc(sizeof(TSOLDIER));
    new->m_PersonalID = id;
    new->m_Next = next;
    return new;
}

TSOLDIER         * mergePlatoons     ( TSOLDIER   * p1, TSOLDIER   * p2 ) {
    TSOLDIER *headA = p1;
    TSOLDIER *headB = p2;

    TSOLDIER *res = NULL;
    TSOLDIER *head = res;
    TSOLDIER *tail = NULL;
    while (headA || headB) {
        if (headA) {
            res = create(headA->m_PersonalID, NULL);
            if (head == NULL) {
                head = res;
                head->m_Next = NULL;
                tail = res;
                tail->m_Next = NULL;
            } else {
                tail->m_Next = res;
                tail = tail->m_Next;
            }
            headA = headA->m_Next;
        }

        if (headB) {
            res = create(headB->m_PersonalID, NULL);
            if (head == NULL) {
                head = res;
                head->m_Next = NULL;
                tail = res;
                tail->m_Next = NULL;
            } else {
                tail->m_Next = res;
                tail = tail->m_Next;
            }
            headB = headB->m_Next;
        }

    }
    return head;
}


int counter ( TSOLDIER * src)
{
    TSOLDIER * tmp = src;
    int count = 0;
    while ( tmp )
    {
        count++;
        tmp = tmp->m_Next;
    }
    return count;
}

void   KILL    ( TSOLDIER        * src ) {
    while (src)
    {
        TSOLDIER *tmp = src->m_Next;
       // free(src->m_SecretRecord);
        free(src);
        src = tmp;
    }
}

void  splitPlatoon  ( TSOLDIER  * src,TSOLDIER  ** p1,TSOLDIER  ** p2 )
{
    TSOLDIER * man = src;

    int cnt ;
    cnt = counter(src);
    if ( cnt%2 == 1)
        cnt-=1;

    KILL(*p1);
    KILL(*p2);

    *p1 = NULL;
    *p2 = NULL;
    TSOLDIER  * headA = *p1;
    TSOLDIER *  headB  = *p2;

    TSOLDIER  * res1 = NULL;
    TSOLDIER  * hedA = res1;
    TSOLDIER  * res2 = NULL;
    TSOLDIER  * hedB = res2;
    TSOLDIER  * talA = NULL;
    TSOLDIER  * talB = NULL;



    for ( int i = 0 ; i < cnt ; i++)
    {
        while ( i != cnt/2)
        {
           res1 = create(man->m_PersonalID,NULL);
           if ( hedA == NULL)
           {
               hedA=res1;
               hedA->m_Next = NULL;
               talA = res1;
               talA->m_Next = NULL;
           }
           else
           {
               talA->m_Next = res1;
               talA=talA->m_Next;
           }
            i++;
            man=man->m_Next;
        }
        *p1 = hedA;

        while ( i!= cnt)
        {
            res2 = create(man->m_PersonalID,NULL);
            if ( hedB == NULL)
            {
                hedB=res2;
                hedB->m_Next = NULL;
                talB = res2;
                talB->m_Next = NULL;
            }
            else
            {
                talB->m_Next = res2;
                talB=talB->m_Next;
            }
            man=man->m_Next;
            i++;
        }
        *p2 = hedB;



    }

}

void               destroyPlatoon    ( TSOLDIER        * src ) {
    while (src)
    {
        TSOLDIER *tmp = src->m_Next;
        free(src);
        src = tmp;
    }
}

void print(TSOLDIER * list)
{
    TSOLDIER * tmp = list;
    while ( tmp )
    {
        printf(" %d ",tmp->m_PersonalID);
        tmp = tmp->m_Next;
    }
    printf("\n");
}

TSOLDIER         * createSoldier     ( int               id,
                                       TSOLDIER        * next )
{
    TSOLDIER * r = (TSOLDIER *) malloc ( sizeof ( *r ) );
    r -> m_PersonalID = id;
    r -> m_Next = next;
    /* r -> m_SecretRecord will be filled by someone with a higher security clearance */
    return r;
}
int main ( void )
{
    TSOLDIER * a, *b, *c;
    a = createSoldier ( 0,
                        createSoldier ( 1,
                                        createSoldier ( 2,
                                                        createSoldier ( 3,
                                                                        createSoldier ( 4, NULL )))));
    b = createSoldier ( 10,
                        createSoldier ( 11,
                                        createSoldier ( 12,
                                                        createSoldier ( 13,
                                                                        createSoldier ( 14, NULL )))));
    c = mergePlatoons ( a, b );
    print(c);
    assert ( c != NULL
             && c -> m_PersonalID == 0
             && c -> m_Next != NULL
             && c -> m_Next -> m_PersonalID == 10
             && c -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_PersonalID == 1
             && c -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
             && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 3
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 4
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    splitPlatoon ( c, &a, &b );
    print(a);
    print(b);
    assert ( a != NULL
             && a -> m_PersonalID == 0
             && a -> m_Next != NULL
             && a -> m_Next -> m_PersonalID == 10
             && a -> m_Next -> m_Next != NULL
             && a -> m_Next -> m_Next -> m_PersonalID == 1
             && a -> m_Next -> m_Next -> m_Next != NULL
             && a -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
             && a -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
             && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b != NULL
             && b -> m_PersonalID == 12
             && b -> m_Next != NULL
             && b -> m_Next -> m_PersonalID == 3
             && b -> m_Next -> m_Next != NULL
             && b -> m_Next -> m_Next -> m_PersonalID == 13
             && b -> m_Next -> m_Next -> m_Next != NULL
             && b -> m_Next -> m_Next -> m_Next -> m_PersonalID == 4
             && b -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && b -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
             && b -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    destroyPlatoon ( a );
    destroyPlatoon ( b );

    a = createSoldier ( 0,
                        createSoldier ( 1,
                                        createSoldier ( 2, NULL )));
    b = createSoldier ( 10,
                        createSoldier ( 11,
                                        createSoldier ( 12,
                                                        createSoldier ( 13,
                                                                        createSoldier ( 14, NULL )))));
    c = mergePlatoons ( a, b );
    assert ( c != NULL
             && c -> m_PersonalID == 0
             && c -> m_Next != NULL
             && c -> m_Next -> m_PersonalID == 10
             && c -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_PersonalID == 1
             && c -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
             && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    splitPlatoon ( c, &a, &b );
    assert ( a != NULL
             && a -> m_PersonalID == 0
             && a -> m_Next != NULL
             && a -> m_Next -> m_PersonalID == 10
             && a -> m_Next -> m_Next != NULL
             && a -> m_Next -> m_Next -> m_PersonalID == 1
             && a -> m_Next -> m_Next -> m_Next != NULL
             && a -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
             && a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b != NULL
             && b -> m_PersonalID == 2
             && b -> m_Next != NULL
             && b -> m_Next -> m_PersonalID == 12
             && b -> m_Next -> m_Next != NULL
             && b -> m_Next -> m_Next -> m_PersonalID == 13
             && b -> m_Next -> m_Next -> m_Next != NULL
             && b -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
             && b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    destroyPlatoon ( a );
    destroyPlatoon ( b );

    a = createSoldier ( 0,
                        createSoldier ( 1,
                                        createSoldier ( 2, NULL )));
    b = createSoldier ( 10,
                        createSoldier ( 11,
                                        createSoldier ( 12,
                                                        createSoldier ( 13, NULL ))));
    c = mergePlatoons ( a, b );
    assert ( c != NULL
             && c -> m_PersonalID == 0
             && c -> m_Next != NULL
             && c -> m_Next -> m_PersonalID == 10
             && c -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_PersonalID == 1
             && c -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
             && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    splitPlatoon ( c, &a, &b );
    assert ( a != NULL
             && a -> m_PersonalID == 0
             && a -> m_Next != NULL
             && a -> m_Next -> m_PersonalID == 10
             && a -> m_Next -> m_Next != NULL
             && a -> m_Next -> m_Next -> m_PersonalID == 1
             && a -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b != NULL
             && b -> m_PersonalID == 11
             && b -> m_Next != NULL
             && b -> m_Next -> m_PersonalID == 2
             && b -> m_Next -> m_Next != NULL
             && b -> m_Next -> m_Next -> m_PersonalID == 12
             && b -> m_Next -> m_Next -> m_Next == NULL );
    destroyPlatoon ( a );
    destroyPlatoon ( b );

    return 0;
}

