#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

typedef struct word {
    int from, len;
} word_t;

typedef struct {
    word_t *words;
    int count;
} str_as_idx;

int strcmp_nocase(char const *a, char const *b, int len) {
    for (int i = 0; i < len; i++, a++, b++) {
        if ((tolower((unsigned char)*a) - tolower((unsigned char)*b)) != 0) {
            return 0;
        }
    }
    return 1;
}

void str_to_idx(str_as_idx *idx, const char *str) {
    idx->count = 0;
    int size = 10;
    idx->words = (word_t*)malloc(size*sizeof(word_t));
    for (unsigned int i = 0; i < strlen(str); i++) {
        int from, len = 0;
        if (isalpha(str[i])) {
            from = i++;
            len++;
            while(isalpha(str[i])) {
                len++;
                i++;
            }
            if (idx->count) {
                int add = 1;
                word_t *word;
                for (int j = 0; j < idx->count; j++) {
                    word = &idx->words[j];
                    if (len == word->len) {
                        if (strcmp_nocase(str + word->from, str + from, len)) {
                            add = 0;
                            break;
                        }
                    }
                }
                if (add) {
                    if (idx->count == size) {
                        size *= 2;
                        idx->words = (word_t*)realloc(idx->words, size*sizeof(word_t));
                    }
                    idx->words[idx->count].from = from;
                    idx->words[idx->count].len = len;
                    idx->count++;
                }
            } else {
                idx->words[idx->count].from = from;
                idx->words[idx->count].len = len;
                idx->count++;
            }
        }
    }
    idx->words = (word_t*)realloc(idx->words, idx->count*sizeof(word_t));
}

int sameWords ( const char * a, const char * b ) {
    int result = 0;
    str_as_idx astr, bstr;
    str_to_idx(&astr, a);
    str_to_idx(&bstr, b);
    if (astr.count == bstr.count) {
        if (!astr.count) {
            result = 1;
        } else {
            word_t *aword, *bword;
            int found = 0;
            for (int  i = 0; i < astr.count; i++) {
                aword = &astr.words[i];
                found = 0;
                for (int j = 0; j < bstr.count; j++) {
                    bword = &bstr.words[j];
                    if (aword->len == bword->len) {
                        found = strcmp_nocase(a + aword->from, b + bword->from, aword->len);
                        if (found) {
                            break;
                        }
                    }
                }
                if (!found) {
                    break;
                }
            }
            result = found;
        }
    }
    free(astr.words);
    free(bstr.words);
    return result;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    assert ( sameWords ( "Hello students.HELLO studEnts", "HELLO studEnts!" ) == 1 );
    assert ( sameWords ( " He said 'hello!'", "'Hello.' he   said." ) == 1 );
    assert ( sameWords ( "He said he would do it.", "IT said: 'He would do it.'" ) == 1 );
    assert ( sameWords ( "one two three", "one two five" ) == 0 );
    return 0;
}
#endif /* __PROGTEST__ */
