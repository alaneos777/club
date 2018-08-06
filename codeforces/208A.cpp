#include <bits/stdc++.h>

using namespace std;

int main(){
	string cadena, palabra;
	string del = "WUB";
	vector<string> nueva;
	size_t pos = 0;
	cin >> cadena;
	while((pos = cadena.find(del)) != string::npos){
		palabra = cadena.substr(0, pos);
		if(palabra != "") nueva.push_back(palabra); 
		cadena.erase(0, pos+del.size());
	}
	if(cadena != "") nueva.push_back(cadena);
	for(const string & str : nueva) cout << str << " ";
	return 0;
}