#include <bits/stdc++.h>
using namespace std;
typedef int ull;

void criba(ull n, vector<ull> & n_divisores){
	n_divisores.resize(n + 1, 0);
	for(ull i = 1; i <= n; ++i){
		for(ull j = i; j <= n; j += i){
			n_divisores[j]++;
		}
	}
}

int main(){
	ull n, ans;
	ull limite = 1100000;
	cin >> n;
	vector<ull> n_divisores;
	criba(limite + 1, n_divisores);
	ull sup = n + 1;
	ull inf = n - 1;
	while(true){
		if(sup <= limite && n_divisores[sup] == n_divisores[n]){
			ans = sup;
			break;
		}
		if(inf > 0 && n_divisores[inf] == n_divisores[n]){
			ans = inf;
			break;
		}
		++sup;
		--inf;
	}
	cout << ans;
	return 0;
}