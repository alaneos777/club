#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool isPrime(lli n){
	if(n <= 1) return false;
	for(lli p = 2; p*p <= n; ++p){
		if(n % p == 0) return false;
	}
	return true;
}

lli S(int n, int d){
	string number(n, '0');
	function<lli(int, int)> gen = [&](int pos, int rem_d){
		if(pos == n){
			assert(rem_d == 0);
			lli x = stoll(number);
			if(isPrime(x)){
				return x;
			}else{
				return 0ll;
			}
		}else{
			lli ans = 0;
			for(int e = (pos==0 ? 1 : 0); e <= 9; ++e){
				if(e == d && rem_d == 0) continue;
				number[pos] = e+'0';
				int new_rem = rem_d - (e==d ? 1 : 0);
				if(new_rem <= n-pos-1) ans += gen(pos+1, new_rem);
				number[pos] = '0';
			}
			return ans;
		}
	};
	for(int mx = n; mx >= 1; --mx){
		lli ans = gen(0, mx);
		if(ans) return ans;
	}
	return 0;
}

int main(){
	lli sum = 0;
	for(int d = 0; d <= 9; ++d){
		lli term = S(10, d);
		sum += term;
		cout << d << " " << term << "\n";
	}
	cout << sum << "\n";
	return 0;
}