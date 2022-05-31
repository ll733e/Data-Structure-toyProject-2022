#include <stdio.h>
#define MAX_N 100000
 
int skip[MAX_N];
 
int mstrlen(char* str) {
    int n = -1;
    while (str[++n]);
 
    return n;
}
 
void make_skip_table(char* str, int len) {
 
    for (int i = 0; i < MAX_N; i++) {
        skip[i] = 0;
    }
 
    int j = 0;
    for (int i = 1; i < len; i++) {
        while (j > 0 && str[i] != str[j])
            j = skip[j - 1];
 
        if (str[i] == str[j])
            skip[i] = ++j;
    }
}
 
int do_kmp(int N, char *text, int M, char *pattern) {
    make_skip_table(pattern, M);
 
    int cnt = 0, j = 0;
 
    for (int i = 0; i < N; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = skip[j - 1];
        }
 
        if (text[i] == pattern[j]) {
            if (j == M - 1) {
                printf("found : %d\n", i+1);
                cnt++;
                j = skip[j];
            }
            else {
                j++;
            }
        }
    }
 
    return cnt;
}
 
int main() {
 
    char a[] = "tomatitomatotomato";
    char b[] = "tomato";
 
    int found = do_kmp(mstrlen(a), a, mstrlen(b), b);
    printf("found count : %d\n", found);
 
    return 0;
}