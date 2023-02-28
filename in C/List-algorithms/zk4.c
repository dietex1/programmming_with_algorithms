#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct Titem{
    int m_Number;
    struct Titem * m_Next;
}TITEM;



TITEM * create ( int numb , TITEM * next)
{
    TITEM * new = (TITEM *)malloc(sizeof(TITEM));
    new ->m_Number = numb;
    new->m_Next = next;

    return new;
}

void print(TITEM * a)
{
    for ( TITEM * tmp = a ; tmp ; tmp = tmp->m_Next)
    {
        printf(" %d ",tmp->m_Number);
    }
    printf("\n");
}


void listFront ( TITEM ** head , int value)
{
    *head = create(value,*head);
}

int compare ( const void * lec , const void * lec2)
{
    int rec1 = *(int*)lec;
    int rec2 = *(int*)lec2;

    if ( rec1 > rec2)
        return 1;
    else if ( rec1 < rec2)
        return -1;
    else
        return 0;
}

TITEM * kkk ( TITEM * a , TITEM * b , TITEM * c)
{

    int * array = (int * )calloc(30,sizeof(int));
    int i = 0;
    TITEM * headA = a;
    TITEM * headB = b;
    TITEM * headC = c;

    while ( headA )
    {
        array[i] = headA->m_Number;
        headA=headA->m_Next;
        i++;
    }
    array = (int * )realloc(array,20* i * sizeof(int));
    while (headB)
    {
        array[i] = headB->m_Number;
        headB=headB->m_Next;
        i++;
    }
    array = (int * )realloc(array,20* i * sizeof(int));
    while (headC)
    {
        array[i] = headC->m_Number;
        headC=headC->m_Next;
        i++;
    }

    qsort(array,i,sizeof(int),compare);

    TITEM * res = NULL;
    TITEM * head = res;
    TITEM * tail = NULL;

    for ( int j = 0 ; j < i ; j++)
    {

       res = create(array[j],NULL);

       if ( head == NULL)
       {
           head = res;
           head ->m_Next = NULL;
           tail = res ;
           tail ->m_Next = NULL;
       }
       else
       {
           tail -> m_Next = res;
           tail = tail ->m_Next;
       }

    }
    free(array);
    return head;
}


void KILL ( TITEM * a )
{


    while ( a != NULL)
    {
        TITEM * tmp = a ->m_Next;
        free(a);
        a= tmp;
    }
}


int main (void){

    TITEM * a = create(1, create(5, create(10,NULL)));
    print(a);
    TITEM * b = create(4,  create(8,NULL));
    print(b);
    TITEM * c = create(-3,  create(25,NULL));
    print(c);

    TITEM * add = kkk(a,b,c);
    print(add);
    KILL(a);
    KILL(b);
    KILL(c);

    return 0;
}



