#include <bits/stdc++.h>
using namespace std;
using ld = long double;

ld str_to_ld(const string& s){
	ld ans = 0;
	for(int i = s.size()-1; i >= 0; --i) ans = ans/10 + (s[i]-'0');
	return ans/10;
}

string gen(ld f, int terms){
	string s;
	for(int i = 1; i <= terms; ++i){
		f = floorl(f) * (f - floorl(f) + 1);
		s += to_string((int)floorl(f));
	}
	return s;
}

int main(){
	string digits;
	int i = 1;
	while(digits.size() < 25){
		for(int j = 1; ; ++j){
			string nxt = digits + to_string(j);
			int len = nxt.size();
			ld f = 2 + str_to_ld(nxt);
			if(gen(f, i) == nxt){
				digits = nxt;
				break;
			}
		}
		i++;
	}
	string ans = string("2.") + digits;
	cout << ans << "\n";
	return 0;
}