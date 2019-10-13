#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> Phi;

void phiSieve(int n){
	Phi.resize(n+1);
	iota(Phi.begin(), Phi.end(), 0);
	for(int i = 2; i <= n; ++i){
		if(Phi[i] == i){
			for(int j = i; j <= n; j += i){
				Phi[j] -= Phi[j] / i;
			}
		}
	}
}

lli sumTau(lli n){
	lli ans = 0;
	lli i = 1;
	while(i <= n){
		lli ni = n / i;
		lli u = n / ni;
		ans += (u - (i - 1)) * (n / i);
		i = u + 1;
	}
	return ans;
}

lli S(lli n){
	lli ans = 0;
	lli m = sqrt(n);
	for(lli i = 1; i <= m; ++i){
		ans += Phi[i] * sumTau(n / (i * i));
	}
	return ans;
}

int main(){
	lli n = 1e15;
	phiSieve(sqrt(n) + 10);
	cout << S(n) << "\n";
	return 0;
}