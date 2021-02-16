 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<winsock2.h>

//Utils

struct node
{
struct node * next;
int *client_socket;
};

struct node* head = NULL; 

struct node* tail = NULL;

int * dequeue()
{
if(head == NULL) 
{ 
return NULL;
} 
else 
{ 
int *result = head->client_socket; 
struct node *temp = head;
head = head->next;
if (head == NULL) 
{
tail = NULL;
} 
free (temp); 
return result;
}
}

void enqueue (int * client_socket)
{
struct node *newnode = (struct node*)malloc(sizeof(struct node));
newnode->client_socket = client_socket;
newnode->next = NULL; 
if(tail == NULL) 
{ 
head = newnode; 
} 
else 
{ 
tail->next = newnode;
}
tail = newnode;
}

const char * getMimeType(const char * str)
{
return "";
}

//Framework

typedef struct {
}Cookie;

typedef struct{
}Session;

typedef struct{
}Request;

typedef struct 
{
}Response;

typedef  void (*Process) (Request * request , Response * response);

typedef struct{
const char * processType ;
Process process; 
}Service;

typedef  Service * (*Resolver) (const char *);
 
Resolver JerryMouseResolver;

void  setResolver(Resolver resolver)
{
JerryMouseResolver = resolver;
}


#define JerryMousePoolSize 21
pthread_t threadPool[JerryMousePoolSize];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var= PTHREAD_COND_INITIALIZER;

void * requestProcessor (void * p_client_socket )
{
SOCKET clientSocket = *(int *)p_client_socket ;
free(p_client_socket);
char buffer[1024];
char requestType[10];
char requestURL[100];
recv(clientSocket,buffer,sizeof(buffer),0);
printf("%s\n",buffer);
const char * header="HTTP/1.1 200 OK\r\n\r\nHello.";
send(clientSocket,header,sizeof(header),0);
closesocket(clientSocket);
}


void * threadFunction(void *args)
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

void setUpThreadPool()
{
for(int i=0 ; i < JerryMousePoolSize ; i++) 
{
pthread_create(&threadPool[i],NULL,threadFunction,NULL);
}
}

void setUpServer()
{
int status,addr_len;
WSADATA wsa;
SOCKET server_socket,client_socket;
struct sockaddr_in server_addr , client_addr;
status=WSAStartup(MAKEWORD(2,2),&wsa);
if(status != 0) {} 
server_socket=socket(AF_INET,SOCK_STREAM,0);
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
server_addr.sin_port=htons(8080);
status=bind(server_socket,(struct sockaddr *)&server_addr,sizeof(server_addr));
if(status == SOCKET_ERROR) {}
status=listen(server_socket,128);
if(status == SOCKET_ERROR) {}
printf("listening...\n");
while(1)
{
addr_len=sizeof(client_addr);
client_socket=accept(server_socket,(struct sockaddr *)&client_addr,&addr_len);
if(client_socket ==  INVALID_SOCKET){}
else
{
char buf[1024];
recv(client_socket,buf,sizeof(buf),0);
printf("%s\n",buf);
const char * header="HTTP/1.1 200 OK\r\nContent-Type : text/html; charset=UTF-8\r\nSet-Cookie: sessionid=123456789;\r\n\r\n";
printf("----------------------------------------------\n");
send(client_socket,header,strlen(header),0);
printf("size:%d\n",sizeof("akshat"));
printf("len:%d\n",strlen("akshat"));
printf("%s\n",header);
char buffer[1024] = {0};
FILE *f;
if((f=fopen("test.html","rb"))) printf("Yes\n");
else printf("No\n");
int len=0;
int result=0;
while((result=fread(buffer,1,1024,f)) > 0)
{
len=send(client_socket, buffer, result, 0);
if(len == SOCKET_ERROR) 
{
printf("socketerror\n");
return ;
}
else if(!len)
{
printf("end\n");
return ;
}
}
fclose(f);
closesocket(client_socket);
}
}
}

void start()
{
setUpThreadPool();
setUpServer();
}


//Developer
void addEmployee(Request *,Response *);

Service * getService(const char * name)
{
if(!strcmp(name,"/addEmployee"))
{
Service * service ;
service =(Service *)malloc(sizeof(Service));
service->processType="POST";
service->process=&addEmployee;
return service;
} 
return NULL;
}

void addEmployee(Request * request ,Response * response)
{
printf("Employee Added.\n");
}

int main()
{
Resolver resolver;
resolver=&getService;
setResolver(resolver);
start();
return 0;
}