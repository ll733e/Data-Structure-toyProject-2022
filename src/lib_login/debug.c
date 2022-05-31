#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "..//lib_json//parson.h"

void add_user(char* ID, char* PW){
	//char ID_encrpyt[10];
	char PW_encrpyt[12];

    JSON_Value *rootValue;
    JSON_Object *rootObject;
	rootValue = json_parse_file("account.json");
	rootObject = json_value_get_object(rootValue);

	//memset(ID_encrpyt, 0, sizeof(ID_encrpyt));
	memset(PW_encrpyt, 0, sizeof(PW_encrpyt));

	//read(0, ID, 12);//ID는 일단 학번으로 생각해서 10자리 예상
	//read(0, PW, 12);//최대 12자리까지만 가능하도록 예상
    scanf("%s", &ID);
    scanf("%s", &PW);

	//SHA256_Encrpyt(ID, strlen(ID), ID_encrpyt);
	//SHA256_Encrpyt(PW, strlen(PW), PW_encrpyt);

	json_object_set_string(rootObject, "Title", "Account");
	json_object_set_string(rootObject, "ID", ID);
	json_object_set_string(rootObject, "PW", PW_encrpyt);

	json_serialize_to_file_pretty(rootValue, "account.json");
	json_value_free(rootValue);
}

void check(char* ID, char* PW){
	//if(ID==NULL) retrun -1;
}

void del_user(char* ID, char* PW){
	//remove(ID.json);
}

int main() {
	char id[20] = "AAAA";
	char pw[20] = "BBBB";

	add_user(id, pw);
}
