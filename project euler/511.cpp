#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9;

vector<lli> getDivs(lli n){
	vector<lli> divs;
	for(lli d = 1; d*d <= n; ++d){
		if(n%d == 0){
			lli e = n/d;
			divs.push_back(d);
			if(e != d) divs.push_back(e);
		}
	}
	return divs;
}

vector<int> mult(const vector<int>& a, const vector<int>& b, int k){
	vector<int> c(k);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			int pos = i+j;
			if(pos >= k) pos -= k;
			c[pos] += (lli)a[i]*b[j] % mod;
			if(c[pos] >= mod) c[pos] -= mod;
		}
	}
	return c;
}

vector<int> power(const vector<int>& a, int k, lli n){
	vector<int> ans(k);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		ans = mult(ans, ans, k);
		if(n & p) ans = mult(ans, a, k);
	}while(p >>= 1);
	return ans;
}

lli Seq(lli n, int k){
	vector<int> P(k);
	for(lli d : getDivs(n)){
		P[(d+1)%k]++;
	}
	P = power(P, k, n);
	return P[0];
}

int main(){
	cout << Seq(1234567898765ll, 4321) << "\n";
	return 0;
}