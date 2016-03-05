#include<winsock.h>
#include<stdio.h>

main()
{
	SOCKADDR_IN a;
	SOCKADDR b;
	
	printf("sockaddr_in %d\n",sizeof(a));
	printf("sockaddr %d\n",sizeof(b));
	
}
