#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

void fwt(vector<int>& a){
	int n = a.size();
	for(int sz = 2; sz <= n; sz <<= 1){
		for(int start = 0; start < n; start += sz){
			for(int j = 0; j < sz/2; ++j){
				a[start+j+sz/2] ^= a[start+j];
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(1<<20);
	for(int i = 0; i < n; ++i){
		cin >> a[n-1-i];
	}
	fwt(a);
	for(int i = 1; i <= m; ++i){
		if(i > 1) cout << " ";
		cout << a[(1<<20)-i];
	}
	cout << "\n";
	return 0;
}