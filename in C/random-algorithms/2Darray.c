#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct kod {
    int inOut;
    char name[11];
} KOD;


void insert(KOD ***array, int row, int col, char *buffer, int *count) {

    for (int i = 0; i <= row; i++) {
        for (int j = 0; j <= col; j++) {
            if ((*array)[i][j].inOut == 0) {
                //(*array)[i][j].name = (char *) malloc((sizeof(char) * (strlen(buffer) + 2)));
                strcpy((*array)[i][j].name, buffer);
                (*array)[i][j].inOut = 1;
                (*count)--;
                printf("Pozice: %c%c, zbyva: %d\n", (i + 'A'), (j + 'A'), (*count));
                return;
            }
        }

    }
    printf("Plne obsazeno\n");
}


void get(KOD ***array, int row, int col, char *buffer, int *count) {


    for (int i = 0; i <= row; i++) {
        for (int j = 0; j <= col; j++) {
            if ((*array)[i][j].inOut == 1) {
                if (strcmp((*array)[i][j].name, buffer) == 0) {
                    //(*array)[i][j].name = (char *) malloc((sizeof(char) * (strlen(buffer) + 2)));
                    strcpy((*array)[i][j].name, buffer);
                    (*array)[i][j].inOut = 0;
                    (*count)++;
                    printf("Pozice: %c%c, zbyva: %d\n", (i + 'A'), (j + 'A'), (*count));
                    return;
                }
            }
        }
    }
    printf("Nenalezeno\n");
}


void KILL(KOD **array, int row) {
    for (int i = 0; i <= row; i++) {
        free(array[i]);
    }

}

int main(void) {

    int row, col, res;
    char buffer[13], x, y, znak;

    printf("Velikost:\n");

    if (scanf(" %c %c", &x, &y) != 2) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    row = x - 'A';
    col = y - 'A';

    KOD **array = (KOD **) malloc((row + 2) * sizeof(KOD *));
    for (int i = 0; i <= row; i++)
        array[i] = (KOD *) malloc((col + 3) * sizeof(KOD));

    int count = (row + 1) * (col + 1);
    printf("Pozadavky:\n");


    for (int i = 0; i <= row; i++) {
        for (int j = 0; j <= col; j++) {
            array[i][j].inOut = 0;
        }
    }
    while ((res = scanf(" %c", &znak)) != EOF) {


        if (res != 1 || !(znak == '+' || znak == '-')) {
            printf("Nespravny vstup.\n");
            KILL(array, row);
            return 1;
        }

        switch (znak) {
            case '+':

                if (scanf(" %10s", buffer) != 1 || strlen(buffer) > 10 || strlen(buffer) < 0) {
                    printf("Nespravny vstup.\n");
                    KILL(array, row);
                    return 1;
                }
                insert(&array, row, col, buffer, &count);
                break;
            case '-':
                if (scanf(" %10s", buffer) != 1 || strlen(buffer) > 10 || strlen(buffer) < 0) {
                    printf("Nespravny vstup.\n");
                    KILL(array, row);
                    return 1;
                }
                get(&array, row, col, buffer, &count);
                break;
        }
    }

    KILL(array, row);

    return 0;
}
	
