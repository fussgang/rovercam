#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>

extern int sock, conn;

void
initsock()
{
	struct sockaddr_in addr;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1){
		perror("socket");
		exit(-1);
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.0.18");
	addr.sin_port = htons(15000);

	if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0){
		perror("connect");
		exit(-1);
	}
}