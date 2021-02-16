#include<iostream>
using namespace std;
class Service;


class Request
{
};

class Response
{
};

class ServiceResolver
{
public:
virtual Service * getService (string serviceUrl) = 0;
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