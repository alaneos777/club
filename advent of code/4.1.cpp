#include <bits/stdc++.h>
using namespace std;

const set<string> A = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};
const set<string> B = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

bool valid(const string & passport){
	string field;
	stringstream ss(passport);
	set<string> keys;
	while(ss >> field){
		string key = field.substr(0, 3);
		string val = field.substr(4);
		keys.insert(key);
	}
	return keys == A || keys == B;
}

int main(){
	string linea;
	string passport;
	int ans = 0;
	while(getline(cin, linea)){
		if(linea == ""){
			ans += valid(passport);
			passport = "";
		}else{
			passport += linea + " ";
		}
	}
	if(passport != ""){
		ans += valid(passport);
	}
	cout << ans << "\n";
	return 0;
}