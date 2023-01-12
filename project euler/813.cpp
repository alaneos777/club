#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9+7;
const int ord = (mod-1)/2;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

using poly = set<int>;

poly sq(const poly& p){
	poly ans;
	for(int x : p){
		x = x+x;
		if(x >= ord) x -= ord;
		if(ans.count(x)) ans.erase(x);
		else ans.insert(x);
	}
	return ans;
}

poly operator*(const poly& p, const poly& q){
	poly ans;
	for(int x : p){
		for(int y : q){
			int z = x+y;
			if(z >= ord) z -= ord;
			if(ans.count(z)) ans.erase(z);
			else ans.insert(z);
		}
	}
	return ans;
}

poly pw(const poly& a, const string& n){
	poly ans = {0};
	for(char d : n){
		ans = sq(ans);
		if(d == '1') ans = ans * a;
	}
	return ans;
}

int eval(const poly& p){
	lli ans = 0;
	for(int x : p){
		ans += power(2, x);
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int main(){
	poly p = pw(poly{0, 1, 3}, "11001101000010000000000000000000000000000000000000000000000000000");
	int ans = eval(p);
	cout << ans << "\n";
	return 0;
}