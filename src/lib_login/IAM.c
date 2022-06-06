#include <stdio.h>
#include <string.h>
#include "parson.h"
#include "IAM.h"

void addUser(double ID, double PW)
{
	JSON_Value *rootValue = json_parse_file("userSample.json");
	JSON_Object *rootObject = json_value_get_object(rootValue);

	// memset(ID_encrpyt, 0, sizeof(ID_encrpyt));
	// memset(PW_encrpyt, 0, sizeof(PW_encrpyt));

	// read(0, ID, 12);//ID는 일단 학번으로 생각해서 10자리 예상
	// read(0, PW, 12);//최대 12자리까지만 가능하도록 예상

	// SHA256_Encrpyt(ID, strlen(ID), ID_encrpyt);
	// SHA256_Encrpyt(PW, strlen(PW), PW_encrpyt);

	// json_object_set_string(rootObject, "Title", "Account");
	json_object_set_number(rootObject, "ID", ID);
	json_object_set_number(rootObject, "hash", PW);

	json_object_set_value(rootObject, "rent", json_value_init_array());
	JSON_Array *rent = json_object_get_array(rootObject, "rent");
	json_object_set_value(rootObject, "waiting", json_value_init_array());
	JSON_Array *waiting = json_object_get_array(rootObject, "waiting");
	json_array_append_string(rent, "book1");
	json_array_append_string(waiting, "wait_book1");

	json_serialize_to_file_pretty(rootValue, "userSample.json");
	json_value_free(rootValue);
}

void delUser(double ID); // 사용자 탈퇴 OR 사용자 자격 박탈
void delUser(double ID)
{

	JSON_Value *rootValue = json_parse_file("userSample.json");
	JSON_Object *rootObject = json_value_get_object(rootValue);
}
void prtUser(); // 사용자 정보 출력 (대출 권수, 대출 목록)
void prtUser()
{

	JSON_Value *rootValue = json_parse_file("userSample.json");
	JSON_Object *rootObject = json_value_get_object(rootValue);

	json_object_get_value(rootObject, "rent");
	JSON_Array *rent = json_object_get_array(rootObject, "rent");
	json_object_get_value(rootObject, "waiting");
	JSON_Array *waiting = json_object_get_array(rootObject, "waiting");
	json_array_append_string(rent, "book1");
	json_array_append_string(waiting, "wait_book1");

	double Id = json_object_get_number(rootObject, "ID");
	double Pw = json_object_get_number(rootObject, "hash");

	printf("ID : %lf\n", Id);
	printf("Pw : %lf\n", Pw);

	json_serialize_to_file_pretty(rootValue, "userSample.json");
	json_value_free(rootValue);
}
/*          Indentification & Authentication        */
void logUser();			// 사용자 로그인 기능 함수
unsigned int getUser(); // 사용자 정보 가져오기
