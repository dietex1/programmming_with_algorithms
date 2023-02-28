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

int numb ( char n )
{
    return n - 48;
}


int check ( TITEM * x)
{
    if ( x == NULL)
        return 0;
    while ( x)
    {
        if ( numb(x->m_Digit) > 9 || numb(x->m_Digit) < 0)
            return 0;

        x = x ->m_Next;
    }
    return 1;
}


int compare ( TITEM * x , TITEM * y)
{

    int res = 0;
    while ( x || y )
    {
        int numb1 = 0;
        int numb2= 0;
        if ( x)
        {
            numb1 = numb(x->m_Digit);
            x= x->m_Next;
        }
        if ( y )
        {
            numb2 = numb(y->m_Digit);
            y = y->m_Next;
        }
        if ( numb1 > numb2)
            res = 1;
        else if ( numb1 < numb2)
            res = 0;
        else
            continue;

    }
    return res;
}

TITEM * maxOf (TITEM ** x, int nr)
{
    TITEM * max = x[0];

    for ( int i = 0 ; i < nr ; i++)
        if (check(x[i]) == 0)
            return NULL;
    for ( int i = 1 ; i < nr ; i++)
    {

        if (compare(x[i],max) == 1)
            max = x[i];

    }
    return max;
}



int main (int argc, char * argv [])
{
    TITEM * a[5];

    a[0] = createItem ( '4',
                        createItem ( '3',
                                     createItem ( '2',
                                                  createItem ( '2', NULL ))));
    a[1] = createItem ( '4',
                        createItem ( '3',
                                     createItem ( '3',
                                                  createItem ( '2', NULL))));
    assert ( maxOf ( a, 2 ) == a[1] );
    deleteList( a[0] );
    deleteList( a[1] );

    a[0] = createItem ( '2',
                        createItem ( '0',
                                     createItem ( '0',
                                                  createItem ( '1', NULL ))));
    a[1] = createItem ( '2',
                        createItem ( '3',
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
    assert ( maxOf ( a, 2 ) == a[1] );
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
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList ( a[2] );

    return 0;
}




