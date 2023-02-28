#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *acronym;
    int len;
} acronym_t;

typedef struct {
    char *line;
    int len;
    char task;
} problem_t;

typedef struct words {
    int *from; // start of word
    int *to; // end of word
    int *limit; // N fr each word
    int limit_max;// N
    int size;
    int *sols;// 1..N solutions
} words_t;

// read line and cut off tabs, spaces before and after "
int read_problem(problem_t *problem) {
    int letter;
    int cnt = 0;
    problem->len = 10;
    problem->line = (char*)malloc(problem->len*sizeof(char));
    //skip all tabs or spaces, return error if EOF
    while(1) {
        letter = getchar();
        if ((letter == ' ') || (letter == '\t')) {
            continue;
        } else if (letter == '"') {
            problem->line[cnt++] = letter;
            break;
        } else {
            return ((letter == EOF) ? -1 : 0);
        }
    }
    // write to line all symbols untill \n reached
    while(1) {
        letter = getchar();
        if (letter == '\n') {
            break;
        } else {
            if (cnt == problem->len) {
                problem->len *= 2;
                problem->line = (char*)realloc(problem->line, problem->len*sizeof(char));
            }
            problem->line[cnt++] = tolower(letter);
        }
    }
    if (!cnt) {
        return 0;
    }
    // cut all tabs or spaces
    for (int i = cnt - 1; i >= 1; i--) {
        if (problem->line[i] == '"') {
            problem->len = i + 1;
            break;
        }
        if (i == 1) {
            return 0;
        }
    }
    return 1;
}

// get start and end indicies of all words
void parse(problem_t *problem, words_t *words, int limit) {
    int count = 0;
    int words_count = 0;
    words->limit_max = limit;
    words->size = 10;
    words->from = (int*)malloc(words->size*sizeof(int));
    words->to = (int*)malloc(words->size*sizeof(int));
    for (int i = 0; i < problem->len; i++) {  
        // if char found read untill not char      
        while(isalpha(problem->line[i])) {
            count++;
            i++;
            if (i == problem->len) {
                break;
            }
        }
        if (count) {
            if (words_count == words->size) {
                words->size += 10;
                words->from = (int*)realloc(words->from, words->size*sizeof(int));
                words->to = (int*)realloc(words->to, words->size*sizeof(int));
            }
            words->from[words_count] = i - count;
            words->to[words_count] = i;
            words_count++;
            count = 0;
        }
    }
    words->size = words_count;
    words->limit = (int*)calloc(words->size, sizeof(int));
    words->sols = (int*)calloc(words->limit_max, sizeof(int));
}

// Recursive functions which iterates throug each symbol and word
// Printing srting at the end and writes solution to suolution array for each N
void find(problem_t *problem, acronym_t *acronym, int acr_cnt, words_t *words, int word_cnt, int idx, int max) {
    if (acr_cnt != acronym->len) {
        char ch = acronym->acronym[acr_cnt];
        for (int i = word_cnt; i < words->size; i++) { // for aech word
            int from, next_word, next_idx;
            // Determin if we want to start from first symbols if wthis word
            // or from next relative to last uppercased
            if (words->limit[i] == 0) {
                from = words->from[i];
            } else {
                from = idx;
            }
            for (int j = from; j < words->to[i]; j++) { // for each symbol in word
                if ((words->limit[i] != words->limit_max) && (problem->line[j] == ch)) {
                    int max_next = max; // lacol copy for max variable
                    problem->line[j] = toupper(problem->line[j]);
                    words->limit[i]++; // increasy capacity of N used
                    // Shirt word or symbol index
                    if (words->limit[i] != words->limit_max) {
                        next_word = i;
                        next_idx = j + 1;
                    } else {
                        next_word = i + 1;
                        next_idx = j;
                    }
                    if (words->limit[i] > max) {
                        max_next = words->limit[i];
                    }
                    find(problem, acronym, acr_cnt + 1, words, next_word, next_idx, max_next);
                    // turn back all the chages
                    words->limit[i]--;
                    problem->line[j] = tolower(problem->line[j]);
                }
            }
        }
    } else {
        if (problem->task == '?') {
            for (int i = 0; i < problem->len; i++) {
                putchar(problem->line[i]);
            }
            putchar('\n');
        }
        for (int i = 0; i < words->limit_max; i++) { // for each possible solution
            if (i >= max - 1) {
                words->sols[i]++;
            }
        }
    }
}

int solve(acronym_t *acronym, int limit, int task) {
    int rc;
    problem_t problem;
    words_t words;
    rc = read_problem(&problem);
    problem.task = task;
    if (rc > 0) {
        parse(&problem, &words, limit);
        find(&problem, acronym, 0, &words, 0, 0, 0);
        if (problem.task == '?') {
            printf("> %d\n", words.sols[limit - 1]);
        } else {
            for (int i = 0; i < limit; i++) {
                printf("> limit %d: %d\n", i + 1, words.sols[i]);
            }
        }
        free(words.from);
        free(words.to);
        free(words.limit);
        free(words.sols);
    }   
    free(problem.line);
    return rc;
}

int main(int argc, char *argv[]) {
    int letter;
    int cnt = 0;
    acronym_t acronym;
    acronym.len = 10;
    acronym.acronym = (char*)malloc(acronym.len*sizeof(char));
    printf("Zkratka:\n");
    while((letter = getchar()) != '\n') {
        if (!isupper(letter)) {
            cnt = 0;
            break;
        }
        if (cnt == acronym.len) {
            acronym.len *= 2;
            acronym.acronym = (char*)realloc(acronym.acronym, acronym.len*sizeof(char));
        }
        acronym.acronym[cnt++] = tolower(letter);
    }
    if (!cnt) {
        printf("Nespravny vstup.\n");
    } else {
        acronym.len = cnt;
        printf("Problemy:\n");
        char task;
        int limit, rc;
        while((rc = scanf("%c %d", &task, &limit)) != EOF) {
            if ((rc != 2) || ((task != '#') && (task != '?')) || (limit <= 0)) {
                printf("Nespravny vstup.\n");
                break;
            } else {
                rc = solve(&acronym, limit, task);
                if (rc <= 0) {
                    if (rc == 0) {
                        printf("Nespravny vstup.\n");
                    }
                    break;
                }
            }
        }
    }
    free(acronym.acronym);    
    return 0;
}
