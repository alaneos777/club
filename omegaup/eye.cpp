#include <bits/stdc++.h>
using namespace std;

const int maxi = 1e6;

int Phi[maxi+1];
void phiSieve(int n){
	for(int i = 1; i <= n; ++i) Phi[i] = i;
	for(int i = 2; i <= n; ++i){
		if(Phi[i] == i){
			for(int j = i; j <= n; j += i){
				Phi[j] -= Phi[j] / i;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int p, q;
	cin >> p >> q;
	phiSieve(q + 1);
	int m, n = -1;
	for(int i = p; i <= q; ++i){
		if(n == -1 || Phi[i] > m){
			m = Phi[i];
			n = i;
		}
	}
	cout << m << " " << n << "\n";
	return 0;
}