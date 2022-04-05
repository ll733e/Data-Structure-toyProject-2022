#include <stdio.h>
#include "parson.h"    // parson.h 헤더 파일 포함

int main()
{
    JSON_Value      *rootValue;
    JSON_Object     *rootObject;    
    char            *filename       = "book1";
    char            buf[256];
    /* 초기화 */
    sprintf(buf, "../../data/book/%s.json", filename);
    rootValue = json_parse_file(buf);      // JSON 파일을 읽어서 파싱
    rootObject = json_value_get_object(rootValue);    // JSON_Value에서 JSON_Object를 얻음
    
    /* 사용 */
    // 객체에서 키에 해당하는 문자열을 가져옴
    printf("Title: %s\n", json_object_get_string(rootObject, "Title"));
    printf("Year: %d\n", (int)json_object_get_number(rootObject, "Year"));
    printf("Actors:\n");
    JSON_Array *array = json_object_get_array(rootObject, "Actors");
    for (int i = 0; i < json_array_get_count(array); i++)     // 배열의 요소 개수만큼 반복
    {
        printf("  %s\n", json_array_get_string(array, i));
    }
    printf("ISBN: %s\n", json_object_get_string(rootObject, "ISBN"));

    /* 해제 */
    json_value_free(rootValue);    // JSON_Value에 할당된 동적 메모리 해제
    return 0;
}