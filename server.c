#include<windows.h>
#include<winsock2.h>
#include<stdio.h>
#include<string.h>

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdshow)
{
	WSADATA ws;
	int nret;
	
	WSAStartup(0x0202,&ws);
	SOCKET listeningSocket;
	
	listeningSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(listeningSocket == INVALID_SOCKET)
	{
		printf("Could not create listening socket\n");
		WSACleanup();
		return 1;
	}
	
	//use a sockaddr_in struct to fill in address information
	SOCKADDR_IN serverInfo;
	
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverInfo.sin_port = htons(10001);
	
	//bind the socket to our local server address
	nret = bind(listeningSocket,(SOCKADDR*)&serverInfo,sizeof(struct sockaddr));
	if(nret == SOCKET_ERROR)
	{
		printf("Could not bind listening socket\n");
		WSACleanup();
		return 2;
	}
	
	//make the socket listen.Up to 10 connections may wait at any one time
	nret = listen(listeningSocket,5);
	if(nret == SOCKET_ERROR)
	{
		printf("%d %ld ",nret,WSAGetLastError());
		printf("Could not listen\n");
		WSACleanup();
		return 3;
	}
	
	//wait for a client
	SOCKET commsocket;

	commsocket = accept(listeningSocket,NULL,NULL);
	
	if(commsocket == INVALID_SOCKET)
	{
		printf("Could not accept connection request");
		WSACleanup();
		return 4;
	}
	
	char sendbuffer[256] = "from server: hi there";
	char recvbuffer[256];
		
	nret = recv(commsocket,recvbuffer,255,0);
	recvbuffer[nret] = 0;
	gets(sendbuffer);
	nret = send(commsocket,sendbuffer,255,0);
	printf("%s",recvbuffer);
	
	closesocket(commsocket);
	closesocket(listeningSocket);
	
	getch();		
	WSACleanup();

	return 0;
}
