#include <stdio.h>

void cmp3 ( int a , int b , int c , int a1 , int b1 ,int c1 , int * pocet) {
    int x = 0;
    int ar1[] = {a, b, c};
    int ar2[] = {a1, b1, c1};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (ar1[i] == ar2[j]) {
                x++;
                i++;
                j = -1;
            }
    if (x == 3)
        (*pocet)++;
    else
        return;

}

void cmp4 ( int a , int b , int c , int d, int a1 , int b1 ,int c1 ,int d1 , int * pocet) {
    int x = 0;
    int ar1[] = {a, b, c ,d};
    int ar2[] = {a1, b1, c1 ,d1};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (ar1[i] == ar2[j]) {
                x++;
                i++;
                j = -1;
            }
    if (x == 4)
        (*pocet)++;
    else
        return;

}

void cmp5 ( int a , int b , int c ,int d , int e, int a1 , int b1 ,int c1 ,int d1, int e1, int * pocet) {
    int x = 0;
    int ar1[] = {a, b, c,d,e};
    int ar2[] = {a1, b1, c1 ,d1,e1};
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            if (ar1[i] == ar2[j]) {
                x++;
                i++;
                j = -1;
            }
        }
    if (x == 5)
        (*pocet)++;
    else
        return;

}




int main ( void ){
    int pocet = 0;
    int  cis1 ,cis2,cis3 ,cis4,cis5,cis11,cis12,cis13,cis14,cis15;
    char znak ;
    while ( !feof(stdin) )
    {
        scanf(" [ %d , %d , %d", &cis1, &cis2, &cis3);
        scanf(" %c ", &znak);
        if (znak == ',') {
            scanf(" %d", &cis4); //4
            scanf(" %c", &znak);
            if (znak == ',') {
                scanf(" %d ] = [ %d , %d , %d , %d , %d ]", &cis5, &cis11, &cis12, &cis13, &cis14, &cis15); //5
                cmp5(cis1, cis2, cis3, cis4, cis5, cis11, cis12, cis13, cis14, cis15 , &pocet);

            } else if (znak == ']') {
                scanf(" = [ %d ,%d , %d , %d ]", &cis11, &cis12, &cis13, &cis14); //4
                cmp4(cis1, cis2, cis3, cis4, cis11, cis12, cis13, cis14 ,&pocet);

            }

        } else if (znak == ']') {
            scanf(" = [ %d , %d , %d ]", &cis11, &cis12, &cis13);
            //3
            cmp3(cis1, cis2, cis3, cis11, cis12, cis13, &pocet); //3

        }
    }
    printf(" %d\n",pocet);
    return 0;
}


