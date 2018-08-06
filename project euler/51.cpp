#include <bits/stdc++.h>
using namespace std;

vector<int> primos;
vector<bool> esPrimo;

void criba(int n){
	primos.push_back(2);
	esPrimo.resize(n + 1, true);
	for(int i = 4; i <= n; i += 2) esPrimo[i] = false;
	int limit = sqrt(n);
	for(int i = 3; i <= n; i++){
		if(esPrimo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(int j = i * i; j <= n; j += 2*i){
					esPrimo[j] = false;
				}
			}
		}
	}
}

string intToStr(int n){
	stringstream ss;
	ss << n;
	return ss.str();
}

int strToInt(string s){
	int n;
	stringstream ss(s);
	ss >> n;
	return n;
}

int condition(int n){
	if(!esPrimo[n]) return 0;
	string s = intToStr(n);
	int ans = 0;
	int digits = s.size();
	int limit = 1 << digits;
	for(int i = 0; i < limit; i++){
		int count = 0;
		set<int> tmp;
		for(char digit = '0'; digit <= '9'; digit++){
			string sCopy = s;
			for(int j = 0; j < digits; j++){
				if((i >> j) & 1){
					sCopy[j] = digit;
				}
			}
			tmp.insert(strToInt(sCopy));
		}
		for(const int & t : tmp){
			if(intToStr(t).size() == s.size() && esPrimo[t]){
				count++;
			}
		}
		if(tmp.count(n)) ans = max(ans, count);
	}
	return ans;
}

int main(){
	int limit = 1e6;
	criba(limit);
	for(int i = 56003; i <= limit; i++){
		if(condition(i) == 8){
			cout << i << "\n";
			break;
		}
	}
	return 0;
}