#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 100

int main ( void )
{
    int n = 0 ;

    int maxLoad = 0, maxLast = 0;
    int cap = INITIAL_CAPACITY; //size

    int * timeline = (int*) malloc (cap * sizeof ( timeline ) );
    printf ( "Zatez:\n" );

    // while ( ! feof ( stdin ) )
    while( n < 7)
    {
        int first , last, load;
        if (  scanf (" %d: %d..%d",&load ,&first, &last) !=3 || load < 0 || first < 0 || last < first || last < 0)
        {
            printf("Nespravny vstup!\n");
            free(timeline);
            return 1;
        }

        if ( last > cap )
        {
            cap += last + cap;
            timeline = (int*) realloc ( timeline , cap * sizeof( int));
        }

        for ( int i = first; i < last; i ++ )
        {
            timeline[i] += load;

            if ( timeline[i] > maxLoad )
                maxLoad = timeline[i];
        }

        if ( last > maxLast )
            maxLast = last;
        n++;
    }


 //   for ( int i = 0 ; i < 11 ; i++)
 //       printf(" %d %d ",i,timeline[i]);



    printf ( "Nejvyssi zatez: %d\n", maxLoad );

    for ( int i = 0; i <= maxLast; i ++ )
    {
        int start, end;

        if (timeline[i] == maxLoad) {
            start = i;

            while (timeline[i] == maxLoad)
                end = i++;

            printf("%d..%d\n", start, end + 1);
        }


    }
    free ( timeline );
    return 0;
}


