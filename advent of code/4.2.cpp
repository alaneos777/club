#include <bits/stdc++.h>
using namespace std;

const set<string> A = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};
const set<string> B = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
const set<string> eyes = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

bool isnumeric(const string & s){
	bool valid = !s.empty();
	for(char c : s){
		valid &= ('0' <= c && c <= '9');
	}
	return valid;
}

bool ishex(const string & s){
	bool valid = true;
	for(char c : s){
		valid &= (('0' <= c && c <= '9') || ('a' <= c && c <= 'f'));
	}
	return valid;
}

bool valid(const string & passport){
	string field;
	stringstream ss(passport);
	set<string> keys;
	bool valid = true;
	while(ss >> field){
		string key = field.substr(0, 3);
		string val = field.substr(4);
		keys.insert(key);
		if(key == "byr"){
			int year = ((val.size() == 4 && isnumeric(val)) ? stoi(val) : 0);
			valid &= (1920 <= year && year <= 2002);
		}else if(key == "iyr"){
			int year = ((val.size() == 4 && isnumeric(val)) ? stoi(val) : 0);
			valid &= (2010 <= year && year <= 2020);
		}else if(key == "eyr"){
			int year = ((val.size() == 4 && isnumeric(val)) ? stoi(val) : 0);
			valid &= (2020 <= year && year <= 2030);
		}else if(key == "hgt"){
			string type = val.substr(val.size()-2);
			int num = (isnumeric(val.substr(0, val.size()-2)) ? stoi(val.substr(0, val.size()-2)) : 0);
			if(type == "cm"){
				valid &= (150 <= num && num <= 193);
			}else if(type == "in"){
				valid &= (59 <= num && num <= 76);
			}else{
				valid = false;
			}
		}else if(key == "hcl"){
			valid &= (val.size() == 7 && val[0] == '#' && ishex(val.substr(1)));
		}else if(key == "ecl"){
			valid &= eyes.count(val);
		}else if(key == "pid"){
			valid &= (val.size() == 9 && isnumeric(val));
		}
	}
	return valid && (keys == A || keys == B);
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