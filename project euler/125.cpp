#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool pal(lli n){
	lli N = n, n_rev = 0;
	while(n){
		lli d = n % 10;
		n_rev = n_rev * 10 + d;
		n /= 10;
	}
	return N == n_rev;
}

const int M = 1e8;

int main(){
	set<lli> st;
	for(lli a = 1; ; ++a){
		bool found = false;
		for(lli b = a+1; ; ++b){
			lli n = b*(b+1)*(2*b+1)/6 - a*(a-1)*(2*a-1)/6;
			if(n > M){
				break;
			}
			if(pal(n)){
				st.insert(n);
			}
			found = true;
		}
		if(!found) break;
	}
	lli sum = 0;
	for(lli x : st){
		sum += x;
	}
	cout << sum << "\n";
	return 0;
}