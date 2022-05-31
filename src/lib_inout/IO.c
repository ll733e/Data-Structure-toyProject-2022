#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"
#include "..//lib_type/types.h"

int countFile() {
    FILE*   RFP;
    char    line[200];
    int     tolnum = 0;

    RFP = fopen(oriFILE, "rt");
    fgets(line, sizeof(line), RFP);
    tolnum = atoi(line);
    
    while(!feof(RFP)) {
        fgets(line, sizeof(line), RFP);
        tolnum++;
    }
    fclose(RFP);

    return tolnum;
}

void addNode(Book _book) {
    Node*   curNode = (Node*)malloc(sizeof(Node));
    curNode->book   = _book;
    curNode->pNext  = NULL;

    if(pHead == NULL)   pHead        = curNode;
    else                pTail->pNext = curNode;
    
    pTail = curNode;
}

void loadFile(int tolnum) {
    FILE*   RFP;
    Book    book;
    char    line[256];
    char    *ptH;               // strTOK
    int     lenSTR;             // 길이 카운터의 버퍼 길이
    int     curNum = 0;
    char    *str;

    RFP = fopen(oriFILE, "r+t");

    //while(!feof(RFP))
    for(int i = 0 ; i < 20 ; i++) {
    fgets(line, sizeof(line), RFP);
    ptH = strtok(line, "\t"); lenSTR = strlen(ptH); book.TITLE  = (char*)malloc((lenSTR + 1) * 10); strcpy(book.TITLE  , ptH);
    ptH = strtok(NULL, "\t"); lenSTR = strlen(ptH); book.AUTHOR = (char*)malloc((lenSTR + 1) * 10); strcpy(book.AUTHOR , ptH); 
    ptH = strtok(NULL, "\t"); lenSTR = strlen(ptH); book.YEAR   = (char*)malloc((lenSTR + 1) * 10); strcpy(book.YEAR   , ptH);
    ptH = strtok(NULL, "\t"); lenSTR = strlen(ptH); book.ISBN   = (char*)malloc((lenSTR + 1) * 10); strcpy(book.ISBN   , ptH);
    
    //printf("%s\n%s\n%s\n%s\n", book.TITLE, book.AUTHOR, book.ISBN, book.YEAR);
    addNode(book);
    memset(line, 0, sizeof(line));
    }   
    //printf("%s", ptH);
    /*      TO LOAD ALL FILE       */ 
    //while(!feof(RFP)) 
    /*
    for(int i = 0 ; i < 2 ; i++) {
        fgets(line, sizeof(line), RFP);
        //printf("%s\n", line);
        ptH = strtok(line, "|");    book[curNum].TITLE  = ptH; 
        ptH = strtok(NULL, "|");    book[curNum].AUTHOR = ptH;
        ptH = strtok(NULL, "|");    book[curNum].ISBN   = ptH;
        ptH = strtok(NULL, "|");    book[curNum].YEAR   = ptH;
        curNum++;
    } 
    */
/*
    for(int i = 0 ; i < 2 ; i++) {
        printf("%s \n", book[curnum].TITLE  = ptH);
        printf("%s \n", book[curnum].AUTHOR = ptH);
        printf("%s \n", book[curnum].ISBN   = ptH);
        printf("%s \n", book[curnum].YEAR   = ptH);
        curnum++;
    } */
    //printf("tol : %d\ncol : %d\n", tolnum, curnum);
    fclose(RFP);
}

void showAllInfo() {
    Node    *curNode = pHead;

    if(pHead == NULL) {
        puts("현재 메모리에는 할당된 데이터가 없습니다. [-550 : HEAP FREE]");
        return;
    }
    while(curNode != NULL) {
        printf("%s\n", curNode->book.TITLE);
        curNode = curNode->pNext;
    }
    puts("");
}

void showSingleInfo(Book *_book) {
    printf("책 제목\t\t%s\n", _book->TITLE);
    printf("책 저자\t\t%s\n", _book->AUTHOR);
    printf("발행일자\t[%s]\n", _book->YEAR);
    printf("ISBN 정보\t%s\n", _book->ISBN);
}
/*      노드 정보 삭제 함수        */
void freeNode(Book *_book) {
    // 4개의 필드 모두 동적할당 했었으니 FREE로 동적할당 해지
    if(_book->TITLE  != NULL)    free(_book->TITLE);
    if(_book->AUTHOR != NULL)    free(_book->AUTHOR);
    if(_book->ISBN   != NULL)    free(_book->ISBN);
    if(_book->YEAR   != NULL)    free(_book->YEAR);
}
/*      노드 정보 전체 삭제 함수        */
void freeAllNode() {
    Node    *curNode = pHead;       // 헤드를 현재 노드로 설정
    Node    *delNode = NULL;

    if(pHead == NULL)   return;     // 헤드가 빌 경우 함수 종료
    while(curNode != NULL) {        // 헤드가 비지 않을 경우 빌 때까지 반복
        delNode = curNode;          // 삭제할 노드를 현재 노드로 설정
        curNode = curNode->pNext;   // 현재 노드는 다음 연결 노드로 설정 
        free(delNode->book.TITLE);  // 함수 호출 싫어서 4개 필드 연장선
        free(delNode->book.AUTHOR);
        free(delNode->book.ISBN);
        free(delNode->book.YEAR);
        free(delNode);              // 마지막 깔끔
    }
    pHead = pTail = NULL;           // 이거 안 해주면 더블프리
}

void searchNode() {
    char    searchKey[256];
    Node    *curNode = pHead;
    memset(searchKey, 0, sizeof(searchKey));
    
    printf("검색할 단어를 입력하세요 >> ");
    scanf("%[^\n]s", searchKey);

    system("clear");
    printf("\"%s\" 에 대해 검색한 결과입니다.\n", searchKey);
    while(curNode != NULL) {
        if(strcmp(curNode->book.TITLE, searchKey) == 0) {
            showSingleInfo(&(curNode->book));
            return;
        }
        curNode = curNode->pNext;
    }
    fflush(stdout);
}

int main() {
    int     dataNum = countFile();
    loadFile(dataNum); // 리드
    showAllInfo();
    searchNode();
    freeAllNode();         // 죽여!
    
}
/*
https://stackoverflow.com/questions/8370468/debugging-segmentation-faults-on-a-mac

해야할 것
1. 21번째 메모리 덤프 원인 알아내기
2. 검색 알고리즘 강화 KMP
3. ISBN 자르고 검색 기능(?)
4. 사용자 JSON만들고 대출 여부 만들기
5. 도서 예약
*/