#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"

void addNode(Book _book) {
    Node*   curNode = (Node*)malloc(sizeof(Node));
    curNode->book   = _book;
    curNode->pNext  = NULL;

    if(pHead == NULL)   pHead        = curNode;
    else                pTail->pNext = curNode;
    
    pTail = curNode;
}

void deleteEndString(char *buf) {
    int     i = 0;
    while(buf[i]) i++;      i--;
    while(buf[i] == ' ' || buf[i] == '\n') {
        buf[i] = '\0';
        i--;
    }
}

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

void showAllInfo() {
    Node    *curNode = pHead;

    if(pHead == NULL) {
        puts("현재 메모리에는 할당된 데이터가 없습니다. [-550 : HEAP FREE]");
        return;
    }
    while(curNode != NULL) {
        printf("[%s | %s] %s %s %s %s\n", rentStat, resvStat, curNode->book.TITLE,curNode->book.AUTHOR,curNode->book.ISBN,curNode->book.YEAR);
        curNode = curNode->pNext;
    }
    puts("");
}

void showSingleInfo(Book *_book) {
    puts("");
    printf("책 제목\t\t%s\n",   _book->TITLE);
    printf("책 저자\t\t%s\n",   _book->AUTHOR);
    printf("발행일자\t%s\n",     _book->YEAR);
    printf("ISBN 정보\t%s\n",   _book->ISBN);
}
/*      노드 정보 전체 삭제 함수        */
void freeNodes() {
    Node    *curNode = pHead;       // 헤드를 현재 노드로 설정
    Node    *delNode = NULL;

    if(pHead == NULL)   return;     // 헤드가 빌 경우 함수 종료
    while(curNode != NULL) {        // 헤드가 비지 않을 경우 빌 때까지 반복
        delNode = curNode;          // 삭제할 노드를 현재 노드로 설정
        curNode = curNode->pNext;   // 현재 노드는 다음 연결 노드로 설정 
        free(delNode);              // 마지막 깔끔
    }
    pHead = pTail = NULL;           // 이거 안 해주면 더블프리
}

void searchTitle() {
    char    searchKey[256];
    Node    *curNode = pHead;
    memset(searchKey, 0, sizeof(searchKey));
    
    printf("검색할 단어를 입력하세요 >> ");
    scanf("%[^\n]s", searchKey);

    puts("[ 자료구조론 8팀 라이브러리 검색 결과 ]");
    while(curNode != NULL) {
        if(strcmp(curNode->book.TITLE, searchKey) == 0) {
            printf("\"%s\"에 대한 검색 결과입니다.\n", searchKey);
            showSingleInfo(&(curNode->book));
        }
        curNode = curNode->pNext;
    }
    printf("\n\"%s\"에 대한 검색 결과가 없습니다.\n", searchKey);
    return;
}

void searchall(char *searchKey) {
    //char    searchKey[256];
    Node    *curNode = pHead;
    //memset(searchKey, 0, sizeof(searchKey));
    //FILE *fp = fopen("result.txt","w");
    FILE*   RFP;
    RFP = fopen(oriFILE, "r+t");
    if(RFP == NULL) { puts("데이터 파일이 없습니다."); exit(1); }
    
    char *title,*author,*isbn,*year;
    int searchNum = 0;

    //printf("검색할 단어를 입력하세요 >> ");
    //scanf("%[^\n]s", searchKey);

    char *s1;
    puts("[ 자료구조론 8팀 라이브러리 검색 결과 ]");
    printf("\"%s\"에 대한 검색 결과입니다.\n", searchKey);
    //fprintf(fp,"\"%s\"에 대한 검색 결과입니다.\n", searchKey);

    title   = malloc(sizeof(curNode->book.TITLE));
    author  = malloc(sizeof(curNode->book.AUTHOR));
    isbn    = malloc(sizeof(curNode->book.ISBN));
    year    = malloc(sizeof(curNode->book.YEAR));
    strncpy(title,curNode->book.TITLE,   sizeof(curNode->book.TITLE));
    strncpy(author,curNode->book.AUTHOR, sizeof(curNode->book.AUTHOR));
    strncpy(isbn,curNode->book.ISBN,     sizeof(curNode->book.ISBN));
    strncpy(year,curNode->book.YEAR,     sizeof(curNode->book.YEAR));

    while(curNode != NULL) {
        //int     lenSTR;             // 길이 카운터의 버퍼 길이
        char    line[500];
        fseek(RFP, 0, SEEK_SET);

        while(!feof(RFP)) {
            fgets(line, sizeof(line), RFP);
            s1 = strtok(line, ",\t ");
            while(strcmp(s1, "\0") != 0) {
                if(strcmp(s1, searchKey) == 0) {
                    if(strcmp(curNode->book.TITLE, title) == 0 && strcmp(curNode->book.AUTHOR, author) == 0 && strcmp(curNode->book.ISBN, isbn) == 0 && strcmp(curNode->book.YEAR, year) == 0) {
                        s1 = strtok(NULL, ",\t "); if(s1 == NULL) s1 = "\0"; else deleteEndString(s1);
                        continue;
                    }
                    else {
                        searchNum++;
                        strncpy(title,curNode->book.TITLE,   sizeof(curNode->book.TITLE));
                        strncpy(author,curNode->book.AUTHOR, sizeof(curNode->book.AUTHOR));
                        strncpy(isbn,curNode->book.ISBN,     sizeof(curNode->book.ISBN));
                        strncpy(year,curNode->book.YEAR,     sizeof(curNode->book.YEAR));
                        //fprintf(fp,"%d. \"%s\"에 대한 검색 결과입니다.\n", searchNum,searchKey);
                        //fprintf(fp,"%s\n%s\n%s\n%s\n", curNode->book.TITLE,curNode->book.AUTHOR,curNode->book.ISBN,curNode->book.YEAR);
                        showSingleInfo(&(curNode->book));
                    }
                }
                s1 = strtok(NULL, ",\t "); if(s1 == NULL) s1 = "\0"; else deleteEndString(s1);
            }
            curNode = curNode->pNext;
            if(curNode == NULL) {
                break;
            }
        }
        if(searchNum == 0) {
            curNode = pHead;
            while(curNode != NULL) {
            if(strcmp(curNode->book.TITLE, searchKey) == 0) {
                //printf("\"%s\"에 대한 검색 결과입니다.\n", searchKey);
                showSingleInfo(&(curNode->book));
                return;
            }
            curNode = curNode->pNext;
    }
    printf("\n\"%s\"에 대한 검색 결과가 없습니다.\n", searchKey);
    return;
            //printf("\n\"%s\"에 대한 검색 결과가 없습니다.\n", searchKey);
        }
    }
    printf("\n%d개의 검색 결과가 있습니다.\n", searchNum);
    fclose(RFP);
    //fclose(fp);
    free(title);    free(author);   free(isbn);     free(year);
    return;
}

void searchISBN(char *searchKey) {
    Node    *curNode = pHead;

    while(curNode != NULL) {
        if(strcmp(curNode->book.ISBN, searchKey) == 0) {
            printf("\"%s\"에 대한 검색 결과입니다.\n", searchKey);
            showSingleInfo(&(curNode->book));
        }
        curNode = curNode->pNext;
    }
    return;
}

void addUser(char *ID, char *HASH, int rtNum, int rvNum) {
    FILE    *WFP;
    char    buf[256];
    Book    book[20];
    sprintf(buf, "%s%s%s", USERDIR, ID, FORMAT);

    WFP = fopen(buf, "w+t");

    fprintf(WFP, "%s\n", ID);
    fprintf(WFP, "%s\n", HASH);
    fprintf(WFP, "%d\n", rtNum);
    fprintf(WFP, "%d\n", rvNum); // 목록 넣어보기

    fclose(WFP);
}

int  logRespone(char *ID, char *HS) {
    FILE    *RFP;
    char    buf[256];
    char    getID[11];
    char    getHS[65];
    char    *ptel;
    //int     rtNum, rvNum;

    sprintf(buf, "%s%s%s", USERDIR, ID, FORMAT);
    RFP = fopen(buf, "r+t");
    if(RFP == NULL)     return 2;
    
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), RFP);       ptel  = strtok(buf, "\n");    strncpy(getID, ptel, 10);
    fgets(buf, sizeof(buf), RFP);       ptel  = strtok(buf, "\n");    strncpy(getHS, buf, 64);
    //fgets(buf, sizeof(buf), RFP);       rtNum = atoi(buf);
    //fgets(buf, sizeof(buf), RFP);       rvNum = atoi(buf);
    fclose(RFP);
    if(strncmp(HS, getHS, 64 * sizeof(char)) != 0) return -1;
    else    return 1;
    //printf("ID [%s]\tHS [%s]\nrtN [%d]\trvN [%d]\n", getID, getHS, rtNum, rvNum);
    return -1;
}

void logRequest(char *ID, char *HS) {
    if(strlen(ID) != 10 || strlen(HS) != 64)    return;
    int     res = logRespone(ID, HS);
    if(res == 1)       { puts("로그인 성공!"); }
    else if(res == 2)  { puts("찾을 수 없는 계정입니다. 새로 파일을 만듭니다. 초기 비밀번호는 \"test\"입니다."); addUser(ID, TESTHASH, 0, 0); }
    else if(res == -1) { puts("패스워드가 틀렸습니다!"); }
    else               { puts("알 수 없는 오류입니다. 관리자에게 문의하세요."); }
}

int main(int argc, char* argv[]) {
    //logRequest("2021270131", "4888400e1fbc18408be8469b244be413b012f14c8080403f465447fab1a33d59");
    logRequest("2021270139", "4888400e1fbc18408be8469b244be413d012f14c8080403f465447fab1a33d59");
}