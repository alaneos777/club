#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int c, n;
	cin >> c >> n;
	vector<int> cuentas(2*n), ceros(2*n), unos(2*n);
	for(int i = 0; i < n; ++i){
		cin >> cuentas[i];
		cuentas[i+n] = cuentas[i];
	}
	for(int i = 0; i < 2*n; ++i){
		ceros[i] = (i ? ceros[i-1] : 0) + (1 - cuentas[i]);
		unos[i] = (i ? unos[i-1] : 0) + cuentas[i];
	}
	auto get = [&](const vector<int> & source, int l, int r){
		if(l > r) r += n;
		return source[r] - (l ? source[l-1] : 0);
	};
	int ans = 1 << 30;
	for(int i = 0, j = 0; i < n; ++i){
		while(get(ceros, i, j) < c){
			j = (j + 1) % n;
		}
		ans = min(get(unos, i, j), ans);
	}
	cout << ans << "\n";
	return 0;
}