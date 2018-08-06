#include <bits/stdc++.h>
using namespace std;

vector<int> numeros;

void criba(int n){
	numeros.push_back(1);
	vector<bool> free(n + 1, true);
	int limit = cbrt(n);
	for(int i = 2; i <= n; i++){
		if(free[i]){
			numeros.push_back(i);
			if(i <= limit){
				for(int j = i * i * i; j <= n; j += i * i * i){
					free[j] = false;
				}
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(1e6);
	int t, n;
	cin >> t;
	for(int i = 1; i <= t; i++){
		cin >> n;
		int pos = lower_bound(numeros.begin(), numeros.end(), n) - numeros.begin();
		if(numeros[pos] == n){
			cout << "Case " << i << ": " << pos + 1 << "\n";
		}else{
			cout << "Case " << i << ": Not Cube Free\n";
		}
	}
	return 0;
}