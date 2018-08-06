#include <bits/stdc++.h>

using namespace std;

int main(){
	string str;
	cin >> str;
	if('a' <= str[0] && str[0] <= 'z') str[0] += 'A' - 'a';
	cout << str;
	return 0;
}