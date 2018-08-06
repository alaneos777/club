#include <bits/stdc++.h>
using namespace std;
typedef __int128 lli;

lli inv(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1 != 0){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	return s0;
}

lli modPow(lli a, lli b, lli m){
	lli ans = 1;
	a %= m;
	while(b){
		if(b & 1) ans = (ans * a) % m;
		b >>= 1;
		a = (a * a) % m;
	}
	return ans;
}

lli m = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	long long int _n, _p;
	lli n, p;
	cin >> _p >> _n;
	n = _n, p = _p;
	set<lli> values;
	values.insert(p * p - 1);
	values.insert(2 * (p - 1));
	lli limit = sqrt(_p - 1);
	for(lli i = 1; i <= limit; i++){
		if((p - 1) % i == 0){
			lli j = (p - 1) / i;
			values.insert(p * (p - 1) / j + p - 1);
			if(j > 1) values.insert((j + 1) * (p - 1) / j);
			if(i != j){
				values.insert(p * (p - 1) / i + p - 1);
				if(i > 1) values.insert((i + 1) * (p - 1) / i);
			}
		}
	}
	lli a0 = p - 1;
	lli ans = 0;
	for(lli a1 : values){
		if(n == 0){
			ans = (ans + a0) % m;
		}else if(n == 1){
			ans = (ans + a1) % m;
		}else{
			lli r = a1 * inv(a1 - a0, m) % m;
			ans = (ans + r) % m;
		}
	}
	if(n >= 2) ans = ans * modPow(p, n - 1, m) % m;
	if(ans < 0) ans += m;
	cout << values.size() << " ";
	stack<int> digits;
	do{
		digits.push(ans % 10);
		ans /= 10;
	}while(ans > 0);
	while(!digits.empty()){
		cout << digits.top();
		digits.pop();
	}
	return 0;
}