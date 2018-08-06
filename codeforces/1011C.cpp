#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(n), c;
	for(int i = 0; i < n; ++i){
		cin >> a[i];
	}
	for(int i = 0; i < n; ++i){
		cin >> b[i];
	}
	for(int i = 0; i < n; ++i){
		c.push_back(a[i]);
		c.push_back(b[(i+1)%n]);
	}
	double l = 0, r = 2e9;
	auto func = [&](double x){
		double curr = m + x;
		double fuel = x;
		for(int i = 0; i < 2*n; ++i){
			double rest = curr / c[i];
			if(fuel - rest >= 0){
				curr -= rest;
				fuel -= rest;
				//cout << curr << " " << fuel << "\n";
			}else{
				return false;
			}
		}
		return true;
	};
	while(abs(l - r) >= 1e-10){
		double m = (l + r) / 2;
		if(func(m)) r = m;
		else l = m;
	}
	if(abs(l - 2e9) < 1e-6) cout << "-1\n";
	else cout << fixed << setprecision(10) << l << "\n";
	return 0;
}