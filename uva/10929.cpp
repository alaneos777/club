#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	string str;
	while(cin >> str && str != "0"){
		int suma = 0, alt = 1;
		for(int i = 0; i < str.size(); i++){
			suma += alt * (str[i] - '0');
			alt *= -1;
		}
		cout << str << " is";
		if(suma % 11 != 0)
			cout << " not";
		cout << " a multiple of 11.\n";
	}
	return 0;
}