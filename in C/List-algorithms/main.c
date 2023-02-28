#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TVan
{
    struct TVan   * m_Next;
    char          * m_To;
    void          * m_Cargo; // none
} TVAN;

typedef struct TTrain
{
    TVAN          * m_Start;
    int             m_Count;
} TTRAIN;



TVAN * borrowVan ( const char * to ) // create
{
   TVAN * new= (TVAN*)malloc(sizeof(TVAN));
   new->m_To= (char*)calloc((sizeof(char)+1),(strlen(to)+3));
   strcpy(new->m_To,to);
   new->m_Cargo = NULL;
   new->m_Next = NULL;
   return new;
}
void   delete ( TTRAIN * train )  //delete
{
    TVAN  * list = train->m_Start;
    while ( list )
    {
        TVAN  * tmp = list->m_Next;
        free(list->m_To);
        free(list);
        list= tmp;
    }
}

void   returnVans ( TTRAIN * train )  //delete
{
    TVAN  * list = train->m_Start;
    while ( list )
    {
        TVAN  * tmp = list->m_Next;
        free(list->m_To);
        free(list);
        list= tmp;
    }
    train->m_Start =NULL;
    train->m_Count = 0;
}

void print ( TTRAIN * start)
{
    TVAN * tmp = start->m_Start;
    while ( tmp )
    {
        printf(" %s",tmp->m_To);
        tmp = tmp->m_Next;
    }
    printf("\n");
}

void   connectVan ( TTRAIN * train, TVAN * van, int toStart )
{
    TVAN * tmp = train->m_Start;
    TVAN * new ;
    if ( toStart != 0)
    {
        new = borrowVan(van->m_To);
        new->m_Next = tmp;
        train->m_Start = new;
        train->m_Count++;
    }
    else
    {
        while (tmp && tmp->m_Next)
        {
            tmp = tmp->m_Next;
        }
        new = borrowVan(van->m_To);
        tmp ->m_Next = new;
        new->m_Next = NULL;
        train->m_Count++;
    }
}


void   route ( const char * stationName, TTRAIN * train, TTRAIN * localTrain )
{
    TVAN * headMain = train->m_Start;
    TVAN * localMin = localTrain->m_Start;
    TVAN * resMain;

    while ( headMain && headMain->m_Next != NULL )
    {
        headMain=headMain->m_Next;
    }

    TVAN * localPrev = localMin;

   /*
    headMain->m_Next = localMin;
    train->m_Count+=localTrain->m_Count;
    localTrain->m_Count = 0;

    */

    while ( localMin)
    {
        TVAN * buffer = localMin->m_Next;
        headMain->m_Next = localMin->m_Next;
        headMain=headMain->m_Next;
        localMin->m_Next =
        localPrev = localMin;
        localMin = localMin->m_Next;
    }

   // delete(localTrain);
    printf("----------");
   // print(localTrain);


    headMain = train->m_Start;
    printf("++++++++");
    print(train);
    //localMin = NULL;
    /*
    TVAN * prev = headMain;
    while ( headMain)
    {
        if ( strcmp(headMain->m_To,stationName) == 0)
        {
            connectVan(localTrain,headMain,1);
            prev->m_Next = headMain->m_Next;
        }
        headMain=headMain->m_Next;
        prev = headMain;
    }
*/

}



/*
void   route ( const char * stationName, TTRAIN * train, TTRAIN * localTrain )
{
    TVAN *headMain = train->m_Start;
    TVAN *localMin = localTrain->m_Start;
    TVAN *prevMain = headMain;

    if ( strcmp(headMain->m_To,stationName) == 0)
    {
        TVAN * bufMin = localMin->m_Next;
        TVAN * bufmax = headMain->m_Next;
        localMin = bufmax;
        headMain = bufmax;
    }
    if ( headMain->m_Next != NULL)
    {
        headMain = headMain->m_Next;
    }
    headMain = headMain->m_Next;
    while (headMain )
    {
        if ( strcmp(headMain->m_To,stationName) == 0)
        {

        }
        prevMain = headMain;
        headMain = headMain->m_Next;
    }

}

 */

int main ( int argc, char * argv [] )
{
    TTRAIN a = { NULL, 0 }, b = { NULL, 0 }, c = { NULL, 0 };
    char   tmpStr[100];

    connectVan ( &a, borrowVan ( "Praha" ), 1 );
    connectVan ( &a, borrowVan ( "Brno" ), 1 );
    connectVan ( &a, borrowVan ( "Ostrava" ), 0 );
    connectVan ( &a, borrowVan ( "Brno" ), 0 );
    print(&a);
/* a: train with 4 vans: [Brno] -> [Praha] -> [Ostrava] -> [Brno] */
    connectVan ( &b, borrowVan ( "Praha" ), 1 );
    connectVan ( &b, borrowVan ( "Plzen" ), 1 );
    connectVan ( &b, borrowVan ( "Ostrava" ), 0 );
    connectVan ( &b, borrowVan ( "Praha" ), 0 );
    print(&b);
/* b: train with 4 vans: [Plzen] -> [Praha] -> [Ostrava] -> [Praha] */
    route ( "Brno", &a, &b  );
   // print(&a);
    //print(&b);
/* a: train with 6 vans: [Praha] -> [Ostrava] -> [Plzen] -> [Praha] -> [Ostrava] -> [Praha] */
/* b: train with 2 vans: [Brno] -> [Brno] */
    returnVans ( &a );
    returnVans ( &b );
/*
    connectVan ( &a, borrowVan ( "Praha" ), 1 );
    connectVan ( &a, borrowVan ( "Brno" ), 1 );
    connectVan ( &a, borrowVan ( "Ostrava" ), 0 );
    connectVan ( &a, borrowVan ( "Brno" ), 0 );
    connectVan ( &a, borrowVan ( "Plzen" ), 0 );
    print(&a);
// a: train with 5 vans: [Brno] -> [Praha] -> [Ostrava] -> [Brno] -> [Plzen]
    connectVan ( &b, borrowVan ( "Praha" ), 1 );
    connectVan ( &b, borrowVan ( "Ostrava" ), 1 );
    connectVan ( &b, borrowVan ( "Usti nad Labem" ), 1 );
    print(&b);
    b: train with 3 vans: [Usti nad Labem] -> [Ostrava] -> [Praha]
    connectVan ( &c, borrowVan ( "Kosice" ), 0 );
    connectVan ( &c, borrowVan ( "Plzen" ), 0 );
    connectVan ( &c, borrowVan ( "Ostrava" ), 0 );
    print(&c);
    c: train with 3 vans: [Kosice] -> [Plzen] -> [Ostrava]
    route ( "Brno", &a, &b  );
    print(&a);
    print(&b);
    a: train with 6 vans: [Praha] -> [Ostrava] -> [Plzen] -> [Usti nad Labem] -> [Ostrava] -> [Praha]
     b: train with 2 vans: [Brno] -> [Brno]
    route ( "Praha", &a, &c  );
    print(&a);
    print(&c);
 a: train with 7 vans: [Ostrava] -> [Plzen] -> [Usti nad Labem] -> [Ostrava] -> [Kosice] -> [Plzen] -> [Ostrava]
 c: train with 2 vans: [Praha] -> [Praha]
    returnVans ( &a );
    returnVans ( &b );
    returnVans ( &c );

    strncpy ( tmpStr, "Praha", sizeof ( tmpStr ) );
    connectVan ( &a, borrowVan ( tmpStr ), 1 );
    strncpy ( tmpStr, "Brno", sizeof ( tmpStr ) );
    connectVan ( &a, borrowVan ( tmpStr ), 1 );
    strncpy ( tmpStr, "Ostrava", sizeof ( tmpStr ) );
    connectVan ( &a, borrowVan ( tmpStr ), 0 );
    strncpy ( tmpStr, "Brno", sizeof ( tmpStr ) );
    connectVan ( &a, borrowVan ( tmpStr ), 0 );
    a: train with 4 vans: [Brno] -> [Praha] -> [Ostrava] -> [Brno]
    strncpy ( tmpStr, "Praha", sizeof ( tmpStr ) );
    connectVan ( &b, borrowVan ( tmpStr ), 1 );
    strncpy ( tmpStr, "Plzen", sizeof ( tmpStr ) );
    connectVan ( &b, borrowVan ( tmpStr ), 1 );
    strncpy ( tmpStr, "Ostrava", sizeof ( tmpStr ) );
    connectVan ( &b, borrowVan ( tmpStr ), 0 );
    strncpy ( tmpStr, "Praha", sizeof ( tmpStr ) );
    connectVan ( &b, borrowVan ( tmpStr ), 0 );
    b: train with 4 vans: [Plzen] -> [Praha] -> [Ostrava] -> [Praha]
    route ( "Brno", &a, &b  );
    a: train with 6 vans: [Praha] -> [Ostrava] -> [Plzen] -> [Praha] -> [Ostrava] -> [Praha]
    b: train with 2 vans: [Brno] -> [Brno]
    returnVans ( &a );
    returnVans ( &b );
    */
    return 0;
}