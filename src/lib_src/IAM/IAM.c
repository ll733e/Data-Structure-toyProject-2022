#include <stdio.h>
#include <string.h>
#include <../JSON/parson.h>
#include "IAM.h"

void addUser(char* ID, char* PW) {
/*
	JSON_Value		*rootValue = json_parse_file("account.json");
	JSON_Object 	*rootObject = json_value_get_object(rootValue);

	//memset(ID_encrpyt, 0, sizeof(ID_encrpyt));
	//memset(PW_encrpyt, 0, sizeof(PW_encrpyt));

	read(0, ID, 12);//ID는 일단 학번으로 생각해서 10자리 예상
	read(0, PW, 12);//최대 12자리까지만 가능하도록 예상

	//SHA256_Encrpyt(ID, strlen(ID), ID_encrpyt);
	//SHA256_Encrpyt(PW, strlen(PW), PW_encrpyt);

	json_object_set_string(rootObject, "Title", "Account");
	json_object_set_string(rootObject, "ID", ID);

	json_serialize_to_file_pretty(rootValue, "account.json");
	json_value_free(rootValue);

	*/
}
void            delUser();      // 사용자 탈퇴 OR 사용자 자격 박탈
void            prtUser();      // 사용자 정보 출력 (대출 권수, 대출 목록)

/*          Indentification & Authentication        */
void            logUser();      // 사용자 로그인 기능 함수
unsigned int    getUser();      // 사용자 정보 가져오기