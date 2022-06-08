#include <stdio.h>
#include <stdlib.h>
#include "core.h"

#define     USERDIR    "..//..//data//user//"
#define     FORMAT     ".user"

void loadFile(int tolnum) {
    FILE*   RFP;
    Book    book;
    int     lenSTR;             // 길이 카운터의 버퍼 길이
    int     curNum = 0;
    char    line[500];
    char    *s1, *s2, *s3, *s4;

    RFP = fopen(oriFILE, "r+t");
    if(RFP == NULL) { puts("데이터 파일이 없습니다."); exit(1); }
    //while(!feof(RFP))

    for(int i = 0 ; i < tolnum ; i++) {
        fgets(line, sizeof(line), RFP);

        s1 = strtok(line, "\t");    if(s1 == NULL) s1 = "\0";   else deleteEndString(s1);  strcpy(book.TITLE,  s1);
        s2 = strtok(NULL, "\t");    if(s2 == NULL) s2 = "\0";   else deleteEndString(s2);  strcpy(book.AUTHOR, s2);
        s3 = strtok(NULL, "\t");    if(s3 == NULL) s3 = "\0";   else deleteEndString(s3);  strcpy(book.YEAR,   s3);
        s4 = strtok(NULL, "\n");    if(s4 == NULL) s4 = "\0";   else deleteEndString(s4);  strcpy(book.ISBN,   s4);
        //printf("%s\n%s\n%s\n%s\n\n", s1, s2, s3, s4);
        
        addNode(book);
        //printf("%s\n%s\n%s\n%s\n\n", book.TITLE, book.AUTHOR, book.YEAR, book.ISBN);
    }
    fclose(RFP);
}

void addUser(char *ID, char *HASH, int rtNum, int rvNum) {
    FILE    *WFP;
    char    buf[256];
    Book    book[20];
    sprintf(buf, "%s%s%s", USERDIR, ID, FORMAT);

    WFP = fopen(buf, "w+t");

    fprintf(WFP, "%s\n", ID);
    fprintf(WFP, "%s\n", HASH);   

    for(int i = 0 ; i < rtNum - 1 ; i++) {
        fprintf(WFP, "%s\t", book.ISBN[i]);
    }   fprintf(WFP, "%s\n", book.ISBN[rtNum - 1]);

    fclose(WFP);
}

int main() {
    addUser("2021270131", "4888400e1fbc18408be8469b244be413b012f14c8080403f465447fab1a33d59", 3, 10);
}