#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#define ll long long

using namespace std;

ifstream in ("input.txt");
ofstream out("output.txt");

ll sumOfAll;
string newString;
vector <string> numberList = { "one","two","three","four","five","six","seven","eight","nine"};

char parseNumber(string str) {
    int index = 1;
    for (auto number : numberList) {
        int length = number.length();
        if (number.compare(0,length,str,0,length) == 0) {
            return '0'+index;
        }
        index++;
    }
    return str[0];
}

void parseString(string &str) {
    for (int i = 0; i < str.size();i++) {
        str[i] = parseNumber(str.substr(i));
    }
}

int main()
{
    while (in >> newString) {
        int last=0, first=0,ok=0;
        parseString(newString);
        for (auto i : newString) {
            if (i >= '0' && i <= '9')
            {
                last = i - '0';
                if (!ok) {
                    first = last;
                    ok = 1;
                }
            }
        }
        int nb = first * 10 + last;
        sumOfAll += nb;
    }
    cout << sumOfAll;
    return 0;
}
