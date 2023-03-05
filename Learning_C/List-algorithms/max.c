#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
    struct TItem * m_Next;
    char           m_Digit;
} TITEM;

TITEM * createItem ( char digit, TITEM * next )
{
    TITEM * n = (TITEM *) malloc (sizeof ( *n ));
    n -> m_Digit = digit;
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


int numb ( char n)
{
    return n - 48;
}

int check ( TITEM * x )
{
    TITEM * tmp = x ;
    int len = 0;
    if ( x  == NULL )
        return 0;
    while ( tmp )
    {
        if ( numb(tmp->m_Digit) < 0 || numb(tmp->m_Digit) > 9)
            return 0;
        tmp = tmp->m_Next;
        len++;
    }
    return len;
}

/*
int compare (TITEM * x , TITEM * y)
{
    TITEM * headX = x;
    TITEM * headY = y;
    int max = 0;
    while ( headX || headY)
    {
        if (numb(headX->m_Digit) > numb(headY->m_Digit) )
        {
            if ( numb(headX->m_Digit) > max)
                max = numb(headX->m_Digit);
        }
        else
        {
            if (  numb(headY->m_Digit) > max)
                max = numb(headY->m_Digit);
        }
        headX=headX->m_Next;
        headY=headY->m_Next;
    }
    return max;

}
 */

int compare (TITEM * x )
{
    TITEM * headX = x;
    int max = 0;
    int num1 = 0,num2 = 0;
    while ( headX )
    {
        if (headX->m_Next != NULL)
        {

            if ( numb(headX->m_Digit) == max && numb(headX->m_Next->m_Digit) == max )
            {
                if (headX->m_Next != NULL)
                    headX = headX->m_Next;
            }



            if (numb(headX->m_Digit) > numb(headX->m_Next->m_Digit))
            {
                if (numb(headX->m_Digit) > max)
                    max = numb(headX->m_Digit);
            }
            else
            {
                if (numb(headX->m_Next->m_Digit) > max)
                    max = numb(headX->m_Next->m_Digit);
            }


            if (headX->m_Next != NULL)
                headX = headX->m_Next;
        }
        else
            return max;
    }
    return max;

}


TITEM * maxOf (TITEM ** x, int nr)
{

    TITEM * y = x[0];
    int mmax = 0;
    for ( int i = 0; i < nr ; i++) {
        if ( check(x[i]) == 0 )
            return NULL;
        if (compare(x[i]) == mmax)
            continue;
        if (compare(x[i]) > mmax)
        {
            mmax = compare(x[i]);
            y = x[i];
        }


    }
    printf(" %c\n" ,mmax+'0');
    return y;

}

int main (int argc, char * argv [])
{
    TITEM * a[5];

    a[0] = createItem ( '4',
                        createItem ( '3',
                                     createItem ( '2',
                                                  createItem ( '1', NULL ))));
    a[1] = createItem ( '2',
                        createItem ( '3',
                                     createItem ( '4',
                                                  createItem ( '5', NULL))));

    assert ( maxOf ( a, 2 ) == a[1] );
    deleteList( a[0] );
    deleteList( a[1] );

    a[0] = createItem ( '0',
                        createItem ( '0',
                                     createItem ( '0',
                                                  createItem ( '1', NULL ))));
    a[1] = createItem ( '2',
                        createItem ( '0',
                                     createItem ( '0',
                                                  createItem ( '1', NULL ))));
    a[2] = createItem ( '1',
                        createItem ( '0',
                                     createItem ( '0',
                                                  createItem ( '1', NULL))));
    a[3] = createItem ( '2',
                        createItem ( '0',
                                     createItem ( '0',
                                                  createItem ( '1',
                                                               createItem ( '0',
                                                                            createItem ( '0', NULL ))))));
    assert ( maxOf ( a, 4 ) == a[1] );
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList ( a[2] );
    deleteList ( a[3] );

    a[0] = createItem ( '1',
                        createItem ( '0',
                                     createItem ( '0',
                                                  createItem ( '0',
                                                               createItem ( '0',
                                                                            createItem ( '0', NULL ))))));
    a[1] = createItem ( '0',
                        createItem ( '0',
                                     createItem ( '1', NULL )));
    a[2] = createItem ( '1',
                        createItem ( '0',
                                     createItem ( '0',
                                                  createItem ( '0',
                                                               createItem ( '0',
                                                                            createItem ( '9', NULL ))))));
    a[3] = createItem ( '0',
                        createItem ( '0',
                                     createItem ( '0',
                                                  createItem ( '0',
                                                               createItem ( '0',
                                                                            createItem ( '0',
                                                                                         createItem ( '0',
                                                                                                      createItem ( '0',
                                                                                                                   createItem ( '0',
                                                                                                                                createItem ( '0',
                                                                                                                                             createItem ( '0',
                                                                                                                                                          createItem ( '0',
                                                                                                                                                                       createItem ( '0',
                                                                                                                                                                                    createItem ( '0',
                                                                                                                                                                                                 createItem ( '0', NULL )))))))))))))));
    assert ( maxOf (a, 4) == a[2] );
    maxOf(a,2);
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList ( a[2] );
    deleteList ( a[3] );

    a[0] = createItem ( '0',
                        createItem ( '0',
                                     createItem ( '0',
                                                  createItem ( '0',
                                                               createItem ( '0',
                                                                            createItem ( '0',
                                                                                         createItem ( '0',
                                                                                                      createItem ( '0',
                                                                                                                   createItem ( '0',
                                                                                                                                createItem ( '0',
                                                                                                                                             createItem ( '0',
                                                                                                                                                          createItem ( '0',
                                                                                                                                                                       createItem ( '0',
                                                                                                                                                                                    createItem ( '0',
                                                                                                                                                                                                 createItem ( '0',
                                                                                                                                                                                                              createItem ( '0',
                                                                                                                                                                                                                           createItem ( '0',
                                                                                                                                                                                                                                        createItem ( '0',
                                                                                                                                                                                                                                                     createItem ( '0',
                                                                                                                                                                                                                                                                  createItem ( '0',
                                                                                                                                                                                                                                                                               createItem ( '0',
                                                                                                                                                                                                                                                                                            createItem ( '1', NULL ))))))))))))))))))))));
    a[1] = createItem ( '1',
                        createItem ( '0',
                                     createItem ( '0',
                                                  createItem ( '0',
                                                               createItem ( '0',
                                                                            createItem ( '0',
                                                                                         createItem ( '0',
                                                                                                      createItem ( '0',
                                                                                                                   createItem ( '0',
                                                                                                                                createItem ( '0',
                                                                                                                                             createItem ( '0',
                                                                                                                                                          createItem ( '0',
                                                                                                                                                                       createItem ( '0',
                                                                                                                                                                                    createItem ( '0',
                                                                                                                                                                                                 createItem ( '0',
                                                                                                                                                                                                              createItem ( '0',
                                                                                                                                                                                                                           createItem ( '0',
                                                                                                                                                                                                                                        createItem ( '0',
                                                                                                                                                                                                                                                     createItem ( '0',
                                                                                                                                                                                                                                                                  createItem ( '0',
                                                                                                                                                                                                                                                                               createItem ( '0',
                                                                                                                                                                                                                                                                                            createItem ( '1', NULL ))))))))))))))))))))));
    assert ( maxOf ( a, 2 ) == a[0] );
    maxOf(a,2);
    deleteList ( a[0] );
    deleteList ( a[1] );

    a[0] = createItem ( '3',
                        createItem ( '2',
                                     createItem ( '1', NULL )));
    a[1] = createItem ( '6',
                        createItem ( '5',
                                     createItem ( '4', NULL )));
    a[2] = createItem ( '9',
                        createItem ( 'c',
                                     createItem ( 'b',
                                                  createItem ( '9',
                                                               createItem ( '9', NULL )))));
    assert ( maxOf ( a, 3 ) == NULL);
    maxOf(a,3);
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList ( a[2] );

    return 0;
}
