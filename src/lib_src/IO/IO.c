#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"

#if OS
#define     oriFILE     "../../../data/liblist.test"        // 원본파일
#define     bakFILE     "../../../data/liblist.bak"       // 백업파일
#else
#define     oriFILE     "liblist.test"
#endif

typedef struct Book {
    char    *TITLE;     // 책 이름
    char    *AUTHOR;    // 저자 이름
    char    *ISBN;       // ISBN
    char    *YEAR;       // 발행연도
}   Book;

typedef struct Node {
    Book    book;
    struct  Node    *pNext;
} Node;

Node*   pHead = NULL;
Node*   pTail = NULL;

void FILELOAD() {
    FILE*   RFP;
    Book    book[10];
    char    line[150];
    char    *ptH;               // strTOK
    char    bufTitle[256];      // 제목 BUF
    char    bufAuthor[256];     // 저자 BUF
    int     lenTitle;           // 제목 길이
    int     lenAuthor;          // 저자 길이
    int     curnum = 0;
    int     tolnum = 0;

    // Windows : (OD) OA, MAC : OA;
    RFP = fopen(oriFILE, "r+t");
    fgets(line, sizeof(line), RFP);
    /*      TO LOAD ALL FILE       */ 

    while(!feof(RFP)) {
        ptH = strtok(NULL, "|");    book[curnum].TITLE = ptH; 
        ptH = strtok(NULL, "|");    book[curnum].AUTHOR = ptH;
        ptH = strtok(NULL, "|");    book[curnum].ISBN = ptH;
        ptH = strtok(NULL, "|");    book[curnum].YEAR = ptH;
        curnum++;
    }
    //printf("tol : %d\ncol : %d\n", tolnum, curnum);
    fclose(RFP);
    
}

int main() {
    FILELOAD();


}