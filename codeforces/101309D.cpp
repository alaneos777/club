#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-9;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	if(fopen("dome.in", "r")){
		freopen("dome.in", "r", stdin);
		freopen("dome.out", "w", stdout);
	}
	int n;
	cin >> n;
	vector<ld> x(n), y(n), z(n);
	for(int i = 0; i < n; ++i){
		cin >> x[i] >> y[i] >> z[i];
	}
	auto V = [&](ld h){
		ld r = 0;
		for(int i = 0; i < n; ++i){
			r = max(r, h * hypotl(x[i], y[i]) / (h - z[i]));
		}
		return make_pair(r, r*r*h);
	};
	ld lo = *max_element(z.begin(), z.end()), hi = 1e18;
	while(abs(lo - hi) >= eps){
		ld izq = lo + (hi - lo) / 3;
		ld der = hi - (hi - lo) / 3;
		if(V(izq).second > V(der).second){
			lo = izq;
		}else{
			hi = der;
		}
	}
	ld h = (lo + hi) / 2;
	auto[r, vol] = V(h);
	cout << fixed << setprecision(3) << h << " " << r << "\n";
	return 0;
}