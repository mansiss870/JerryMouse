#include<iostream>
#include<map>
using namespace std;
class Request {};
class Response {};
typedef void (*service)(Request * , Response *); 
class ServiceResolver
{
public:
virtual pair< string , void (*service)(Request * , Response *) >  getService (string serviceUrl) = 0;
};
