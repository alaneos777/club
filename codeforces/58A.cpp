#include <bits/stdc++.h>

using namespace std;

int main(){
	string s, destino = "hello";
	cin >> s;
	int i = 0;
	for(char c : s){
		if(c == destino[i]){
			i++;
		}
	}
	if(i == destino.size()) cout << "YES";
	else cout << "NO";
	return 0;
}