/*
    CORE HEADER LIBRARBY
*/
#ifndef     __CORE_H__
#define     __CORE_H__
#define     AVAILABLE       20

#define     oriFILE    "../../data/book/book.dat"        // 원본파일
#define     USERDIR    "..//..//data//user//"
#define     FORMAT     ".user"
#define     TESTHASH   "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08"

typedef struct Book {
    char    TITLE[200];     // 책 이름
    char    AUTHOR[500];    // 저자 이름
    char    YEAR[20];       // 발행연도
    char    ISBN[20];       // ISBN
}   Book;

typedef struct User {
    char    ID[50];         // 식별할 수 있는 유저 아이디
    char    HS[35];         // 해쉬
    int     RVNum;          // 예약 도서 권수
    Book    RT[AVAILABLE];  // 대출 중인 도서 목록
    Book    *RV;            // 예약 도서 목록
}   User;

typedef struct Node {
    Book    book;
    struct  Node    *pNext;
}   Node;

Node*   pHead = NULL;
Node*   pTail = NULL;

void    addNode();         // 노드 insert 함수
void    loadFile();        // 파일을 로드하는 함수
void    showAllInfo();     // 모든 정보를 출력하는 함수
void    showSingleInfo();  // 특정 정보를 하나만 출력하는 함수
void    freeNodes();       // 노드 전체 프리
void    searchNode();      // 단순 겹치는 문자열 검색 기능 

#endif  // __CORE_H__