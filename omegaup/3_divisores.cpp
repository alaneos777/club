#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

int main(){
	ull p, q, ans = 0;
	cin >> p >> q;
	p = ceil(sqrt(p));
	q = sqrt(q);
	vector<bool> es_primo(q + 1, true);
	es_primo[0] = es_primo[1] = false;
	for(ull i = 2; i <= q; ++i){
		if(es_primo[i]){
			if(p <= i){
				++ans;
			}
			for(ull j = i * i; j <= q; j += i){
				es_primo[j] = false;
			}
		}
	}
	cout << ans;
	return 0;
}