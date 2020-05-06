#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int N = 30;

const vector<string> keywords = {"FREE", "FARE", "AREA", "REEF"};

map<tuple<int, string, uint8_t>, lli> mem;

lli f(int idx, const string & last, uint8_t mask){
	if(idx == N){
		return mask == 15;
	}
	auto key = make_tuple(idx, last, mask);
	if(mem.count(key)) return mem[key];
	lli ans = 0;
	for(char c : {'A', 'E', 'F', 'R'}){
		string next_s = last + c;
		int i = 0;
		uint8_t next_m = 0;
		for(const string & keyword : keywords){
			if(keyword == next_s){
				next_m = (1 << i);
				break;
			}
			i++;
		}
		if((mask & next_m) == 0){
			ans += f(idx+1, next_s.substr(1), mask | next_m);
		}
	}
	return mem[key] = ans;
}

int main(){
	cout << f(0, "---", 0) << "\n";
	return 0;
}