#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 100

int main ( void )
{
    int maxLoad = 0, maxTex = 0;
    int cap = INITIAL_CAPACITY; //size
    int * timeline = (int*) malloc (cap * sizeof ( timeline ) );
    printf ( "Zatez:\n" );

    while ( ! feof ( stdin ) )
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

        if ( last > maxTex )
            maxTex = last;
    }

    //

   // for ( int i = 0 ; i < 11 ; i++)
    //    printf(" %d %d ",i,timeline[i]);

    //

    printf ( "Nejvyssi zatez: %d\n", maxLoad );

    for ( int i = 0; i <= maxTex; i ++ )
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
