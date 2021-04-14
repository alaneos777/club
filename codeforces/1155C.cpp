#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<lli> x(n), p(m);
	for(lli& xi : x){
		cin >> xi;
	}
	for(lli& pi : p){
		cin >> pi;
	}
	if(n == 1){
		cout << "YES\n";
		cout << x[0] << " " << 1 << "\n";
	}else{
		lli g = 0;
		for(int i = 1; i < n; ++i){
			g = __gcd(g, x[i] - x[i-1]);
		}
		int idx = -1;
		for(int i = 0; i < m; ++i){
			if(g % p[i] == 0){
				idx = i;
				break;
			}
		}
		if(idx == -1){
			cout << "NO\n";
		}else{
			cout << "YES\n";
			cout << x[0] << " " << idx+1 << "\n";
		}
	}
	return 0;
}