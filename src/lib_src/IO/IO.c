#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"

#define     oriFILE     "../../../data/liblist.dat"        // 원본파일
#define     bakFILE     "../../../data/liblist.bak"       // 백업파일

typedef struct Book {
    char    *TITLE;     // 책 이름
    char    *AUTHOR;    // 저자 이름
    uint32  ISBN;       // ISBN
    uint32  YEAR;       // 발행연도
}   Book;

typedef struct Node {
    Book    book;
    struct  Node    *pNext;
} Node;

Node* pHead = NULL;
Node* pTail = NULL;

void FILELOAD() {
    FILE*   RFP;
    Book    book[10];
    char    line[256];
    char    *ptH;               // strTOK
    char    bufTitle[256];      // 제목 BUF
    char    bufAuthor[256];     // 저자 BUF
    int     lenTitle;           // 제목 길이
    int     lenAuthor;          // 저자 길이
    int     curnum = 0;
    int     tolnum = 0;
    

    RFP = fopen(oriFILE, "r");
    /*      TO LOAD ALL FILE         */
    while(fgets(line, sizeof(line), RFP) != NULL) {
        ptH = strtok(NULL, "|");    strcpy(book[curnum].TITLE, ptH); 
        ptH = strtok(NULL, "|");    strcpy(book[curnum].AUTHOR, ptH);
        ptH = strtok(NULL, "|");    book[curnum].ISBN = atoi(ptH);
        ptH = strtok(NULL, "|");    book[curnum].YEAR = atoi(ptH);
        curnum++;
    } 
    //fseek(RFP, 0, SEEK_CUR);
    fclose(RFP);
    //fprintf(RFP, "%d", curnum);

    
}

int main() {
    FILELOAD();

}