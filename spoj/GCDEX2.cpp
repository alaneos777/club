#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long int lli;
 
vector<lli> phi;
void criba(int n){
	phi.resize(n + 1);
	for(int i = 1; i <= n; i++) phi[i] = (i & 1 ? i : i / 2);
	for(int i = 3; i <= n; i += 2){
		if(phi[i] == i){
			for(int j = i; j <= n; j += i){
				phi[j] -= phi[j] / i;
			}
		}
	}
}
 
lli sum_1(lli n){
	if(n & 1)
		return (n + 1) / 2 * n;
	else
		return n / 2 * (n + 1);
}
 
vector<lli> Tsmall;
unordered_map<lli, lli> Tbig;
 
lli T(lli n){
	if(n < Tsmall.size()){
		return Tsmall[n];
	}else{
		if(Tbig.count(n) == 0){
			lli m = sqrt(n), q2 = n / m;
			lli ans = sum_1(n);
			for(lli k = 2; k <= q2; k++){
				ans -= T(n / k);
			}
			for(lli k = 1; k < m; k++){
				ans -= (n / k - n / (k + 1)) * T(k);
			}
			Tbig[n] = ans;
		}
		return Tbig[n];
	}
}
 
lli S(lli n){
	lli ans = -sum_1(n);
	lli m = sqrt(n), q2 = n / m;
	for(lli k = 1; k <= q2; k++){
		ans += sum_1(n / k) * phi[k];
	}
	for(lli k = 1; k < m; k++){
		ans += (T(n / k) - T(n / (k + 1))) * sum_1(k);
	}
	return ans;
}
 
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	lli maximo = 0;
	int t;
	cin >> t;
	vector<lli> input(t);
	for(int i = 0; i < t; ++i){
		cin >> input[i];
		maximo = max(maximo, input[i]);
	}
	int limit = pow(maximo + 10, 2.0 / 3.0);
	criba(limit);
	Tsmall.resize(limit + 1);
	for(int i = 1; i <= limit; i++){
		Tsmall[i] = Tsmall[i - 1] + phi[i];
	}
	for(int i = 0; i < t; ++i){
		cout << S(input[i]) << "\n";
	}
	return 0;
}