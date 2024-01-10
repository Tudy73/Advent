#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
#define ll long long
#define pb push_back

#define highCard 1
#define onePair 2
#define twoPair 3
#define threeOfaKind 4
#define fullHouse 5
#define fourOfaKind 6
#define fiveOfaKind 7

using namespace std;

ifstream in("input.txt");

typedef struct {
    string cards;
    int value;
    ll bid;
    int type;
}hand;

vector<hand> hands;
map <hand, int> ranking;
map <char, int> cardValue;
char cardTypes[13] = { 'J','2','3','4','5','6','7','8','9','T','Q','K','A' };

bool compare(hand a, hand b) {
    if (a.type == b.type) {
        return a.value < b.value;
    }
    return a.type < b.type;
}
int findValue(string str) {
    int value=0;
    int power = 1;
    for (int i = str.size() - 1; i >= 0;i--) {
        value += cardValue[str[i]]*power;
        power *= 100;
    }
    return value;
}
int findType(string str) {
    int frequency[13];
    for (int i = 0; i < 13; i++)frequency[i] = 0;
    int hasFive = 0, hasFour = 0, hasThree = 0, hasTwo = 0;
    for (auto i : str) {
        frequency[cardValue[i]]++;
    }
    int count = 0;
    for (int i = 1; i < 13; i++) {
        count = max(count, frequency[i]);
    }
    for (int i = 1; i < 13; i++) {
        if (frequency[i] == count) {
            frequency[i] += frequency[0];
            break;
        }
    }
    for (int i = 1; i < 13; i++) {
        switch (frequency[i]) {
        case 5:
            hasFive++;
            break;
        case 4:
            hasFour++;
            break;
        case 3:
            hasThree++;
            break;
        case 2:
            hasTwo++;
            break;
        }  
    }

    if (hasFive) return fiveOfaKind;
    if (hasFour) return fourOfaKind;
    if (hasThree && hasTwo) return fullHouse;
    if (hasThree) return threeOfaKind;
    if (hasTwo == 2) return twoPair;
    if (hasTwo)return onePair;
    return highCard;

}
void readInput() {

    for (int i = 0; i < 13; i++) {
        cardValue[cardTypes[i]] = i;
    }
    string newLine, str;
    ll bid;
    int type,value;
    while (getline(in, newLine)) {
        istringstream sin(newLine);
        sin >> str >> bid;
        value = findValue(str);
        type = findType(str);
        hands.pb({ str,value,bid,type });
    }
}
ll calculateRanks() {
    sort(hands.begin(), hands.end(), compare);
    ll total = 0;
    ll index = 1;
    for (auto item : hands) {
        total += item.bid * index++;
    }
    return total;
}
int main(){

    readInput();
    cout<<calculateRanks();
    return 0;
}