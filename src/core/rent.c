#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int  isAval(char *ISBN) {
    FILE    *RFP;
    char    buf[256];
    char    *p;
    RFP = fopen("..//..//data//book//rented.dat", "r+t");
    
    while(feof(RFP) == 0) {
        fgets(buf, sizeof(buf), RFP);
        p = strtok(buf, "\t");
        if(strcmp(ISBN, p) == 0)    return  0;
    }

    fclose(RFP);

    return 1;
}

void rentBook(char *ID, char *ISBN) {
    FILE    *RFP, *WFP;
    char    buf[256];
    char    *p;
    
    if(isAval(ISBN) == 0) { puts("이미 대출된 도서입니다."); return; }
    else    puts("대출 가능한 도서입니다.");

    RFP = fopen("..//..//data//book//rented.dat", "r+t");
    WFP = fopen("..//..//data//book//bakrent.dat", "w+t");

    

    fclose(RFP);
    fclose(WFP);
}

void returnBook(char *ID, char *ISBN) {
    FILE    *RFP, *WFP;
    char    buf[256];
    char    *p;
    
    if(isAval(ISBN) == 0) { puts("이미 대출된 도서입니다."); return; }
    else    puts("대출 가능한 도서입니다.");

    RFP = fopen("..//..//data//book//rented.dat", "r+t");
    WFP = fopen("..//..//data//book//bakrent.dat", "w+t");

    

    fclose(RFP);
    fclose(WFP);
}

int main() {
    rentBook("2021270131", "978-89-374-4279-7");
}