#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<int> tiempos;
int n, m;

lli suma(lli ti){
	lli ans = 0;
	for(int i = 0; i < n; i++){
		ans += ti / tiempos[i];
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	int mayor = 0;
	cin >> n >> m;
	tiempos.resize(n);
	for(int i = 0; i < n; i++){
		cin >> tiempos[i];
		mayor = max(tiempos[i], mayor);
	}
	lli left = 1, k, right = (lli)mayor * (lli)m;
	while(left < right){
		k = (left + right) >> 1;
		lli sum = suma(k);
		if(sum < m){
			left = k + 1;
		}else{
			right = k;
		}
	}
	cout << left << "\n";
	return 0;
}