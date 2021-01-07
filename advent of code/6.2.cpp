#include <bits/stdc++.h>
using namespace std;

int process(const string & s){
	stringstream ss(s);
	string linea;
	int people = 0;
	vector<int> answers(26);
	while(getline(ss, linea)){
		for(char c : linea){
			answers[c-'a']++;
		}
		people++;
	}
	int ans = 0;
	for(int i = 0; i < 26; ++i){
		ans += (answers[i] == people);
	}
	return ans;
}

int main(){
	string linea;
	string grupo;
	int ans = 0;
	while(getline(cin, linea)){
		if(linea == ""){
			ans += process(grupo);
			grupo = "";
		}else{
			grupo += linea + "\n";
		}
	}
	if(grupo != ""){
		ans += process(grupo);
	}
	cout << ans << "\n";
	return 0;
}