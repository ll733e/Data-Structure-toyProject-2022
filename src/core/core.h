/*
    CORE HEADER LIBRARBY
*/
#ifndef     __CORE_H__
#define     __CORE_H__
#define     AVAILABLE       20
#define     BOOKNUM         3849

#define     oriFILE    "../../data/book/book.dat"        // 원본파일
#define     USERDIR    "..//..//data//user//"
#define     RTFILE     "..//..//data//book//rented.dat"
#define     RBFILE     "..//..//data//book//rentBUF.dat"
#define     FORMAT     ".user"
#define     TESTHASH   "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08"

typedef struct Book {
    char    TITLE[200];     // 책 이름
    char    AUTHOR[500];    // 저자 이름
    char    YEAR[20];       // 발행연도
    char    ISBN[20];       // ISBN
}   Book;

typedef struct Node {
    Book    book;
    struct  Node    *pNext;
}   Node;

typedef struct User {
    char    ID[50];         // 식별할 수 있는 유저 아이디
    char    HS[35];         // 해쉬
    int     RVNum;          // 예약 도서 권수
}   User;

Node*   pHead = NULL;
Node*   pTail = NULL;
Node*   rHead = NULL;
Node*   rTail = NULL;

static char*    rentStat = "대출가능";
static char*    resvStat = "예약가능";

// 파일 로드 및 적재 부분
void loadFile();
void addNode(Book _book);
void freeNodes();
void deleteEndString(char *buf);

// 도서 검색
void searchall(char *searchKey);
void BookList(char *res, int *res_len, char *searchKey, const int limit, const int page);
void searchTitle();
Book rentSearch(char *searchKey);
///void searchISBN(char *searchKey);

// 로그인
int logRespone(char *ID, char *HS);
int logRequest(char *ID, char *HS);
void Login(char *res, int *res_len, char *id, char *passwd);
void addUser(char *ID, char *HASH, int rtNum, int rvNum);

// 대여
void Rental(char *res, int *res_len, char *ISBN, char *ID);
void rentBook(char *ID, char *ISBN);

// 반납
void Return(char *res, int *res_len, char *ID, char *ISBN);
void returnBook(char *ID, char *ISBN);

void showInfoMain();
void showSingleInfo(Book *_book);

void searchMain();
int isAval(char *ISBN);
void rentBookMain(char *ID);
void returnBookMain();
void menu();
void RentInfoMain(char *ID);

#endif  // __CORE_H__