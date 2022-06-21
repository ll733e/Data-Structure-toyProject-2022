#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "socketCore.h"
#include "../json/parson.h"

int tcpListen(int argc, char* argv[]) {
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
            case 1: Login(res, &res_len, json_object_string(reqObj, "id"), json_object_get_string(reqObj, "passwd")); break; //It's Login Request
            case 3: BookInfo(res, &res_len, json_object_string(reqObj, "isbn"), json_object_string(reqObj, "id")); break; //It's Book Request
            case 5: BookList(res, &res_len, json_object_get_string(reqObj, "query"), (int)json_object_get_number(reqObj, "id")); break; //It's Book List Request
            case 7: Rental(res, &res_len, json_object_get_string(reqObj, "isbn"), json_object_get_string(reqObj, "id")); break; //It's Book rental Request
            case 9: Return(res, &res_len, json_object_get_string(reqObj, "isbn"), json_object_get_string(reqObj, "id")); break; //It's Book return Request
            case 11: RentalList(res, &res_len, json_object_get_string(reqObj,"id")); break;
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