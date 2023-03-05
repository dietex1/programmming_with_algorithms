#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct twords{
    struct twords * next;
    char * name;
}TWORDS;


TWORDS * createBook ( char * word ,TWORDS * next )
{
    TWORDS * new = (TWORDS*)malloc(sizeof(TWORDS));
    new->name = (char*)malloc((sizeof(char)+3)*(strlen(word)+4));
    strcpy(new->name,word);
    new->next = next;
    return new;
}

TWORDS * mixChar ( TWORDS * list)
{
    TWORDS * tmp = list;

    if ( list == NULL)
        return NULL;

    TWORDS * res = NULL;
    TWORDS * head = res;
    TWORDS * tail = NULL;

    while ( tmp )
    {
        size_t len = strlen(tmp->name);
        for ( int i = 0 ; i < len ; i++)
        {
            while ( isspace(tmp->name[i]) && i!= len)
            {
                i++;
            }
            char * buffer = (char*)calloc(len+1,sizeof(char));
            int q = 0;
            while (!isspace(tmp->name[i]) && i!= len)
            {
                buffer[q++] = tmp->name[i];
                i++;
            }
            res = createBook(buffer,NULL);
            if ( head == NULL)
            {
                head = res;
                head->next = NULL;
                tail = res;
                tail->next = NULL;
            }
            else
            {
                tail ->next = res;
                tail = tail->next;
            }

            free(buffer);

        }

        tmp = tmp->next;
    }
    return head;
}

void deleteChar ( TWORDS * list)
{
    while ( list)
    {
        TWORDS * tmp = list->next;
        free(list->name);
        free(list);
        list = tmp;
    }
}

void printChar ( TWORDS * list)
{
    TWORDS * tmp = list;
    while ( tmp)
    {
        printf("%s ",tmp->name);
        tmp = tmp->next;
    }
    printf("\n");
}


TWORDS * addFirstChar ( char * word , TWORDS * list)
{
    TWORDS * res = createBook(word,list);
    return res;
}

void addLastChar ( char * word , TWORDS * list)
{
    TWORDS * tmp = list;

    while ( tmp->next )
    {
        tmp =tmp->next;
    }
    TWORDS * res = createBook(word,NULL);
    tmp->next = res;
}


void addBeforeChar ( TWORDS * list, char* before ,char* word)
{
    TWORDS * tmp = list;
    while ( tmp)
    {
        if ( tmp->next != NULL && strcmp(tmp->next->name,before) == 0)
        {
            TWORDS * res = createBook(word,NULL);
            TWORDS * buffer = tmp->next;
            tmp->next = res;
            res->next = buffer;
            return;
        }
        tmp = tmp->next;
    }

}

void deleteNodeChar ( TWORDS * list , TWORDS * node)
{
    TWORDS * tmp = list;
    while ( tmp )
    {
        if ( tmp->next == node && tmp->next != NULL)
        {
            TWORDS * buffer = tmp->next->next;
            free(tmp->next);
            tmp->next= buffer;

        }
        tmp=tmp->next;
    }
}

void replaceChar ( TWORDS * list , char * repl , char * name)
{
    TWORDS * tmp = list;

    while ( tmp )
    {
        if ( strcmp(tmp->next->name,repl) == 0)
        {
            TWORDS * res = createBook(name,NULL);
            TWORDS * buffer = tmp->next->next;
            deleteNodeChar(tmp,tmp->next);
            tmp ->next = res;
            res->next = buffer;
            return;
        }
        tmp=tmp->next;
    }
}

void reverseChar ( TWORDS  ** list)
{
    TWORDS * current = *list;
    TWORDS * prev = NULL;
    TWORDS * next = NULL;
    while ( current )
    {
        next = current ->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *list = prev;
}


void deleteWordChar ( TWORDS * list, char * word)
{
    TWORDS * tmp = list;

    while ( tmp )
    {
        if ( tmp->next != NULL && strcmp(tmp->next->name,word) == 0 )
        {
            TWORDS * buffer = tmp->next->next;
            free(tmp->next->name);
            free(tmp->next);
            tmp ->next = buffer;
            return;
        }
        tmp = tmp->next;
    }
}


//TODO duplicates char
typedef struct duple{
    char * name;
    int count;
}Duple;

int checkDuble (Duple ** array , int * index, int * size , char * buffer )
{
    for ( int i = 0 ; i < (*index) ; i++)
    {
        if ( strcmp((*array)[i].name,buffer) == 0)
        {
            (*array)[i].count++;
            return 1;
        }
    }

    if ((*index) > (*size))
    {
        (*size) *= 2;
        (*array) = (Duple*)realloc((*array),(*size)*sizeof(Duple));
    }

    (*array)[*index].name = (char*)calloc((strlen(buffer)+3),(sizeof(char)+2) );
    strcpy((*array)[*index].name,buffer);
    (*array)[*index].count++;
    (*index)++;
    return 0;
}

TWORDS * duplicChar ( TWORDS * list )
{
    TWORDS * tmp = list;


    TWORDS * res = NULL;
    TWORDS * head = res;
    TWORDS * tail = NULL;
    int index = 0 , size = 16;
    Duple * array = (Duple*)malloc(size* sizeof(Duple));
    while ( tmp)
    {


        if ( checkDuble(&array,&index,&size,tmp->name) == 1)
        {
            //deleteWordChar() if not new list just remove node
            tmp = tmp->next;
            continue;
        }
        else
        {
            res= createBook(tmp->name,NULL);
            if ( head == NULL)
            {
                head = res;
                head->next = NULL;
                tail = res;
                tail->next = NULL;
            }
            else
            {
                tail->next = res;
                tail = tail->next;
            }
        }
        tmp = tmp->next;
    }
    for ( int i = 0 ; i < index ; i++)
        free(array[i].name);
    free(array);
    return head;
}

//TODO duplicates char


//// TODO sort list by sorting array

/*
TODO  for(i=0;i<=n;i++)
      for(j=i+1;j<=n;j++)
      {
           if(strcmp(str[i],str[j])>0)
           {
               strcpy(temp,str[i]);
              strcpy(str[i],str[j]);
              strcpy(str[j],temp);
           }
      }
 */


//TODO LISTY WITH NUMBERS

typedef struct numbers{
    struct numbers * next;
    int m_Digit;
}TNUMB;


TNUMB * createNumber ( int number , TNUMB * next) {
    TNUMB *new = (TNUMB *) malloc(sizeof(TNUMB));
    new->m_Digit = number;
    new->next = next;
    return new;
}

TNUMB * mergeNumb ( TNUMB ** list , int numbList)
{

    if ( list == NULL)
        return NULL;

    TNUMB ** x = list;
    TNUMB * res = NULL;
    TNUMB * head = res;
    TNUMB * tail = NULL;
    for ( int i = 0 ; i < numbList ; i++)
    {
        TNUMB * ar = x[i];
        if ( ar == NULL)
            return NULL;
        while ( ar )
        {
            res = createNumber(ar->m_Digit,NULL);
            if ( head == NULL)
            {
                head = res;
                head->next =NULL;
                tail = res;
                tail->next = NULL;
            }
            else
            {
                tail->next = res;
                tail=tail->next;
            }
            ar = ar->next;
        }
    }
return head;
}

void printNumber ( TNUMB * list)
{
    TNUMB * tmp = list;
    while ( tmp )
    {
        printf("%d ",tmp->m_Digit);
        tmp = tmp->next;
    }
    printf("\n");
}


int cmp ( const void * a , const void * b)
{
    int rec1 = *(int*)a;
    int rec2 = *(int*)b;
    if ( rec1 > rec2)
        return -1;
    else if ( rec1 < rec2)
        return 1;
    else
        return 0;
}

TNUMB * sortNumb ( TNUMB * list)
{
    TNUMB * tmp = list;
    int q = 0 , size = 16;
    int * array = (int*)malloc(size*sizeof(int));
    while ( tmp )
    {
        if ( q >= size)
        {
            size *= 2;
            array= (int*)realloc(array,size*sizeof(int));
        }
        array[q++]= tmp->m_Digit;
        tmp = tmp->next;
    }

    qsort(array,q,sizeof(int),cmp);
    TNUMB * res = NULL;
    TNUMB * head = res;
    TNUMB * tail = NULL;

    for ( int i = 0 ; i < q ; i++)
    {
        res = createNumber(array[i],NULL);
        if ( head == NULL)
        {
            head = res;
            head->next = NULL;
            tail = res;
            tail->next = NULL;
        }
        else
        {
            tail->next = res;
            tail = tail->next;
        }
    }
    return head;

}


void reverseNumb ( TNUMB ** list)
{
    TNUMB * current = *list;
    TNUMB * prev =NULL;
    TNUMB * next= NULL;

    while ( current)
    {
        next = current->next;
        current->next = prev;

        prev = current ;
        current = next;
    }
    (*list) = prev;

}


TNUMB * addFisrtNumb ( TNUMB * list,int  number)
{
   TNUMB * res = createNumber(number,NULL);
   res->next = list;
   return res;
}


void addLastNumb ( TNUMB * list , int number)
{
    TNUMB * tmp = list;

    while ( tmp->next)
    {
        tmp = tmp->next;
    }
    TNUMB * res = createNumber(number,NULL);
    tmp->next = res;
    res->next = NULL;
}


void addBeforeNumb ( TNUMB * list , int number, int before)
{
    TNUMB * tmp = list;
    while ( tmp)
    {
        if ( tmp->next->m_Digit == before)
        {
            TNUMB * buffer = tmp->next;
            TNUMB * res = createNumber(number,NULL);
            tmp->next = res;
            res->next = buffer;
            return;
        }
        tmp = tmp->next;
    }
}

void deleteListNumbers ( TNUMB * list)
{
    while ( list ) {
        TNUMB *tmp = list->next;
        free(list);
        list = tmp;
    }
}


TNUMB *  deleteNumber ( TNUMB * list , int number)
{
    TNUMB * tmp = list;
    if ( list ->m_Digit == number)
    {
        TNUMB * buffer = list->next;
        free(list);
        list = buffer;
        return list;
    }
    while ( tmp )
    {

        if ( tmp ->next != NULL && tmp->next->m_Digit == number)
        {
            TNUMB * buffer = tmp->next->next;
            free(tmp->next);
            tmp->next=buffer;
            return list;
        }
        tmp =tmp->next;
    }
    return list;
}


void helpCounterDuplic ( TNUMB * list , int * q , int * m)
{
    TNUMB * tmp = list;
    while ( tmp )
    {
        if ( tmp->m_Digit > (*q))
            (*q) = tmp->m_Digit;
        if ( tmp->m_Digit < (*m))
            (*m) = tmp->m_Digit;
        tmp = tmp->next;
    }
}

TNUMB * duplicNumb ( TNUMB * list , int limits)
{
    TNUMB * tmp = list;
    TNUMB * res = NULL;
    TNUMB * head = res;
    TNUMB * tail  = NULL;
    int q = 5 , m = 5;
    helpCounterDuplic(list,&q,&m);
    q +=10;
    m *= (-1);
   int * plus = (int*)calloc(q+1,sizeof(int));
   int * minus = (int*)calloc((m+1),sizeof(int));
    //int plus[10000]= {};
    //int minus[10000] = {};
    while ( tmp )
    {
        if ( tmp->m_Digit >= 0)
        {
            if (plus[tmp->m_Digit] < limits)
            {
                plus[tmp->m_Digit]++;
                res = createNumber(tmp->m_Digit,NULL);
                if ( head == NULL)
                {
                    head = res;
                    head->next = NULL;
                    tail = res;
                    tail->next = NULL;
                }
                else
                {
                    tail ->next= res;
                    tail = tail->next;
                }
            }
        }
        else
        {
            int numb = tmp->m_Digit * -1;

            if ( minus[numb] < limits)
            {
                minus[numb]++;
                res = createNumber(tmp->m_Digit,NULL);
                if ( head == NULL)
                {
                    head = res;
                    head->next = NULL;
                    tail = res;
                    tail->next = NULL;
                }
                else
                {
                    tail ->next= res;
                    tail = tail->next;
                }
            }
        }
        tmp = tmp->next;
    }
    return head;
}

int main() {
    TNUMB * listofTmp[2];
    listofTmp[0] = createNumber(13, createNumber(12, createNumber(213, createNumber(2, createNumber(5,NULL)))));
    listofTmp[1] = createNumber(23, createNumber(121, createNumber(1, createNumber(-121, createNumber(10, createNumber(-1,
                                                                                                                       createNumber(13,NULL)))))));
    TNUMB * numbers = mergeNumb(listofTmp,2);
    printNumber(numbers);
    numbers = sortNumb(numbers);
    printNumber(numbers);
    reverseNumb(&numbers);
    printNumber(numbers);
    numbers =  addFisrtNumb(numbers,1111);
    printNumber(numbers);
    addLastNumb(numbers,9999);
    printNumber(numbers);
    addBeforeNumb(numbers,7777,13);
    printNumber(numbers);
    numbers = deleteNumber(numbers,10);
    numbers =  addFisrtNumb(numbers,1111);
    printNumber(numbers);
    TNUMB * aa = duplicNumb(numbers,1);
    printNumber(aa);
    deleteListNumbers(numbers);
    deleteListNumbers(aa);




    //TODO listy with CHARS*
    TWORDS * book = createBook("Hello, my name\n is Rey |\n", createBook("PA1.",NULL) );
    TWORDS * res = mixChar(book);
    printChar(res);
    res = addFirstChar("[FIRST]",res);
    printChar(res);
    addLastChar("[LAST]",res);
    printChar(res);
    addBeforeChar(res,"name","real");
    printChar(res);
    replaceChar(res,"name","surname");
    printChar(res);
    reverseChar(&res);
    printChar(res);
    deleteWordChar(res,"PA1.");
    printChar(res);
    addBeforeChar(res,"real","my");
    addBeforeChar(res,"surname","my");
    printChar(res);
    res = duplicChar(res);
    printChar(res);

    deleteChar(res);
    deleteChar(book);
    return 0;
}


/*
    int i,j,n;
    char str[20][20],temp[20];
    puts("Enter the no. of string to be sorted");
    scanf("%d",&n);
    for(i=0;i<=n;i++)
    {
        gets(str[i]);
    }
    for(i=0;i<=n;i++)
        for(j=i+1;j<=n;j++)
        {
            if(strcmp(str[i],str[j])>0)
            {
                strcpy(temp,str[i]);
                strcpy(str[i],str[j]);
                strcpy(str[j],temp);
            }
        }
    printf("The sorted string\n");

    for(i=0;i<=n;i++)
    {
        puts(str[i]);
    }
*/
