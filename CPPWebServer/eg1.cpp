#include<iostream>
#include<typeinfo>
#include<functional>
#include<map>
using namespace std;

class Service;
class WebServer;
class Request;
class Response;
class Employee;

class ServiceResolver
{
public:
virtual Service * getService (string serviceUrl) = 0;
};

class Service 
{
private:
string type;
public:
Service()
{
this->type="GET";
}
void setType(string type)
{
this->type=type;
}
string getType()
{
return this->type;
}
void setService(function<void(Request*,Response*)> func)
{

}
friend class WebServer;
};

class WebServer
{
private :
ServiceResolver * sr;
public :
void registerServiceResolver(ServiceResolver  * sr)
{
this->sr=sr;
}
void start()
{
Service * s = this->sr->getService("/getEmployees"); 
}
};

class Employee : public ServiceResolver
{
private:
map<string,Service*> serviceMap;
public:
Employee()
{
serviceMap.insert(pair<string,Service*>("/getEmployees",NULL));
}
Service * getService(string name)
{
if(name=="/getEmployees")
{
auto it = serviceMap.find("/getEmployees");
if(it != serviceMap.end())
{
it->second=new Service();
it->second->setType("GET");
it->second->setService(&getEmployees);
return it->second;
}
}
return NULL;
}

void getEmployees(Request * request, Response * response)
{
cout<<"getEmployees called "<<endl;
}

};
int main()
{
WebServer webServer;
webServer.registerServiceResolver(new Employee());
webServer.start();
return 0;
}