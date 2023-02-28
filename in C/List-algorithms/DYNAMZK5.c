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



TITEM * duplic ( TITEM * x , int limits)
{
    TITEM * tmp = x;
    TITEM * res= NULL;
    TITEM * head = res;
    TITEM * tail = NULL;

    if ( x == NULL || limits < 1)
        return NULL;

    //int plus[1000]={};


    int * plus = (int*)calloc(100,sizeof(int)+2);
    int max = 0;

    //int minus[1000]={};

    int * minus = (int*)malloc(100*(sizeof(int)+2));
    while ( tmp )
    {
        int num = tmp->m_Val;

        if (max < num )
            max = num;

        if ( num >=0)
        {

            plus = (int*)realloc(plus,(max+10)*sizeof(int)+2);


            if ( plus[num] < limits)
            {
                plus[num]++;
                res= create(tmp->m_Val,NULL);
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
                    tail=tail->m_Next;
                }
            }

        }
        else if ( num < 0)
        {
            num *=-1;
            if ( num > max)
                max = num;
            minus = (int*)realloc(minus,(max+10)*(sizeof(int)+1));


            if ( minus[num] < limits)
            {
                minus[num]++;
                res = create(tmp->m_Val,NULL);
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
                    tail=tail->m_Next;
                }
            }

        }

        tmp=tmp->m_Next;
    }
    free(plus);
    free(minus);
    return head;

}


int main() {

    TITEM * a , * res;

    a = create(1, create(1, create(2, create(-123123132, create(1000000, create(2, create(1,NULL)))))));
    res = duplic(a,2);
    print(res);
    assert (res->m_Val == 1);
    assert (res->m_Next->m_Val == 1);
    assert (res->m_Next->m_Next->m_Val == 2);
    assert (res->m_Next->m_Next->m_Next->m_Val == -123123132);
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Val == 1000000);
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

    a= create(1,NULL);
    res= duplic(a,0);
    print (res);
    delete(res);
    delete(a);
    a= NULL;
    res = duplic(a,2);
    print(res);
    assert (res== NULL);
    delete(res);
    delete(a);
    return 0;
}


