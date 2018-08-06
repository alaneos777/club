#include <bits/stdc++.h>
using namespace std;

vector<int> divisores;

void criba(int n){
	divisores.resize(n + 1, 0);
	for(int i = 1; i <= n; i++){
		for(int j = i; j <= n; j += i){
			divisores[j] += i;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(500000);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		cout << divisores[n] - n << "\n";
	}
	return 0;
}