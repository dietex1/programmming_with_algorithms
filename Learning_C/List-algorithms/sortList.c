#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>



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


void deleteList ( Tnode * l)
{
    while ( l )
    {
        Tnode * tmp = l->m_Next;
        free(l);
        l=tmp;
    }
}

int check ( Tnode * l)
{
    Tnode * tmp = l;
    while ( tmp )
    {

        if ( tmp->m_Next != NULL && tmp ->m_Val > tmp->m_Next->m_Val)
            return 0;
        tmp = tmp->m_Next;
    }
    return 1;
}

void swap_elements( Tnode * a, Tnode * b)
{
    int tmp = a -> m_Val;
    a -> m_Val = b -> m_Val;
    b -> m_Val = tmp;
}



void sort_list (Tnode * start)
{
    Tnode * tail = NULL;
    Tnode * head;
    int swap = 1;

    while ( swap == 1){
        swap = 0;
        head = start;
        if (head == tail)
            swap = 0;
        while (head != tail)
        {
            if (head -> m_Next  == tail)
                break;
            if (head -> m_Val > head ->m_Next->m_Val) {
                swap_elements(head, head->m_Next);
                swap = 1;
            }
            head = head -> m_Next;
        }
        tail = head;
    }
}


Tnode * connectLists ( Tnode ** a, int nr )
{

    Tnode ** x = a;
    Tnode * res = NULL;
    Tnode * head = res;
    Tnode * tail = NULL;

    for ( int i = 0 ; i < nr ;i++)
    {
        Tnode *tmp = x[i];
        if (tmp == NULL)
            return  NULL;
        if (check(tmp) == 0)
            return NULL;
        while (tmp)
        {
            res = createItem(tmp->m_Val,NULL);


            if ( head == NULL)
            {
                head = res;
                head ->m_Next = NULL;
                tail = res;
                tail->m_Next = NULL;
            }
            else
            {
                tail ->m_Next = res;
                tail = tail->m_Next;
            }
            tmp = tmp->m_Next;
        }
    }

    sort_list(head);



    return head;
}

void printList ( Tnode * l)
{
    Tnode * tmp = l;
    while ( tmp)
    {
        printf(" %d",tmp->m_Val);
        tmp = tmp->m_Next;
    }
    printf("\n");
}



int main(int argc, char *argv[])
{
    Tnode *a[5], *res;

    a[0] = createItem(1, createItem(5, createItem(19, createItem(24, NULL))));
    a[1] = createItem(3, createItem(7, createItem(17, createItem(25, NULL))));
    res = connectLists(a, 2);
    printList(res);
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
    printList(res);

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
    printList(res);

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
    printList(res);

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
    printList(res);

    assert(res == NULL);
    deleteList(res);

    a[0] = createItem(3, createItem(3, NULL));
    a[1] = createItem(4, createItem(4, NULL));
    a[2] = NULL;
    res = connectLists(a, 3);
    printList(res);

    assert(res == NULL);

    deleteList(res);
    a[0] = createItem(0, NULL);
    a[1] = createItem(4, createItem(4, NULL));
    res = connectLists(a, 2);
    printList(res);

    assert(res->m_Val == 0);
    assert(res->m_Next->m_Val == 4);
    assert(res->m_Next->m_Next->m_Val == 4);
    assert(res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    return 0;
}



