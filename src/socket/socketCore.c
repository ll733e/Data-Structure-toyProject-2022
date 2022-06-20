#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int tcpListen(int argc, char* argv[]) {
    int     serv_sock;
    int     clnt_sock;
   
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
   
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); 
    if(serv_sock == -1) puts("Socket Error");
    
    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_addr.s_addr   = htonl(INADDR_ANY);
    serv_addr.sin_port          = htons(atoi(8888));
    
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) puts("Bind Error");
    if(listen(serv_sock, 5) == -1) puts("Listen Error");

    clnt_addr_size = sizeof(clnt_addr);

    char buf[2048];
    int buf_len;

    while (1)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
        if(clnt_sock == -1) puts("Accept Error");
        memset(buf, 0, sizeof(buf));
        buf_len = read(serv_sock, buf, sizeof(buf)-1);
        if(buf_len == -1) puts("Read Error");

        //Do somthing Here

        write(clnt_sock, res, sizeof(res));
    }
    close(clnt_sock);
    close(serv_sock);
    
    return 0;
}