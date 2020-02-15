#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int mex(const vector<int> & a){
	int n = a.size();
	vector<bool> b(n);
	for(int ai : a){
		if(ai < n) b[ai] = true;
	}
	for(int i = 0; i < n; ++i){
		if(!b[i]) return i;
	}
	return n;
}

vector<vector<int>> getDivs(int n){
	vector<vector<int>> ans(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			if(i != j)
				ans[j].push_back(i);
		}
	}
	return ans;
}

const vector<vector<int>> divs = getDivs(100);

const lli mod = 1234567890ll;

inline lli valid(lli n, int a){
	return ((n + (1ll << a)) >> (a+1)) % mod;
}

int main(){
	/*vector<int> mem(101, -1);
	function<int(int)> g = [&](int a){
		if(mem[a] != -1) return mem[a];
		vector<int> conj;
		for(int d : divs[a]){
			if(a-d >= 0){
				conj.push_back(g(a-d));
			}
		}
		return mem[a] = mex(conj);
	};
	for(int i = 1; i <= 100; ++i){
		cout << "g(" << i << ") = " << g(i) << "\n";
	}*/
	lli n = 123456787654321ll;
	int lg = log2l(n);
	lli ans = (n%mod) * (n%mod) % mod * (n%mod) % mod;
	for(int a = 0; a <= lg; ++a){
		for(int b = 0; b <= lg; ++b){
			if((a ^ b) <= lg){
				(ans -= valid(n, a) * valid(n, b) % mod * valid(n, a ^ b)) %= mod;
			}
		}
	}
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}