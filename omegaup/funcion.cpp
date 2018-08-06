#include <bits/stdc++.h>
using namespace std;

const int maxi = 1e6;

int Phi[maxi+1], ans[maxi+1];
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
	int p, pi;
	cin >> p;
	phiSieve(maxi);
	Phi[1] = 0, ans[1] = 1;
	for(int i = 2; i <= maxi; ++i){
		if(Phi[i] > Phi[ans[i - 1]]){
			ans[i] = i;
		}else{
			ans[i] = ans[i - 1];
		}
	}
	while(p--){
		cin >> pi;
		cout << ans[pi] << "\n";
	}
	return 0;
}