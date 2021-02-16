#include<iostream>
#include<sstream>
#include<map>
using namespace std;
unsigned char from_hex(unsigned char ch) 
{
            if (ch <= '9' && ch >= '0')
                ch -= '0';
            else if (ch <= 'f' && ch >= 'a')
                ch -= 'a' - 10;
            else if (ch <= 'F' && ch >= 'A')
                ch -= 'A' - 10;
            else 
                ch = 0;
            return ch;
}

 const std::string urldecode (const std::string& str) 
        {
            using namespace std;
            string result;
            string::size_type i;
            for (i = 0; i < str.size(); ++i)
            {
                if (str[i] == '+')
                {
                    result += ' ';
                }
                else if (str[i] == '%' && str.size() > i+2)
                {
                    const unsigned char ch1 = from_hex(str[i+1]);
                    const unsigned char ch2 = from_hex(str[i+2]);
                    const unsigned char ch = (ch1 << 4) | ch2;
                    result += ch;
                    i += 2;
                }
                else
                {
                    result += str[i];
                }
            }
            return result;
        }

void parse_url(std::string word , map<string,string>& queries)       
        {
            std::string::size_type pos;

            for (pos = 0; pos < word.size(); ++pos)
            {
                if (word[pos] == '&')   word[pos] = ' ';
            }

            std::istringstream sin(word);
            sin >> word;

            while (sin)
            {
                pos = word.find_first_of("=");
                if (pos != std::string::npos)
                {
                    std::string key = urldecode(word.substr(0,pos));
                    std::string value = urldecode(word.substr(pos+1));
                    queries[key] = value;
                }
                sin >> word;
            }
        }