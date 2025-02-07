#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "core.h"
#include "json/parson.h"
#include "socket/socketCore.h"

//파일 로드 및 적재 부분

void loadFile(int tolnum) {
    FILE*   RFP;
    Book book;
    int     lenSTR;             // 길이 카운터의 버퍼 길이
    int     curNum = 0;
    char    line[500];
    char    *s,*s1, *s2, *s3, *s4;

    RFP = fopen(oriFILE, "r+t");
    if(RFP == NULL) { puts("데이터 파일이 없습니다."); exit(1); }

    for(int i = 0 ; i < tolnum ; i++) {
        fgets(line, sizeof(line), RFP);
        s1 = strtok(line, "\t");    if(s1 == NULL) s1 = "\0";   else deleteEndString(s1);  strcpy(book.TITLE,  s1);
        s2 = strtok(NULL, "\t");    if(s2 == NULL) s2 = "\0";   else deleteEndString(s2);  strcpy(book.AUTHOR, s2);
        s3 = strtok(NULL, "\t");    if(s3 == NULL) s3 = "\0";   else deleteEndString(s3);  strcpy(book.YEAR,   s3);
        s4 = strtok(NULL, "\n");    if(s4 == NULL) s4 = "\0";   else deleteEndString(s4);  strcpy(book.ISBN,   s4);
        addNode(book);
    }
    fclose(RFP);
}

void addNode(Book _book) {
    Node*   curNode = (Node*)malloc(sizeof(Node));
    curNode->book   = _book;
    curNode->pNext  = NULL;

    if(pHead == NULL)   pHead        = curNode;
    else                pTail->pNext = curNode;
    
    pTail = curNode;
}

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

void deleteEndString(char *buf) {
    int     i = 0;
    while(buf[i]) i++;      i--;
    while(buf[i] == ' ' || buf[i] == '\n') {
        buf[i] = '\0';
        i--;
    }
}

//도서 검색

void searchall(char *searchKey) {
    Node    *curNode    = pHead;
    char    *title, *author, *isbn, *year, *tmp;
    char    *sptr;
    int     searchNum = 0;
    Book    sResult[10];

    title   = malloc(sizeof(curNode->book.TITLE));  strncpy(title,curNode->book.TITLE,   sizeof(curNode->book.TITLE));
    author  = malloc(sizeof(curNode->book.AUTHOR)); strncpy(author,curNode->book.AUTHOR, sizeof(curNode->book.AUTHOR));
    isbn    = malloc(sizeof(curNode->book.ISBN));   strncpy(isbn,curNode->book.ISBN,     sizeof(curNode->book.ISBN));
    year    = malloc(sizeof(curNode->book.YEAR));   strncpy(year,curNode->book.YEAR,     sizeof(curNode->book.YEAR));
    tmp     = malloc(sizeof(curNode->book.TITLE) + sizeof(curNode->book.AUTHOR) + sizeof(curNode->book.ISBN) + sizeof(curNode->book.YEAR));


    while(curNode != NULL) {
        sprintf(tmp, "%s %s %s %s", curNode->book.TITLE, curNode->book.AUTHOR, curNode->book.ISBN, curNode->book.YEAR);

        if(strcmp(title, searchKey) == 0) {
            if(searchNum < 10) {
                strncpy(sResult[searchNum].TITLE, curNode->book.TITLE,      sizeof(curNode->book.TITLE));
                strncpy(sResult[searchNum].AUTHOR, curNode->book.AUTHOR,    sizeof(curNode->book.AUTHOR));
                strncpy(sResult[searchNum].ISBN, curNode->book.ISBN,        sizeof(curNode->book.ISBN));
                strncpy(sResult[searchNum].YEAR, curNode->book.YEAR,        sizeof(curNode->book.YEAR));
            }
            showSingleInfo(&(curNode->book));
            searchNum++;
            curNode = curNode->pNext;
            continue;
        }

        sptr = strtok(tmp, ",\t ");

        while(sptr != NULL) {
            if(strcmp(sptr, searchKey) == 0) {
                if(searchNum < 10) {
                    strncpy(sResult[searchNum].TITLE, curNode->book.TITLE,      sizeof(curNode->book.TITLE));
                    strncpy(sResult[searchNum].AUTHOR, curNode->book.AUTHOR,    sizeof(curNode->book.AUTHOR));
                    strncpy(sResult[searchNum].ISBN, curNode->book.ISBN,        sizeof(curNode->book.ISBN));
                    strncpy(sResult[searchNum].YEAR, curNode->book.YEAR,        sizeof(curNode->book.YEAR));
                }
                showSingleInfo(&(curNode->book));
                searchNum++;
                break;
            }
            sptr = strtok(NULL,",\t ");
        }
        curNode = curNode->pNext;
    }
    if(searchNum ==  0) {
        printf("\"%s\"와 일치하는 검색어를 찾지 못 했습니다.\n", searchKey);
    }
    
    free(title);
    free(author);
    free(isbn);
    free(year);
    free(tmp);
}

void BookList(char *res, int *res_len, const char *searchKey, const char *ID) {
    Node    *curNode    = pHead;
    char    *title, *author, *isbn, *year, *tmp;
    char    *sptr;
    int     searchNum = 0;
    Book    sResult[10];

    title   = malloc(sizeof(curNode->book.TITLE));  strncpy(title,curNode->book.TITLE,   sizeof(curNode->book.TITLE));
    author  = malloc(sizeof(curNode->book.AUTHOR)); strncpy(author,curNode->book.AUTHOR, sizeof(curNode->book.AUTHOR));
    isbn    = malloc(sizeof(curNode->book.ISBN));   strncpy(isbn,curNode->book.ISBN,     sizeof(curNode->book.ISBN));
    year    = malloc(sizeof(curNode->book.YEAR));   strncpy(year,curNode->book.YEAR,     sizeof(curNode->book.YEAR));
    tmp     = malloc(sizeof(curNode->book.TITLE) + sizeof(curNode->book.AUTHOR) + sizeof(curNode->book.ISBN) + sizeof(curNode->book.YEAR));

    while(curNode != NULL) {
        sprintf(tmp, "%s %s %s %s", curNode->book.TITLE, curNode->book.AUTHOR, curNode->book.ISBN, curNode->book.YEAR);

        if(strcmp(title, searchKey) == 0) {
            if(searchNum < 10) {
                strncpy(sResult[searchNum].TITLE, curNode->book.TITLE,      sizeof(curNode->book.TITLE));
                strncpy(sResult[searchNum].AUTHOR, curNode->book.AUTHOR,    sizeof(curNode->book.AUTHOR));
                strncpy(sResult[searchNum].ISBN, curNode->book.ISBN,        sizeof(curNode->book.ISBN));
                strncpy(sResult[searchNum].YEAR, curNode->book.YEAR,        sizeof(curNode->book.YEAR));
            }
            searchNum++;
            curNode = curNode->pNext;
            continue;
        }

        sptr = strtok(tmp, ",\t ");

        while(sptr != NULL) {
            if(strcmp(sptr, searchKey) == 0) {
                if(searchNum < 10) {
                    strncpy(sResult[searchNum].TITLE, curNode->book.TITLE,      sizeof(curNode->book.TITLE));
                    strncpy(sResult[searchNum].AUTHOR, curNode->book.AUTHOR,    sizeof(curNode->book.AUTHOR));
                    strncpy(sResult[searchNum].ISBN, curNode->book.ISBN,        sizeof(curNode->book.ISBN));
                    strncpy(sResult[searchNum].YEAR, curNode->book.YEAR,        sizeof(curNode->book.YEAR));
                }
                searchNum++;
                break;
            }
            sptr = strtok(NULL,",\t ");
        }
        curNode = curNode->pNext;
    }
    int len = (searchNum < 10) ? searchNum : 10;

    JSON_Value *rootVal = json_value_init_object();
    JSON_Object *rootObj = json_value_get_object(rootVal);

    JSON_Value *tmpv;
    JSON_Object *tmpo;

    json_object_set_number(rootObj, "res", (searchNum) ? 1 : 2);
    json_object_set_string(rootObj, "msg", (searchNum) ? "Success" : "Failed");
    json_object_set_number(rootObj, "count", searchNum);
    json_object_set_value(rootObj, "book", json_value_init_array());
    
    JSON_Array *book = json_object_get_array(rootObj, "book");

    for(int i=0; i < len; i++)
    {
        tmpv = json_value_init_object();
        tmpo = json_value_get_object(tmpv);
        json_object_set_string(tmpo,"isbn", sResult[i].ISBN);
        json_object_set_string(tmpo,"bookTitle", sResult[i].TITLE);
        json_object_set_string(tmpo,"author", sResult[i].AUTHOR);
        json_object_set_string(tmpo,"publishYear", sResult[i].YEAR);
        json_object_set_number(tmpo,"isAvailable", frontAval(ID, sResult[i].ISBN));
        json_array_append_value(book,tmpv);
    }
    
    char *serial = json_serialize_to_string(rootVal);
    strcpy(res, serial);
    *res_len = strlen(res);

    json_value_free(rootVal);
    json_value_free(tmpv);
    json_free_serialized_string(serial);

    free(title);
    free(author);
    free(isbn);
    free(year);
    free(tmp);
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

void BookInfo(char *res, int *res_len, const char *isbn, const char *ID)
{
    Node *curNode = pHead;
    while(curNode != NULL)
    {
        if(strcmp(curNode->book.ISBN, isbn) == 0)
        {
            JSON_Value *rootVal = json_value_init_object();
            JSON_Object *rootObj = json_value_get_object(rootVal);
            json_object_set_number(rootObj, "res", 1);
            json_object_set_string(rootObj, "msg", "Success");
            json_object_dotset_string(rootObj, "book.isbn", curNode->book.ISBN);
            json_object_dotset_string(rootObj, "book.bookTitle", curNode->book.TITLE);
            json_object_dotset_string(rootObj, "book.author", curNode->book.AUTHOR);
            json_object_dotset_string(rootObj, "book.publishYear", curNode->book.YEAR);
            json_object_dotset_number(rootObj, "book.isAvailable", frontAval(ID, curNode->book.ISBN));
            char *serial = json_serialize_to_string(rootVal);
            strncpy(res, serial, strlen(serial));
            *res_len = strlen(res);
            json_free_serialized_string(serial);
            json_value_free(rootVal);

            return;
        }
        curNode = curNode->pNext;
    }
    strcpy(res, "{\"res\":2,\"msg\":\"Book Not Found\"}");
    return;
}

/*
void searchISBN(char *searchKey) {
    Node    *curNode = pHead;
    while(curNode != NULL) {
        if(strcmp(curNode->book.ISBN, searchKey) == 0) {
            showSingleInfo(&(curNode->book));
        }
        curNode = curNode->pNext;
    }
}
*/

//로그인

int logRespone(const char *ID, const char *HS) {
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

int logRequest(const char *ID, const char *HS) {
    if(strlen(ID) != 10 || strlen(HS) != 64)    return -1;
    int     res = logRespone(ID, HS);
    if(res == 1)       { printf("로그인 성공 | %s님 반갑습니다.\n", ID); }
    else if(res == 2)  { puts("찾을 수 없는 계정입니다. 새로 파일을 만듭니다. 초기 비밀번호는 \"test\"입니다."); addUser(ID, TESTHASH, 0, 0); }
    else if(res == -1) { puts("로그인 실패 | 패스워드가 틀렸습니다!"); }
    else               { puts("로그인 실패 | 알 수 없는 오류입니다. 관리자에게 문의하세요."); }

    return res;
}

void Login(char *res, int *res_len, const char *id, const char *passwd) {
    if(strlen(id) != 10 || strlen(passwd) != 64)    { strcpy(res, "{\"res\":-1,\"msg\":\"Input Error Occured\"}"); *res_len = strlen(res); return; }
    switch (logRespone(id, passwd)) {
    case 1:
        strcpy(res, "{\"res\":1,\"msg\":\"Login Success\"}"); *res_len = strlen(res);
        return;
    case 2:
        strcpy(res, "{\"res\":2,\"msg\":\"Account Not Exist\"}"); *res_len = strlen(res);
        return;
    case -1:
        strcpy(res, "{\"res\":2,\"msg\":\"Password Incorrect\"}"); *res_len = strlen(res); 
        return;
    default:
        strcpy(res, "{\"res\":-1,\"msg\":\"Unknown Error Occured\"}"); *res_len = strlen(res);
        return;
    }
}

void addUser(const char *ID, const char *HASH, int rtNum, int rvNum) {
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

//도서 정보 출력


//대여

void Rental(char *res, int *res_len, const char *ISBN, const char *ID) {
    FILE    *RFP;
    char    buf[256];
    char    *p;
    
    if(isAval(ISBN) == 0) { strcpy(res, "{\"res\":2,\"msg\":\"Already rented by someone\"}"); *res_len = strlen(res); return; }

    RFP = fopen(RTFILE, "a+");
    fprintf(RFP, "%s\t%s\n", ISBN, ID);
    fclose(RFP);
    strcpy(res, "{\"res\":1,\"msg\":\"Rent Successful\"}"); *res_len = strlen(res);
}

void rentBook(char *ID, char *ISBN) {
    FILE    *RFP;
    char    buf[256];
    char    *p;
    //if (searchall(ISBN)) // 기반으로 도서 데이터 유무 확인
    if(isAval(ISBN) == 0) { printf("[%s]은 이미 대출된 도서입니다.\n", ISBN); return; }

    RFP = fopen(RTFILE, "a+");
    fprintf(RFP, "%s\t%s\n", ISBN, ID);
    fclose(RFP);
    p = rentSearch(ISBN).TITLE;
    printf("%s님이 대출하신 책은 다음과 같습니다. %s [%s]\n", ID, p, ISBN);
}

//반납

void Return(char *res, int *res_len, const char *ID, const char *ISBN) {
    FILE    *RFP, *WFP;
    char    buf[256];
    char    *p;
    int     cnt = 0;
    
    if(isAval(ISBN) != 0) { strcpy(res, "{\"res\":2,\"msg\":\"Already returned\"}"); *res_len = strlen(res); return; }
    
    RFP = fopen(RTFILE, "r+t");
    WFP = fopen(RBFILE, "w+t");

    while(feof(RFP) == 0) {
        fgets(buf, sizeof(buf), RFP);
        // 반납하려는 ISBN 서칭
        if(strcmp(ISBN, p = strtok(buf, "\t")) == 0) {  
            // 해당 책을 대출한 사람이 지금의 ID인지 확인
            if(strcmp(ID, p = strtok(NULL, "\n")) == 0) { 

                fseek(RFP, 0, SEEK_SET);
                fseek(WFP, 0, SEEK_SET);
                // 파일 새로 쓰기 rented -> rentBUF
                while(feof(RFP) == 0) {
                    fgets(buf, sizeof(buf), RFP);
                    if(strcmp(ISBN, p = strtok(buf , "\t")) != 0) { 
                        fprintf(WFP, "%s\t", p);    p = strtok(NULL, "\n");
                        fprintf(WFP, "%s\n", p); 
                        }
                }
                strcpy(res, "{\"res\":1,\"msg\":\"Return Successful\"}"); *res_len = strlen(res); return;
            }
            else { strcpy(res, "{\"res\":2,\"msg\":\"You didnt rented this book!\"}"); *res_len = strlen(res); return; }
        }
    }
    fclose(RFP);
    fclose(WFP);

    // 파일 덮어씌우기  RFP -> WFP
    RFP = fopen(RBFILE, "rt");
    WFP = fopen(RTFILE,  "wt");
    
    while(feof(RFP) == 0) {
        cnt = fread(buf, sizeof(char), sizeof(buf), RFP);
        fwrite(buf, sizeof(char), cnt, WFP);
    }

    fclose(RFP);
    fclose(WFP);
}

void returnBook(char *ID, char *ISBN) {
    FILE    *RFP, *WFP;
    char    buf[256];
    char    *p;
    int     cnt = 0;
    
    if(isAval(ISBN) != 0) { printf("[%s]은 이미 반납된 도서입니다.\n", ISBN); return; }
    
    RFP = fopen(RTFILE, "r+t");
    WFP = fopen(RBFILE, "w+t");

    while(feof(RFP) == 0) {
        fgets(buf, sizeof(buf), RFP);
        // 반납하려는 ISBN 서칭
        if(strcmp(ISBN, p = strtok(buf, "\t")) == 0) {  
            // 해당 책을 대출한 사람이 지금의 ID인지 확인
            if(strcmp(ID, p = strtok(NULL, "\n")) == 0) { 

                fseek(RFP, 0, SEEK_SET);
                fseek(WFP, 0, SEEK_SET);
                // 파일 새로 쓰기 rented -> rentBUF
                while(feof(RFP) == 0) {
                    fgets(buf, sizeof(buf), RFP);
                    if(strcmp(ISBN, p = strtok(buf , "\t")) != 0) { 
                        fprintf(WFP, "%s\t", p);    p = strtok(NULL, "\n");
                        fprintf(WFP, "%s\n", p); 
                        }
                }
                printf("%s님은 [%s]을 반납하셨습니다.\n", ID, ISBN);
            }
            else { printf("반납실패 | [%s]은 %s님이 빌린 책이 아닙니다.\n", ISBN, ID); return; }
        }
    }
    fclose(RFP);
    fclose(WFP);

    // 파일 덮어씌우기  RFP -> WFP
    RFP = fopen(RBFILE, "rt");
    WFP = fopen(RTFILE,  "wt");
    
    while(feof(RFP) == 0) {
        cnt = fread(buf, sizeof(char), sizeof(buf), RFP);
        fwrite(buf, sizeof(char), cnt, WFP);
    }

    fclose(RFP);
    fclose(WFP);
}

///

void showInfoMain() {
    Node    *curNode = pHead;

    if(pHead == NULL) {
        puts("현재 메모리에는 할당된 데이터가 없습니다. [-550 : HEAP FREE]");
        return;
    }
    while(curNode != NULL) {
        printf("%s | %s | %s | %s\n", curNode->book.TITLE, curNode->book.AUTHOR, curNode->book.YEAR, curNode->book.ISBN);
        curNode = curNode->pNext;
    }
    puts("");
    printf("%d개의 책 데이터를 로드했습니다.\n", BOOKNUM);
}

void showSingleInfo(Book *_book) {
    puts("");
    printf("책 제목\t\t%s\n",   _book->TITLE);
    printf("책 저자\t\t%s\n",   _book->AUTHOR);
    printf("발행일자\t%s\n",     _book->YEAR);
    printf("ISBN 정보\t%s\n",   _book->ISBN);
    
    //printf("%p",_book);
}

void searchMain() {
    char    searchKey[256];
    printf("검색할 단어를 입력하세요 >> ");
    scanf("\n%[^\n]s", searchKey);

    searchall(searchKey);
    return;
}

int isAval(const char *ISBN) {
    FILE    *RFP;
    char    buf[256];
    char    *p;
    RFP = fopen(RTFILE, "r+t");
    
    while(feof(RFP) == 0) {
        fgets(buf, sizeof(buf), RFP);
        if(strcmp(ISBN, p = strtok(buf, "\t")) == 0)    return  0;
    }
    fclose(RFP);
    return 1;
}

int frontAval(const char *ID, const char *ISBN) {
    FILE    *RFP;
    char    buf[256];
    char    *p;
    RFP = fopen(RTFILE, "rt");
    
    while(fgets(buf, sizeof(buf), RFP) != NULL) {
        if(strcmp(p = strtok(buf, "\t"), ISBN) == 0) {
            if(strncmp(ID, p = strtok(NULL, "\n"), 10) == 0) return 2;
            else    return -1;
        }
    }
    fclose(RFP);
    return 1;
}

Book rentSearch(char *searchKey) {
    Node    *curNode    = pHead;
    char    *title, *author, *isbn, *year, *tmp;
    char    *sptr = NULL;
    int     searchNum = 0;
    Book    sResult[10];

    title   = malloc(sizeof(curNode->book.TITLE));  strncpy(title,curNode->book.TITLE,   sizeof(curNode->book.TITLE));
    author  = malloc(sizeof(curNode->book.AUTHOR)); strncpy(author,curNode->book.AUTHOR, sizeof(curNode->book.AUTHOR));
    isbn    = malloc(sizeof(curNode->book.ISBN));   strncpy(isbn,curNode->book.ISBN,     sizeof(curNode->book.ISBN));
    year    = malloc(sizeof(curNode->book.YEAR));   strncpy(year,curNode->book.YEAR,     sizeof(curNode->book.YEAR));
    tmp     = malloc(sizeof(curNode->book.TITLE) + sizeof(curNode->book.AUTHOR) + sizeof(curNode->book.ISBN) + sizeof(curNode->book.YEAR));

    while(curNode != NULL) {
        sprintf(tmp, "%s %s %s %s", curNode->book.TITLE, curNode->book.AUTHOR, curNode->book.ISBN, curNode->book.YEAR);

        if(strcmp(title, searchKey) == 0) {
            if(searchNum < 10) {
                strncpy(sResult[searchNum].TITLE, curNode->book.TITLE,      sizeof(curNode->book.TITLE));
                strncpy(sResult[searchNum].AUTHOR, curNode->book.AUTHOR,    sizeof(curNode->book.AUTHOR));
                strncpy(sResult[searchNum].ISBN, curNode->book.ISBN,        sizeof(curNode->book.ISBN));
                strncpy(sResult[searchNum].YEAR, curNode->book.YEAR,        sizeof(curNode->book.YEAR));
            }
            //showSingleInfo(&(curNode->book));
            searchNum++;
            curNode = curNode->pNext;
            continue;
        }

        sptr = strtok(tmp, ",\t ");

        while(sptr != NULL) {
            if(strcmp(sptr, searchKey) == 0) {
                if(searchNum < 10) {
                    strncpy(sResult[searchNum].TITLE, curNode->book.TITLE,      sizeof(curNode->book.TITLE));
                    strncpy(sResult[searchNum].AUTHOR, curNode->book.AUTHOR,    sizeof(curNode->book.AUTHOR));
                    strncpy(sResult[searchNum].ISBN, curNode->book.ISBN,        sizeof(curNode->book.ISBN));
                    strncpy(sResult[searchNum].YEAR, curNode->book.YEAR,        sizeof(curNode->book.YEAR));
                }
                //showSingleInfo(&(curNode->book));
                searchNum++;
                break;
            }
            sptr = strtok(NULL,",\t ");
        }
        curNode = curNode->pNext;
    }
    free(title);
    free(author);
    free(isbn);
    free(year);
    free(tmp);

    if(searchNum == 0) { strcpy(sResult[1].ISBN, "0"); return sResult[1]; }
    return sResult[0];
}

void rentBookMain(char *ID) {
    char    TITLE[100] = { "" };
    char    rentKey[256] = { "" };
    char    *pISBN = NULL;
    printf("대출하실 책을 입력하세요 >> ");
    scanf("\n%[^\n]s", rentKey);

    fflush(stdin);
    pISBN = rentSearch(rentKey).ISBN;
    if(pISBN == NULL || strncmp(pISBN, "0", 1) == 0) { puts("도서 목록에 없는 책입니다."); return; }
    else    rentBook(ID, pISBN);
}

void returnBookMain(char *ID) {
    char    buf[256];
    char    *pISBN;
    printf("반납하려는 책 >> ");
    scanf("\n%[^\n]s", buf);

    pISBN = rentSearch(buf).ISBN;
    //pISBN[strlen(pISBN) -1] = '\0';
    
    returnBook(ID, pISBN);
}

void RentInfoMain(char *ID) {
    FILE    *RFP;
    char    buf[256];
    char    curID[12];
    char    *p, *p1;
    int     cnt = 0;

    strncpy(curID, ID, 10);

    RFP = fopen(RTFILE, "r");
    fseek(RFP, 0, SEEK_SET);
    while(fgets(buf, sizeof(buf), RFP) != NULL) {
        p = strtok(buf,  "\t");
        if(strncmp(curID, p1 = strtok(NULL, "\n"), 10) == 0) { cnt++; printf("%d번째 대출 중인 책 %s [%s]\n", cnt, rentSearch(p).TITLE, p); }
        
    }
    fclose(RFP);

    printf("현재 대출 중인 권수 [%d]\n", cnt);
}

void menu(char *ID) {
    char    ip[256];
    int     ipN;

    puts("\n자료구조론 도서대출 시스템(CUI ver.)\n");
    printf("1. 도서 목록\t2. 도서 검색\n");
    printf("3. 도서 대출\t4. 도서 반납\n");
    printf("5. 대출 목록\t0. 종료\n");
    printf("\n서비스 항목을 고르세요 >> ");
    scanf("\n%[^\n]s", ip);   ipN = atoi(ip);

    switch(ipN) {
    case 0:     return;
    case 1:     showInfoMain();     break;
    case 2:     searchMain();       break;
    case 3:     rentBookMain(ID);   break;
    case 4:     returnBookMain(ID); break;
    case 5:     RentInfoMain(ID);   break;
    default:    puts("잘못 입력하셨습니다"); break;
    }

    freeNodes();
}
/*
int tcpListen() {
    int     serv_sock;
    int     clnt_sock;
   
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    puts("Starting TCP Socket...");
   
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); 
    if(serv_sock == -1) puts("Socket Error");
    
    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_addr.s_addr   = htonl(INADDR_ANY);
    serv_addr.sin_port          = htons(atoi("8080"));
    
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) puts("Bind Error");
    if(listen(serv_sock, 5) == -1) puts("Listen Error");

    clnt_addr_size = sizeof(clnt_addr);

    JSON_Value *rootVal;
    JSON_Object *rootObj;
    JSON_Object *reqObj;

    char buf[2048];
    int buf_len;

    char res[2048];
    int res_len;

    while (1)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
        if(clnt_sock == -1) puts("Accept Error");

        puts("Client Connected");

        memset(buf, 0, sizeof(buf));
        memset(res, 0, sizeof(res));

        puts("pos0");

        buf_len = read(clnt_sock, buf, sizeof(buf));
        if(buf_len == -1) puts("Read Error");

        puts(buf);

        puts("pos1");
        rootVal = json_parse_string(buf);
        puts("pos2");
        rootObj = json_value_get_object(rootVal);
        puts("pos3");
        reqObj = json_object_get_object(rootObj, "req");


        switch((int)json_object_get_number(rootObj, "reqType"))
        {
            case 1: Login(res, &res_len, json_object_get_string(reqObj, "id"), json_object_get_string(reqObj, "passwd")); break; //It's Login Request
            case 3: BookInfo(res, &res_len, json_object_get_string(reqObj, "isbn"), json_object_get_string(reqObj, "id")); break; //It's Book Request
            case 5: BookList(res, &res_len, json_object_get_string(reqObj, "query"), json_object_get_string(reqObj, "id")); break; //It's Book List Request
            case 7: Rental(res, &res_len, json_object_get_string(reqObj, "isbn"), json_object_get_string(reqObj, "id")); break; //It's Book rental Request
            case 9: Return(res, &res_len, json_object_get_string(reqObj, "isbn"), json_object_get_string(reqObj, "id")); break; //It's Book return Request
            //case 11: RentalList(res, &res_len, json_object_get_string(reqObj,"id")); break;
            default: strcpy(res, "{\"res\":-1,\"msg\":\"Unknown Request\"}"); res_len = strlen(res);
        }
        json_value_free(rootVal);
        puts(res);
        write(clnt_sock, res, res_len);
    }
    close(clnt_sock);
    close(serv_sock);
    
    return 0;
}
*/

int main(int argc, char* argv[]) {
    //char    curID[11] = "2021270131";
    //char    curHS[65] = "4888400e1fbc18408be8469b244be413b012f14c8080403f465447fab1a33d59";
    loadFile(BOOKNUM);
    //if(logRequest(curID, curHS) != 1) return 0;
    //else    menu(curID);
    return tcpListen();
}