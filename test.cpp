#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

const lli x = 101;
const int sz = 4;
const lli mod[] = {lli(1e18) + 3, lli(1e18) - 11, lli(1e17) + 3, lli(1e17) - 3};

lli power(lli a, lli b, lli c){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % c;
		b >>= 1;
		a = a * a % c;
	}
	return ans;
}

struct LLI{
	lli n[sz];
	LLI(){
		memset(n, 0, sizeof(n));
	}
	LLI(lli x){
		for(int i = 0; i < sz; ++i){
			n[i] = x % mod[i];
			if(n[i] < 0) n[i] += mod[i];
		}
	}
	LLI(lli a, lli b){
		for(int i = 0; i < sz; ++i){
			n[i] = power(a, b, mod[i]);
		}
	}
	LLI operator+(const LLI & rhs) const{
		LLI res;
		for(int i = 0; i < sz; ++i){
			res.n[i] = n[i] + rhs.n[i];
			if(res.n[i] >= mod[i]) res.n[i] -= mod[i];
		}
		return res;
	}
	LLI operator-(const LLI & rhs) const{
		LLI res;
		for(int i = 0; i < sz; ++i){
			res.n[i] = n[i] - rhs.n[i];
			if(res.n[i] < 0) res.n[i] += mod[i];
		}
		return res;
	}
	bool operator==(const LLI & rhs) const{
		for(int i = 0; i < sz; ++i){
			if(n[i] != rhs.n[i]) return false;
		}
		return true;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n), b(n);
	for(int & ai : a){
		cin >> ai;
	}
	for(int & bi : b){
		cin >> bi;
	}
	vector<LLI> ha(n), hb(n);
	for(int i = 0; i < n; ++i){
		ha[i] = (i>=1 ? ha[i-1] : 0) + LLI(x, a[i]);
		hb[i] = (i>=1 ? hb[i-1] : 0) + LLI(x, b[i]);
	}
	while(q--){
		int x, y, l;
		cin >> x >> y >> l;
		--x, --y;
		LLI sub_a = ha[x+l-1] - (x>=1 ? ha[x-1] : 0);
		LLI sub_b = hb[y+l-1] - (y>=1 ? hb[y-1] : 0);
		if(sub_a == sub_b){
			cout << "YES\n";
		}else{
			cout << "NO\n";
		}
	}
	return 0;
}