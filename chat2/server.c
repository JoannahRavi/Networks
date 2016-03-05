#include<stdio.h>
#include<winsock2.h>
#include<windows.h>

int _stdcall WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdshow)
{
	WSADATA ws;
	WSAStartup(0x0202,&ws);
	
	SOCKET L_socket;
	L_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	WSACleanup();
	return 0;
}
