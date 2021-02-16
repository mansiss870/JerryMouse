#include <iostream>
#include <unordered_map>
using namespace std;
//framework 


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
serviceMap.insert(pair("/addEmployee",addEmployee));
serviceMap.insert(pair("/deleteEmployee",deleteEmployee));
serviceMap.insert(pair("/getEmployees",getEmployees));
}

Service * getService(string serviceUrl)
{
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