#include<windows.h>
#include<winsock2.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>

char sendbuffer[256] = "Hi!";
char recvbuffer[256];
SOCKET commsocket;
int nret;

void *recv_msg(void *arg)
{
	while(1)
	{
		nret = recv(commsocket,recvbuffer,256,0);
		if(nret == SOCKET_ERROR)
		{
			printf("could not recv from server");
			WSACleanup();
			break;
		}
		else
		{
			printf("Server - %s\n",recvbuffer);
			memset(recvbuffer, 0, sizeof(recvbuffer));
		}
	}
}

void *send_msg(void *arg)
{
	while(1)
	{	
		nret = send(commsocket,sendbuffer,strlen(sendbuffer),0);
		if(nret == SOCKET_ERROR)
		{
			printf("Could not send bytes to server");
			WSACleanup();
			break;
		}
		gets(sendbuffer);
	}
}

int main()
{
	system("Color 0e");
	WSADATA ws;
	int nret;
	char server_ip[20];
	
	//initialize winsock
	WSAStartup(0x0202,&ws);
	
	
	commsocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if( commsocket == INVALID_SOCKET)
	{
		printf("Could not create common socket");
		WSACleanup();
		return 1;
	}
	
	printf("Server IP : ");
	scanf("%s",&server_ip);
	//fill a sockaddr_in struct with address information of server
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = inet_addr(server_ip);
	serverInfo.sin_port = htons(10001);
	
	nret = connect(commsocket,(struct sockaddr*)&serverInfo,sizeof(struct sockaddr));
	if(nret == SOCKET_ERROR)
	{
		printf("Could not connect to server");
		WSACleanup();
		return 2;
	}
	
	pthread_t send,recv;
	
	pthread_create(&send,NULL,send_msg,(void *)1);
	pthread_create(&recv,NULL,recv_msg,(void *)1);
	pthread_join(send,NULL);
	pthread_join(recv,NULL);
	
	getch();
	WSACleanup();
	return 0;
	
}
