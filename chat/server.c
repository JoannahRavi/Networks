#include<windows.h>
#include<winsock.h>
#include<stdio.h>
#include<pthread.h>

#define SOCK_ERROR -2
SOCKET commsock;
SOCKADDR_IN from;

void *recv_msg(void *arg)
{
	int ret;
	do
	{
		
		char recvbuff[256]="",sendbuff[256];
		ret = recv(commsock,recvbuff,256,0);
		if(ret>0)
		printf("%s\n",recvbuff);
		else if(ret == 0)
		printf("[*] -> Connection closed.\n");
		else if(ret < 0)
		printf("[X] -> Error in recveving.\n");
		
		memset(recvbuff, 0, sizeof(recvbuff));
		
	}while(ret>0);
}

void *send_msg(void *arg)
{
	printf("hello");
	char sendbuffer[256] = "From client: hello how r u";
	int ret;
	int fromlen=sizeof(from);
	while(1)
	{	
	ret = sendto(commsock,sendbuffer,strlen(sendbuffer),0,(struct sockaddr*)&from,fromlen);
	if(ret == SOCKET_ERROR)
	{
		printf("Could not send bytes to server");
		WSACleanup();
		
	}
	scanf("%s",&sendbuffer);
	}
}

int _stdcall WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdshow)
{
	WSADATA ws;
	int ret;
	
	WSAStartup(0x0202,&ws);
	
	SOCKET lsnSock;
	lsnSock = socket(AF_INET,SOCK_STREAM,6);
	if(lsnSock == -1)
	{
		printf("[X] -> Could not create Listening Socket.\n");
		WSACleanup();
		return SOCK_ERROR;
	}
	else
	{
		printf("[*] -> Socket created.\n");
	}
	
	SOCKADDR_IN srvInfo;
	srvInfo.sin_family = AF_INET;
	srvInfo.sin_addr.s_addr = inet_addr("192.168.2.101");
	srvInfo.sin_port = htons(10001);
	
	ret = bind(lsnSock,(SOCKADDR *)&srvInfo,sizeof(srvInfo));
	if(ret == INVALID_SOCKET)
	{
		printf("[X] -> Could not bind to the socket.\n");
		WSACleanup();
		return SOCK_ERROR;
	}
	else
	{
		printf("[*] -> binded to the socket.\n");	
	}
	
	ret = listen(lsnSock,10);
	if(ret == INVALID_SOCKET)
	{
		printf("[X] -> Could not listen");
		WSACleanup();
		return SOCK_ERROR;
	}
	else
	printf("[*] -> Listening");
	
	int fromlen = sizeof(from);
	commsock = accept(lsnSock,(struct sockaddr*)&from,&fromlen);
	if(commsock == INVALID_SOCKET)
	{
		printf("[X] -> Unable to accept connection.\n");
		WSACleanup();
		return SOCK_ERROR;
	}
	else
	{
		printf("[*] -> Connection accepted.\n");
	}
	
	
	
	pthread_t recv,send;
	
	pthread_create(&recv,NULL,recv_msg,(void *)1);
	pthread_create(&send,NULL,send_msg,(void *)1);
	pthread_join(send,NULL);
	pthread_join(recv,NULL);
	

	
	
	WSACleanup();
	return 0;
}
