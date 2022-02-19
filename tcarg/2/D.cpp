#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string a, b;
	cin >> a >> b;
	int k;
	cin >> k;
	int sz = a.size();
	a += a;
	a.pop_back();
	lli x = 0, y = 0;
	int n = 0;
	if(equal(a.begin(), a.begin()+sz, b.begin())){
		x = 1;
		n = 1;
	}else{
		y = 1;
	}
	for(int i = 1; i < sz; ++i){
		if(equal(a.begin()+i, a.begin()+i+sz, b.begin())) n++;
	}
	int m = sz - n;
	for(int i = 1; i <= k; ++i){
		tie(x, y) = make_pair((x*(n-1) + y*n) % mod, (x*m + y*(m-1)) % mod);
	}
	cout << x << "\n";
	return 0;
}