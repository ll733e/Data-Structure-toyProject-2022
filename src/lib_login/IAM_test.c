#include <stdio.h>
#include <string.h>
#include "parson.h"

#define ADD_RENT 1
#define DEL_RENT 2

void addUser(int ID, int PW);
void delUser(int ID);
void prtUser();
unsigned int getUser();
void rent(int cmd, int ID, char bookname[128]);
void waiting(int time);

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

	if(!account_size) {
		json_object_set_number(write_setting, "Account_size", 1);
		goto EXIT;
	}


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
	JSON_Array *append_object = NULL;

	int num = 0;
	char name[128] = {0, };

	num = setinit();
   	write_value = json_value_init_object();
   	write = json_value_get_object(write_value);

   	json_object_set_number(write, "ID", ID);
   	json_object_set_number(write, "hash", PW);
	json_object_set_number(write, "num", num);

	json_object_set_value(write, "waiting", json_value_init_array());
   	append_object = json_object_get_array(write, "waiting");

	json_object_set_value(write, "rent", json_value_init_array());
        append_object = json_object_get_array(write, "rent");

	sprintf(name, "user/%d.json", ID);
   	json_serialize_to_file_pretty(write_value, name);
   	json_value_free(write_value);
}

void delUser(int id) {
	char name[128] = {0, };

	sprintf(name, "user/%d.json", id);
	remove(name);
}

void rent(int cmd, int ID, char bookname[128]) {
	int idx = 0;
	char name[128] = {0, };
	JSON_Array *append_object = NULL;
	JSON_Value *write_value;
        JSON_Object *write;
        JSON_Value *read_value;
        JSON_Object *read;

	write_value = json_value_init_object();
        write = json_value_get_object(write_value);
	sprintf(name, "user/%d.json", ID);
	read_value = json_parse_file(name);
	read = json_value_get_object(read_value);

	if(cmd == ADD_RENT) {
		append_object = json_object_get_array(read, "rent");
		json_array_append_string(append_object, bookname);

	}
	else if(cmd == DEL_RENT) {
		append_object = json_object_get_array(read, "rent");
		for (idx = 0; idx < json_array_get_count(append_object); idx++) {
        		if(strcmp(bookname, json_array_get_string(append_object, idx)) == 0) {
				json_array_remove(append_object, idx);
				break;
			}
    		}
	}
	else {
		printf("Not command");
		return;
	}

	json_serialize_to_file_pretty(read_value, name);
        json_value_free(read_value);
}


int main () {
   	addUser(2021272, 14124523);
	rent(1, 2021272, "test!!");
	rent(1, 2021272, "test2!!");
	rent(2, 2021272, "test!!");
}
