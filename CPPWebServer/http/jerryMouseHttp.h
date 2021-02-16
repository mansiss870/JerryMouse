#include<iostream>
using namespace std;
class Response
{

friend Request ;
}
class Request
{
private :
Response response;
string requestUrl;
string requestType;
string reqeustBuffer;
int requestSize;
Response response;
SOCKET clientSocket;
public :
Request(SOCKET clientSocket)
{
this->clientSocket=clientSocket;
}
Response getResponse()
{
Response response(this->clientSocket);
return response;
};
class Response
{
private:
SOCKET clientSocket;
Response(SOCKET clientSocket)
{
this->clientSocket=clientSocket
}
public:
void sendHeader(int responseCode , string mimeType)
{
}
bool write(File *f)
{
}
bool write(string s)
{
}
};
class Session
{
};


/*
char requestBuffer[4096]={0},requestType[10]={0},requestValue[1024]={0};
requestSize=recv(client_socket,requestBuffer,sizeof(requestBuffer),0);
sscanf(requestBuffer,"%s %s ",&requestType,&requestValue);
string requestUrl(requestValue);
char buffer[1024] = {0};
int len;
send(client_socket,"HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n",strlen("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n"), 0);
int result=0;
while((result=fread(buffer,1,1024,f)) > 0)
{
send(client_socket, buffer, result, 0);
if(len == SOCKET_ERROR) 
{
printf("Error sending data, reconnecting...\n");
closesocket(client_socket);
return NULL;
}
else
{
if(!len)
{
printf("Client closed connection\n");
closesocket(client_socket);
return NULL;
}
}
}//while ends
fclose(f);
}
else
{
send(client_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n", 57, 0);
cout<<"Not Found : default\\index.html"<<endl;
return NULL;
}
}// 
*/