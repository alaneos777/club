#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
 
vector<int> Mu;
void muSieve(int n){
	Mu.resize(n + 1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(Mu[i]){
			for(int j = 2*i; j <= n; j += i){
				Mu[j] -= Mu[i];
			}
		}
	}
}
 
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; ++i){
		cin >> a[i];
	}
	int M = *max_element(begin(a), end(a));
	vector<int> freq(M + 1);
	vector<lli> f(M + 1);
	for(int i = 0; i < n; ++i){
		freq[a[i]]++;
	}
	muSieve(M);
	for(int i = 1; i <= M; i++){
		for(int j = i; j <= M; j += i){
			f[i] += freq[j];
		}
	}
	lli ans = 0;
	for(int k = 1; k <= M; ++k){
		ans += Mu[k] * (f[k] * (f[k] - 1) * (f[k] - 2) / 6);
	}
	cout << ans << "\n";
	return 0;
}