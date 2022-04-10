#define _CRT_SECURE_NO_WARNINGS    // fopen 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>     // 파일 처리 함수가 선언된 헤더 파일

int main()
{
    // JSON 문서에 저장할 데이터
    char    *title      = "혼자 공부하는 머신러닝+딥러닝";
    int     year        = 2020;
    char    Author[][30] = {
        "박혜선"
    };
    char    *isbn       = "9791162243664";

    FILE *fp = fopen("book1.json", "w");    // 쓰기 모드로 파일 열기

    // JSON 문법에 맞춰서 fprintf 함수로 값 출력
    fprintf(fp, "{\n");
    fprintf(fp, "   \"Title\": \"%s\",\n", title);
    fprintf(fp, "   \"Year\": %d,\n", year);
    fprintf(fp, "   \"Author\": [\n");
    fprintf(fp, "       \"%s\" \n", Author[0]);
    fprintf(fp, "   ],\n");
    fprintf(fp, "   \"ISBN\": \"%s\"\n", isbn);
    fprintf(fp, "}\n");

    fclose(fp);    // 파일 닫기

    return 0;
}