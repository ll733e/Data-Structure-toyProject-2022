#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"

int  isAval(char *ISBN) {
    FILE    *RFP;
    char    buf[256];
    char    *p;
    RFP = fopen("..//..//data//book//rented.dat", "r+t");
    
    while(feof(RFP) == 0) {
        fgets(buf, sizeof(buf), RFP);
        if(strcmp(ISBN, p = strtok(buf, "\t")) == 0)    return  0;
    }

    fclose(RFP);

    return 1;
}

void rentBook(char *ID, char *ISBN) {
    FILE    *RFP;
    char    buf[256];
    char    *p;
    
    if(isAval(ISBN) == 0) { printf("[%s]은 이미 대출된 도서입니다.\n", ISBN); return; }

    RFP = fopen("..//..//data//book//rented.dat", "a+");
    fprintf(RFP, "%s\t%s\n", ISBN, ID);
    fclose(RFP);   
    printf("%s님은 %s을 대출하셨습니다.\n", ID, ISBN);
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

int main() {
    //rentBook("2021270131", "978-89-374-1449-7");
    returnBook("2021270131", "978-89-374-1449-7");
}