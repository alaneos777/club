#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli sgn(lli x){
	if(x > 0) return 1;
	if(x < 0) return -1;
	return 0;
}

tuple<lli, lli, lli> extgcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		lli q = a/b;
		auto[d, x, y] = extgcd(b, a - b*q);
		return {d, y, x - y*q};
	}
}

vector<lli> getPrimes(lli n){
	vector<lli> ans;
	for(lli p = 2; p*p <= n; ++p){
		int a = 0;
		while(n % p == 0){
			a++;
			n /= p;
		}
		if(a > 0) ans.push_back(p);
	}
	if(n > 1) ans.push_back(n);
	return ans;
}

auto getDivs(lli n){
	vector<lli> ans = {1};
	for(lli p : getPrimes(n)){
		int sz = ans.size();
		for(int i = 0; i < sz; ++i){
			ans.push_back(-ans[i]*p);
		}
	}
	return ans;
}

lli S(lli N){
	if(N%2 == 0) return 0;
	lli ans = 0;
	lli rhs = N%3;
	for(lli d : getDivs((N+3)/2)){
		lli mu = sgn(d); d = abs(d);
		auto[gcd, x, _] = extgcd(d, 3);
		if(rhs % gcd > 0) continue;
		lli step = 3/gcd;
		x = x * (rhs/gcd % step) % step;
		if(x < 0) x += step;
		x = x*d;
		lli lcm = d*step;
		ans += mu * ((N+1)/2 - x + lcm) / lcm;
	}
	return ans;
}

int main(){
	cout << S(12017639147ll) << "\n";
	return 0;
}