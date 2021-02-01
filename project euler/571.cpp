#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli str_to_int(const string & s, int b){
	lli ans = 0;
	for(char c : s){
		int d = (('0' <= c && c <= '9') ? c-'0' : c-'A'+10);
		ans = ans * b + d;
	}
	return ans;
}

bool is(lli n, int b){
	int freq = 0, full = (1 << b) - 1;
	while(n){
		int d = n % b;
		n /= b;
		freq |= (1 << d);
		if(freq == full) return true;
	}
	return false;
}

int main(){
	set<lli> st;
	string s = "1023456789AB";
	do{
		lli n = str_to_int(s, 12);
		bool valid = true;
		for(int b = 11; b >= 2; --b){
			if(!is(n, b)){
				valid = false;
				break;
			}
		}
		if(valid){
			st.insert(n);
		}
		if(st.size() == 10) break;
	}while(next_permutation(s.begin(), s.end()));
	lli sum = 0;
	for(lli x : st){
		sum += x;
		cout << x << "\n";
	}
	cout << "\n" << sum << "\n";
	return 0;
}