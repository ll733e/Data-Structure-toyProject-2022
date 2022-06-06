#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"
#include "..//lib_type//types.h"


int countFile() {
    FILE*   RFP;
    char    line[200];
    int     tolnum = 0;

    RFP = fopen(oriFILE, "rt");
    if(RFP == NULL) { puts("데이터 파일이 없습니다."); exit(1); }
    fgets(line, sizeof(line), RFP);
    tolnum = atoi(line);
    
    while(!feof(RFP)) {
        fgets(line, sizeof(line), RFP);
        tolnum++;
    }
    fclose(RFP);

    return tolnum;
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
    char    line[256];
    int     lenSTR;             // 길이 카운터의 버퍼 길이
    int     curNum  = 0;
    char    *str    = NULL;

    RFP = fopen(oriFILE, "r+t");
    if(RFP == NULL) { puts("데이터 파일이 없습니다."); exit(1); }

    //while(!feof(RFP))

    for(int i = 0 ; i < tolnum - 13 ; i++) {
        fgets(line, sizeof(line), RFP);
        str = strtok(line, "\t\t\t\n");
        deleteEndString(str);     
        
        while(str != NULL) {
            deleteEndString(str);
            printf("%s\n", str);
            str = strtok(NULL, "\t\t\t\n");
        }
        puts("");
    }

    fclose(RFP);
}

int main() {
    int     dataNum = countFile();
    loadFile(dataNum); // 리드
    //freeAllNode();         // 죽여!
    
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