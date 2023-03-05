#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct Titem{
    struct Titem * m_Next;
    int m_Val;
} TITEM;


TITEM * create ( int val , TITEM * next)
{
    TITEM * new = (TITEM*)malloc(sizeof(TITEM));
    new->m_Val = val;
    new->m_Next = next;
    return new;
}


void delete ( TITEM * l)
{
    while ( l )
    {
        TITEM * tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}

void  print ( TITEM * l)
{
    TITEM * tmp = l;
    while ( tmp )
    {
        printf(" %d ",tmp->m_Val);
        tmp = tmp->m_Next;
    }
    printf("\n");
}



TITEM * duplic (TITEM * x, int limits) {
    {

        TITEM *tmp = x;

        TITEM *res = NULL;
        TITEM *head = res;
        TITEM *tail = NULL;

        int arr[1000000] = {};
        int arrMin[1000000] = {};
        while (tmp) {
            int number = tmp->m_Val;
            if ( number >= 0)
            {
                if (arr[tmp->m_Val] < limits)
                {
                    arr[tmp->m_Val]++;
                    res = create(tmp->m_Val, NULL);
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
            else if ( number < 0)
            {
                number *= -1;
                if (arrMin[number] < limits) {
                    arrMin[number]++;
                    res = create(tmp->m_Val, NULL);
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
            tmp = tmp->m_Next;
        }
        return head;
    }
}


int main() {

    TITEM * a , * res;

    a = create(1, create(1, create(2, create(3, create(4, create(2, create(1,NULL)))))));
    res = duplic(a,2);
    print(res);
    assert (res->m_Val == 1);
    assert (res->m_Next->m_Val == 1);
    assert (res->m_Next->m_Next->m_Val == 2);
    assert (res->m_Next->m_Next->m_Next->m_Val == 3);
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Val == 4);
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 2);
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    delete(res);
    delete(a);

    a = create(-1, create(1, create(2, create(3, create(-1, create(2, create(1,NULL)))))));
    res = duplic(a,2);
    print(res);
    assert (res->m_Val == -1);
    assert (res->m_Next->m_Val == 1);
    assert (res->m_Next->m_Next->m_Val == 2);
    assert (res->m_Next->m_Next->m_Next->m_Val == 3);
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Val == -1);
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 2);
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 1);
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    delete(res);
    delete(a);

    return 0;
}

