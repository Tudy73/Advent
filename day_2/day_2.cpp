#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#define ll long long
#define totalRed 12
#define totalGreen 13
#define totalBlue 14
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int sum;

int main()
{
    string newLine;
    string gameString;
    int gameNo;
    char dots;
    int noOfCubes;
    string color;

    string endLine;
    while (getline(in, newLine)) {
        istringstream sin(newLine);
        sin >> gameString >> gameNo >> dots;

        int red=totalRed, green=totalGreen, blue=totalBlue;
        int minRed = 0, minGreen = 0, minBlue = 0;
        bool ok = 1;
        while (sin >> noOfCubes >> color) {
            char comma = color[color.length() - 1];
            if (comma == ',' || comma == ';')
                color.pop_back();
            else
                comma = ';';

            if (color == "red") {
                minRed = max(minRed, noOfCubes);
            }
            else if (color == "green") {
                minGreen = max(minGreen, noOfCubes);
            }
            else if (color == "blue") {
                minBlue = max(minBlue, noOfCubes);
            }

            if(comma == ';')
                red = totalRed, green = totalGreen, blue = totalBlue;
        }

        if (ok) {
            sum += minRed*minGreen*minBlue;
        }
    }
    cout << sum;
}