#include<stdio.h>
#include<winsock2.h>
int main()
{
WSADATA wsa;
if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
{
printf("no\n");
}
else
{
printf("yes\n");
}
return 0;
}