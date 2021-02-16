#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

#include <winsock2.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>  
#include <vector>
#include <cstdio>
#include <string>
#include <unordered_map>

#include "utils/queue.h"
#include "utils/mimetype.h"

#include "eg1.h"
using namespace std;


vector<string> split(string str, string delimiter)
{
vector<string> arr;
auto start=0;
auto end=str.find(delimiter);
while(end!=string::npos)
{
arr.push_back(str.substr(start,end-start));
start=end+delimiter.length();
end=str.find(delimiter,start);
}
arr.push_back(str.substr(start,end));
return arr;
}

string join(vector<string> arr , string delimiter)
{

string result="";
for(int i = 0 ; i  < arr.size() ;i++)
{
if(arr[i] == "") continue;
result+=arr[i];
result+=delimiter;
}
return result.substr(0,result.size()-delimiter.size());
}

//framework 
class Request
{
private:
char requestBuffer[7168]={0};
char requestType[10]={0};
char requestUrl[4096]={0};
int requestSize=0;
SOCKET clientSocket;
public:
Request(SOCKET clientSocket)
{
this->clientSocket=clientSocket;
this->requestSize=recv(this->clientSocket,this->requestBuffer,sizeof(this->requestBuffer),0);
sscanf(this->requestBuffer,"%s %s ",&(this->requestType),&(this->requestUrl));
}
int getSize()
{
return this->requestSize;
}
string getType()
{
return string(this->requestType);
}
string getBuffer()
{
return string(this->requestBuffer);
}
string getRequestUrl()
{
return string(this->requestUrl);
}
void close()
{
closesocket(clientSocket);
}
};

class Response
{
private:
SOCKET clientSocket;
public:
Response(SOCKET clientSocket)
{
this->clientSocket=clientSocket;
}
bool sendHeader(int responseCode , string mimeType)
{
string h;
if(responseCode == 200)
{
h="HTTP/1.1 200 OK\r\nContent-Type:"+ mimeType +"; charset=UTF-8\r\n\r\n Set-Cookie: key=value; Max-Age=3600; Secure; Path=/index.html; \r\n";
cout<<h<<endl;
send(clientSocket,h.c_str(),strlen(h.c_str()), 0);
return true;
}
if(responseCode == 500)
{
h="HTTP/1.1 500 INTERNAL SERVER ERROR\r\nContent-Type:"+ mimeType +"; charset=UTF-8\r\n\r\n";
send(clientSocket,h.c_str(),strlen(h.c_str()), 0);
return true;
}
if(responseCode == 404)
{
h="HTTP/1.1 404 NOT FOUND\r\nContent-Type:"+ mimeType +"; charset=UTF-8\r\n\r\n";
send(clientSocket,h.c_str(),strlen(h.c_str()), 0);
return true;
}
return false;
}

void write(FILE *f)
{
char buffer[1024] = {0};
int len=0;
int result=0;
while((result=fread(buffer,1,1024,f)) > 0)
{
len=send(clientSocket, buffer, result, 0);
if(len == SOCKET_ERROR) 
{
return ;
}
else if(!len)
{
return ;
}
}

}

bool write(string s)
{
int len=0;
len=send(clientSocket, s.c_str(), strlen(s.c_str()), 0);
if(len == SOCKET_ERROR) 
{
return false;
}
return true;
}

};

class Session
{
};

class Service 
{
public:
virtual void processGetService(Request * request , Response * response)=0;
virtual void processPostService(Request * request , Response * response)=0;
};
class GetService : public Service 
{
public:
void processPostService(Request * request , Response * response)
{
cout<<"Not Allowed !"<<endl;
return;
}
};
class PostService : public Service 
{
public:
void processGetService(Request * request , Response * response)
{
cout<<"Not Allowed !"<<endl;
return;
}
};
class ServiceResolver
{
public:
virtual Service * getService (string serviceUrl) = 0;
};

class JerryMouse
{
private :
ServiceResolver  * serviceResolver;
SOCKET clientSocket;
MimeType * mimeType;
public :
JerryMouse()
{
mimeType=new MimeType();
}
~JerryMouse()
{
delete mimeType;
}
void registerServiceResolver(ServiceResolver * serviceResolver)
{
this->serviceResolver = serviceResolver;
}

void start()
{
int status,addr_len;
WSADATA wsa;
SOCKET server_socket,client_socket;
struct sockaddr_in server_addr , client_addr;
status=WSAStartup(MAKEWORD(2,2),&wsa);
server_socket=socket(AF_INET,SOCK_STREAM,0);
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
server_addr.sin_port=htons(7860);
status=bind(server_socket,(struct sockaddr *)&server_addr,sizeof(server_addr));
status=listen(server_socket,128);
cout<<"JerryMouse Listening On Port : 7860"<<endl;
while(1)
{
addr_len=sizeof(client_addr);
client_socket=accept(server_socket,(struct sockaddr *)&client_addr,&addr_len);
cout<<"client connected to server with , IP_ADDRESS : "<<inet_ntoa(client_addr.sin_addr)<<" PORT : "<<htons(client_addr.sin_port)<<endl;
this->clientSocket=client_socket;
Request request(client_socket);
Response response(client_socket);
int requestSize=request.getSize();
cout<<"error"<<endl;
string requestUrl=request.getRequestUrl();
cout<<requestUrl<<endl;

if(requestUrl=="/favicon.ico") 
{
FILE * f ;
if(f = fopen("default\\favicon.ico","rb"))
{
response.sendHeader(200,this->mimeType->getMimeType("ico"));
response.write(f);
request.close();
fclose(f);
}
}
if(requestUrl=="/")
{
FILE * f ;
if(f = fopen("default\\index.html","rb"))
{
response.sendHeader(200,this->mimeType->getMimeType("html"));
response.write(f);
fclose(f);
request.close();
}
}
if(requestUrl=="/index.html")
{
FILE * f ;
if(f = fopen("index.html","rb"))
{
response.sendHeader(200,this->mimeType->getMimeType("html"));
response.write(f);
fclose(f);
request.close();
}
}
if(requestUrl=="/abcd.html")
{
FILE * f ;
if(f = fopen("abcd.html","rb"))
{
response.sendHeader(200,this->mimeType->getMimeType("html"));
response.write(f);
fclose(f);
request.close();
}
}
else
{
vector<string> qs =  split(requestUrl,"?");
map<string,string> queryMap;
parse_url(qs[1],queryMap);
for(auto it=queryMap.begin();it != queryMap.end() ; ++it)
{
cout<< it->first << " : " << it->second <<endl; 
}
for(string sss : qs) cout<<sss<<endl;
vector<string> fs=  split(qs[0],"/");
cout<<"fs:"<<endl;
cout<<fs[1]<<endl;
cout<<"asdfasdfasdfasdfasdfdfhgdfghdfhfghfdhfdghfdh"<<endl;
Service * service = this->serviceResolver->getService("/addEmployee");
cout<<service<<endl;
cout<<"asdfadfasdfasfsadf"<<endl;
//Request * req = new Request(clientSocket);
//req.setParameter(queryMap);
//Response * res = new Response(clientSocket);
cout<<"ayyyyaa"<<endl;
service->processPostService(NULL,NULL);

cout<<"Processed"<<endl;
}
} //while ends
} //start ends
};//class ends

//webapp
class AddEmployee : public PostService 
{
public:
void processPostService(Request * request , Response  * response)
{
cout<<"addEmployee chlla !!"<<endl;
}
};

class DeleteEmployee : public PostService
{
public:
void processPostService(Request * request , Response  * response)
{
cout<<"processEmployee chlla !!"<<endl;
}
};

class GetEmployees: public GetService
{
public :
void processGetService(Request * request, Response * response)
{
cout<<"getEmployees chlla !!"<<endl;
}
};

class Employee : public ServiceResolver
{

private:
unordered_map<string,Service*> serviceMap;

public:

Employee()
{
Service *addEmployee,*deleteEmployee,*getEmployees;
serviceMap.insert(make_pair("/addEmployee",addEmployee));
serviceMap.insert(make_pair("/deleteEmployee",deleteEmployee));
serviceMap.insert(make_pair("/getEmployees",getEmployees));
}

Service * getService(string serviceUrl)
{
cout<<"getService chllaaa"<<endl;
if(serviceUrl=="/addEmployee")
{
auto it = serviceMap.find("/addEmployee");
if(it != serviceMap.end())
{
it->second=new AddEmployee();
return it->second;
}
}

if(serviceUrl=="/deleteEmployee")
{
auto it = serviceMap.find("/deleteEmployee");
if(it != serviceMap.end())
{
it->second=new DeleteEmployee();
return it->second;
}
}

if(serviceUrl=="/getEmployees")
{
auto it = serviceMap.find("/getEmployees");
if(it != serviceMap.end())
{
it->second=new GetEmployees();
return it->second;
}
}
return NULL;
}

};

int main()
{
JerryMouse jerryMouse ;
jerryMouse.registerServiceResolver(new Employee());
jerryMouse.start();
return 0;
}