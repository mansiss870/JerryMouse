#include <iostream>
#include <string>
#include <list>
using namespace std;
int main()
{
list<string> arr;
string str="apps\\test\\private\\app.conf";
string delimiter="\\";
auto start=0;
auto end=str.find(delimiter);
while(end!=string::npos)
{
arr.push_back(str.substr(start,end-start));
start=end+delimiter.length();
end=str.find(delimiter,start);
}
arr.push_back(str.substr(start,end));
for(auto i =arr.begin();i!=arr.end();++i)
{
cout<< *i <<endl;
}
return 0;
}