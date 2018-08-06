#include <bits/stdc++.h>

using namespace std;

int main(){
	string cadena;
	set<char> s;
	getline(cin, cadena);
	for(const char & c : cadena){
		if('a' <= c && c <= 'z') s.insert(c);
	}
	cout << s.size();
	return 0;
}