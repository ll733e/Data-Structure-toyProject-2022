#include <stdio.h>
#include <string.h>
#include "parson.h"

void addUser(int ID, int PW);
void delUser(double ID);
void prtUser();
unsigned int getUser();
void rent();
void waiting();

/* setinit 함수로 학생 인원수 파악 가능 */
/* adduser에서 학생 인원수 파악후 번호 매김 */

int setinit() {
	JSON_Value *read_setting_value;
	JSON_Object *read_setting;
	JSON_Value *write_setting_value;
	JSON_Object *write_setting;
	int account_size = 0;


	read_setting_value = json_parse_file("user/setting.json");
	read_setting = json_value_get_object(read_setting_value);
	write_setting_value = json_value_init_object();
	write_setting = json_value_get_object(write_setting_value);

	account_size = json_object_get_number(read_setting, "Account_size");
	/*
	if(!account_size) {
		json_object_set_number(write_setting, "Account_size", 0);
		goto EXIT;
	}
	*/

	json_object_set_number(write_setting, "Account_size", account_size+1);
	goto EXIT;

	EXIT:
	json_serialize_to_file_pretty(write_setting_value, "user/setting.json");
   	json_value_free(write_setting_value);
	json_value_free(read_setting_value);
	return account_size;
}

void addUser(int ID, int PW) {
   	JSON_Value *write_value;
   	JSON_Object *write;
	JSON_Value *read_value;
	JSON_Object *read;
	JSON_Array *waiting = NULL;
	JSON_Array *rent = NULL;

	int num = 0;
	char name[128] = {0, };

	num = setinit();
   	write_value = json_value_init_object();
   	write = json_value_get_object(write_value);

   	json_object_set_number(write, "ID", ID);
   	json_object_set_number(write, "hash", PW);
	json_object_set_number(write, "num", num);

	json_object_set_value(write, "waiting", json_value_init_array());
   	waiting = json_object_get_array(write, "waiting");
   	json_array_append_string(rent, "book1");

	json_object_set_value(write, "rent", json_value_init_array());
        waiting = json_object_get_array(write, "rent");
        json_array_append_string(rent, "rent1");

	sprintf(name, "user/%d-%d.json", ID, num);
   	json_serialize_to_file_pretty(write_value, name);
   	json_value_free(write_value);
}

int main () {
   	addUser(2021271, 14124523);
}