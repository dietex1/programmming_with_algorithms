#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct tnode {
    struct tnode * m_Next;
    int m_Val;
} Tnode;



Tnode * createItem ( int i ,Tnode * next ) {
    Tnode * l = (Tnode*) malloc ( sizeof(*l) );
    l->m_Val = i;
    l->m_Next = next;
    return l;
}


void deleteList(Tnode *l)
{
    while (l)
    {
        Tnode *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}




int compare ( const void * a , const void * b)
{
    int rec1 = *(int*)a;
    int rec2 = *(int*)b;
    if ( rec1 > rec2)
        return 1;
    else if ( rec1 < rec2)
        return -1;
    else
        return 0;
}

int check ( Tnode * x )
{
    Tnode * tmp = x;

    if ( tmp == NULL)
        return 0;

    while ( tmp)
    {
        if ( tmp->m_Next != NULL) {
            if (tmp->m_Val > tmp->m_Next->m_Val)
                return 0;
        }
        tmp = tmp->m_Next;
    }
    return 1;
}

Tnode *connectLists ( Tnode ** a, int nr )
{
    Tnode ** ar = a;

    int * mas = (int *)malloc(sizeof(int));
    int  j = 0;
    for ( int i = 0 ; i < nr ; i++)
    {
        Tnode * hed = ar[i];
        if(check(ar[i]) == 0)
        {
            return NULL;
        }
        while ( hed  != NULL)
        {
            mas[j] = hed->m_Val;
            int x = mas[j];
            mas = (int *) realloc(mas, (sizeof(int) * (j + 2)));
            hed = hed->m_Next;
            j++;
        }

    }

    qsort(mas,j,sizeof(int),compare);

    for ( int i = 0 ; i < j ; i++) {
        int x = mas[i];

        printf(" [ %d ]", x);
    }
    printf("\n");

    Tnode * res = NULL;
    Tnode * head = res;
    Tnode * tail = NULL;

    for ( int i = 0 ; i < j ; i++)
    {
        int x = mas[i];

        printf(" [ %d ]",x);
        res = createItem(x,NULL);
        if ( head == NULL)
        {
            head = res;
            head->m_Next = NULL;
            tail = res;
            tail ->m_Next = NULL;
        }
        else
        {
            tail->m_Next= res;
            tail = tail ->m_Next;
        }


       // printf(" %d",tail->m_Val);

    }


    free(mas);

    return head;
}

int main(int argc, char *argv[])
{
    Tnode *a[5], *res;

    a[0] = createItem(1, createItem(5, createItem(19, createItem(24, NULL))));
    a[1] = createItem(3, createItem(7, createItem(17, createItem(25, NULL))));
    res = connectLists(a, 2);
    assert(res->m_Val == 1);
    assert(res->m_Next->m_Val == 3);
    assert(res->m_Next->m_Next->m_Val == 5);
    assert(res->m_Next->m_Next->m_Next->m_Val == 7);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 17);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 19);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 24);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 25);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);

    a[0] = createItem(-1, createItem(3, createItem(5, NULL)));
    a[1] = createItem(2, createItem(3, createItem(7, NULL)));
    res = connectLists(a, 2);
    assert(res->m_Val == -1);
    assert(res->m_Next->m_Val == 2);
    assert(res->m_Next->m_Next->m_Val == 3);
    assert(res->m_Next->m_Next->m_Next->m_Val == 3);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 5);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 7);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);

    a[0] = createItem(-1, createItem(3, createItem(5, NULL)));
    a[1] = createItem(2, createItem(3, createItem(7, NULL)));
    res = connectLists(a, 2);
    assert(res->m_Val == -1);
    assert(res->m_Next->m_Val == 2);
    assert(res->m_Next->m_Next->m_Val == 3);
    assert(res->m_Next->m_Next->m_Next->m_Val == 3);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 5);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 7);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);

    a[0] = createItem(2, createItem(4, createItem(4, NULL)));
    a[1] = createItem(5, createItem(6, NULL));
    a[2] = createItem(-1, createItem(5, NULL));
    res = connectLists(a, 3);
    assert(res->m_Val == -1);
    assert(res->m_Next->m_Val == 2);
    assert(res->m_Next->m_Next->m_Val == 4);
    assert(res->m_Next->m_Next->m_Next->m_Val == 4);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 5);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 5);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 6);
    assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);

    a[0] = createItem(8, createItem(11, NULL));
    a[1] = createItem(4, createItem(4, NULL));
    a[2] = createItem(-5, createItem(0, NULL));
    a[3] = createItem(2, createItem(1, NULL));
    res = connectLists(a, 4);
    assert(res == NULL);
    deleteList(res);

    a[0] = createItem(3, createItem(3, NULL));
    a[1] = createItem(4, createItem(4, NULL));
    a[2] = NULL;
    res = connectLists(a, 3);
    assert(res == NULL);
    deleteList(res);

    return 0;
}

