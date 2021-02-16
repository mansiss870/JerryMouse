#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

#include <winsock2.h>
#include <stdlib.h>
#include <pthread.h>

#include <filesystem>  
#include <algorithm>
#include <iostream>  
#include <vector>
#include <cstdio>
#include <string>
#include <map>

#include "utils/queue.h"
#include "utils/mimetype.h"
#include "http/jerryMouseHttp.h"

using namespace std; 

class WebApplication;
class MimeType;

#define THREAD_POOL_SIZE 16

int PORT_NUMBER;
string IP_ADDRESS;
map<string,WebApplication> contextMap;
vector<string> webApplications;

pthread_t threadPool[THREAD_POOL_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var= PTHREAD_COND_INITIALIZER;

MimeType mt;

class WebApplication
{
private :
string homePage;
map<string,string> requestMapping;
public :
void setHomePage(string homePage)
{
this->homePage=homePage;
}
string getHomePage()
{
return this->homePage;
}
void setRequestMapping(map<string,string> requestMapping) 
{
this->requestMapping=requestMapping;
}
map<string,string> getRequestMapping()
{
return this->requestMapping;
}
};

vector<string> getWebApplications()
{
vector<string> webApplications;
for (auto& i : filesystem::directory_iterator("apps"))
{
if(filesystem::is_directory(i)) 
{
webApplications.push_back(i.path().string().substr(5));
}
}
return webApplications;
}


bool contains(vector<string> arr , string search)
{
return  find(arr.begin(),arr.end(),search) != arr.end();
}


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


void setServerConf()
{
//setting ipAddress and portNumber from server.conf
FILE *file;
if(file=fopen("server.conf","rb"))
{
//server.conf found
char readBuffer[1024];
rapidjson::FileReadStream fileReadStream(file,readBuffer,sizeof(readBuffer));
rapidjson::Document document;
document.ParseStream(fileReadStream);
if(document.HasParseError())
{
//server.conf is invalid
PORT_NUMBER=7860;
IP_ADDRESS="172.0.0.1";
}
else
{
rapidjson::Value & portNumber = document["PORT_NUMBER"];
rapidjson::Value & ipAddress = document["IP_ADDRESS"];
PORT_NUMBER=portNumber.GetInt();
IP_ADDRESS=ipAddress.GetString();
}
fclose(file);
}
else
{
//server.conf not found
PORT_NUMBER=7860;
IP_ADDRESS="172.0.0.1";
}
}


void setAppConf()
{
//getting list of webapplication
webApplications = getWebApplications();

//creating context map
for(string application : webApplications )
{
WebApplication webApplication;
contextMap.insert(pair<string,WebApplication>(application,webApplication));
}

//iterating directories for app.conf
for (auto &rdi : filesystem::recursive_directory_iterator("apps")) 
{
//splitting the path in to an arrary using some delimeter
vector<string> arr = split(rdi.path().string(),"\\");
if(arr.size() > 1)
{
if( arr.size() == 3 && filesystem :: is_directory(rdi) && arr[2] == "private" && contains(webApplications,arr[1]))
{
string appConfPath=rdi.path().string() + "\\app.conf";
FILE *file;
if(file=fopen(appConfPath.c_str(),"rb"))
{
//app.conf found 
char readBuffer[100000];
rapidjson::FileReadStream fileReadStream(file,readBuffer,sizeof(readBuffer));
rapidjson::Document document;
document.ParseStream(fileReadStream);
if(document.HasParseError())
{
//app.conf invalid 
}
else
{
rapidjson::Value & homePage = document["homePage"];
WebApplication wa = contextMap.find(arr[1])->second ;
wa.setHomePage(homePage.GetString());
map<string,string> ss;
rapidjson::Value & requestMapping = document["requestMapping"];
for(rapidjson::Value::ConstMemberIterator itr = requestMapping.MemberBegin(); itr!=requestMapping.MemberEnd() ;++itr) 
{
ss.insert(pair<string,string>(itr->name.GetString(),itr->value.GetString()));
}
wa.setRequestMapping(ss);
}
fclose(file);
}
else
{
//app.conf not found
} 
}
}
}//for loop ends  
}


void * requestProcessor (void * p_client_socket )
{
SOCKET client_socket = *(int *)p_client_socket ;
free(p_client_socket);
Request request(client_socket);

int requestSize=request.getSize();
string requestType=request.getType();
string requestUrl=request.getRequestURL();
string requestBuffer=request.getBuffer();
Response response= request.getResponse();

if(requestUrl=="/")
{
FILE * f ;
if(f = fopen("default\\index.html","rb"))
{
response.sendHeader(200,mt.getMimeType("html"));
response.send(f);
fclose(f);
}
else
{
response.sendHeader(404,mt.getMimeType("html"));
response.send(fopen("error\\404.html"),"rb");
}
}

return NULL;
}




void * thread_function(void *args)
{
while(1)
{
int *p_client_socket;
pthread_mutex_lock(&mutex);
pthread_cond_wait(&condition_var,&mutex);
p_client_socket=dequeue();
pthread_mutex_unlock(&mutex);
if(p_client_socket != NULL)
{
requestProcessor(p_client_socket);
}
}
}

void createThreadPool()
{
for(int i=0 ; i < THREAD_POOL_SIZE ; i++) 
{
pthread_create(&threadPool[i],NULL,thread_function,NULL);
}
}

void init()
{
setServerConf();
setAppConf();
createThreadPool();
}

int main(int argc, char ** argv)
{

init();
MimeType mimeType;
cout<< mimeType.getMimeType("zip") <<endl;

//creating server_socket 

int status,addr_len;
WSADATA wsa;
SOCKET server_socket,client_socket;
struct sockaddr_in server_addr , client_addr;

status=WSAStartup(MAKEWORD(2,2),&wsa);
if(status != 0)
{
//unable to intialize winsock
return 1;
}

server_socket=socket(AF_INET,SOCK_STREAM,0);
if(server_socket == INVALID_SOCKET)
{
//unable to create socket
}

server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS.c_str());
server_addr.sin_port=htons(PORT_NUMBER);

status=bind(server_socket,(struct sockaddr *)&server_addr,sizeof(server_addr));
if(status == SOCKET_ERROR)
{
//unable to bind socket
}

status=listen(server_socket,128);
if(status == SOCKET_ERROR) 
{
//unable to listen
}

cout<<"JerryMouse Listening On Port : "<<PORT_NUMBER<<endl;

while(1)
{
addr_len=sizeof(client_addr);
client_socket=accept(server_socket,(struct sockaddr *)&client_addr,&addr_len);
if(client_socket ==  INVALID_SOCKET)
{
//unable to create socket
}
else
{ 
//processing request on diffrent threads
cout<<"client connected to server with , IP_ADDRESS : "<<inet_ntoa(client_addr.sin_addr)<<" PORT : "<<htons(client_addr.sin_port)<<endl;
/*
pthread_t t;
int *p_client_socket=(int *)malloc(sizeof(SOCKET));
*p_client_socket=client_socket;
pthread_create(&t,NULL,requestProcessor,p_client_socket);
*/

int *p_client_socket=(int *)malloc(sizeof(SOCKET));
*p_client_socket=client_socket;
pthread_mutex_lock(&mutex);
enqueue(p_client_socket);
pthread_cond_signal(&condition_var);
pthread_mutex_unlock(&mutex);

}
}// while loop ends
return 0;
}








