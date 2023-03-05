#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TItem {
    struct TItem * m_Next;
    int m_Digit;
} TITEM;

TITEM * create ( int data , TITEM * next)
{
    TITEM * new = (TITEM*)malloc(sizeof(TITEM));
    new->m_Digit = data;
    new->m_Next = next;
    return new;
}


void delete ( TITEM * l)
{
    while ( l )
    {
        TITEM * tmp = l->m_Next;
        free(l);
        l=tmp;
    }
}

TITEM * tren(TITEM * a , int zdvig)
{
    TITEM * tmp = a;

    int array[100];
    int q = 0;
    while (tmp)
    {
        array[q++]=tmp->m_Digit;
        tmp=tmp->m_Next;
    }


    if ( zdvig < 0)
    {
        zdvig *= -1;
        // left shift
        for (int i = 0; i < zdvig; ++i) {
            int last = array[q - 1];
            for (int j = q - 1; j > 0; j--)
                array[j] = array[j - 1];
            array[0] = last;
        }

        for (int i = 0; i < q; ++i)
            printf("%d ", array[i]);
        printf("\n");

    }
    else if ( zdvig > 0)
    {
        //RIGHT shift
        for (int i = 0; i < zdvig; i++)
        {
            int first = array[0];
            for (int j = 0; j < q - 1; j++)
            {
                array[j] = array[j + 1];
            }
            array[q - 1] = first;
        }

        for (int i = 0; i < q; ++i)
            printf("%d ", array[i]);
    }

    TITEM * res = NULL;
    TITEM * head = res;
    TITEM * tail = NULL;

        for ( int i = 0 ; i < q ; i++)
        {
            res = create(array[i],NULL);
            if ( head == NULL)
            {
                head = res;
                head->m_Next = NULL;
                tail = res;
                tail->m_Next = NULL;
            }
            else
            {
                tail->m_Next = res;
                tail = tail->m_Next;
            }
        }
        return head;
}



int main() {
    TITEM * a,* res;
    a = create(1, create(2, create(3, create(4,NULL))));

    res = tren(a,-1);
    assert (res->m_Digit == 4);
    assert (res->m_Next->m_Digit == 1);
    assert (res->m_Next->m_Next->m_Digit == 2);
    assert (res->m_Next->m_Next->m_Next->m_Digit == 3);
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    delete(a);
    delete(res);

    a = create(1, create(2, create(3, create(4,NULL))));

    res = tren(a,1);
    assert (res->m_Digit == 2);
    assert (res->m_Next->m_Digit == 3);
    assert (res->m_Next->m_Next->m_Digit == 4);
    assert (res->m_Next->m_Next->m_Next->m_Digit == 1);
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    delete(a);
    delete(res);

    return 0;
}

