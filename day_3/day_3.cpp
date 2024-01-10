#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#define ll long long
#define rows 140
#define columns 140

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

string map[rows];
bool visited[rows][columns];
ll sum;

int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { -1,0,1,-1,1,-1,0,1 };

ll addNumber(int row, int column) {

	int number = 0;
	while (column < columns && isdigit(map[row][column])) {
		number = number * 10 + (map[row][column] - '0');
		visited[row][column] = true;
		++column;
	}
	return number;
}
ll findRootofNumber(int row, int column) {
	int col = column;
	while (col>0 && isdigit(map[row][col-1])) {
		col--;
	}
	return col;
}
ll extractNumber(int row, int column) {
	int newColumn = findRootofNumber(row, column);
	return addNumber(row, newColumn);
}
bool inBounds(int row, int column) {
	if (row >= 0 && column >= 0 && row < rows && column < columns)
		return true;
	return false;
}
bool okToExtract(int row, int column) {
	if (!visited[row][column] && inBounds(row, column) && isdigit(map[row][column]))
		return true;
	return false;
}
int main()
{
	for (int i = 0; i < rows; i++) {
		in >> map[i];
	}
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j <columns; j++) {
			if (map[i][j] == '*') {
				ll extractCounter = 0, product = 1;
				for (int k = 0; k < 8; k++) {
					int x1 = i + dx[k];
					int y1 = j + dy[k];
					if (okToExtract(x1,y1)) {
						extractCounter++;
						product *= extractNumber(x1, y1);
					}
				}
				if (extractCounter == 2) {
					sum += product;

				}
			}
		}
	}

	cout << sum;
}