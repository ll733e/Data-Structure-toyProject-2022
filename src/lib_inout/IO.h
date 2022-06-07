/*
    IO는 책을 모아놓은 빅데이터의 입출력을 담당하는 라이브러리입니다.
*/
#ifndef __IO_H__
#define __IO_H__


#define     oriFILE     "../../data/book/book.dat"        // 원본파일

typedef struct Book {
    char    TITLE[200];     // 책 이름
    char    AUTHOR[500];    // 저자 이름
    char    YEAR[20];       // 발행연도
    char    ISBN[20];       // ISBN
}   Book;

typedef struct Node {
    Book    book;
    struct  Node    *pNext;
} Node;

Node*   pHead = NULL;
Node*   pTail = NULL;

int     countFile();       // 축척된 파일의 개수를 구하는 함수
void    addNode();         // 노드를 추가합니다
void    loadFile();        // 파일을 로드하는 함수
void    showAllInfo();     // 모든 정보를 출력하는 함수
void    showSingleInfo();  // 특정 정보를 하나만 출력하는 함수
void    freeNode();        // 특정 노드 프리
void    freeAllNode();     // 전체 노드 프리
void    searchNode();      // 단순 겹치는 문자열 검색 기능 
void    searchNodeKMP();   // KMP 알고리즘 문자열 검색 기능


#endif  // __IO_H__