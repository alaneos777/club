#include <bits/stdc++.h>
using namespace std;

void cribaDivisores(int n, vector<int> & suma){
	suma.resize(n + 1, 0);
	for(int i = 1; i <= n; i++){
		for(int j = i; j <= n; j += i){
			suma[j] += i;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	vector<int> suma;
	cribaDivisores(1000, suma);
	vector<int> ans(1001, -1);
	for(int i = 1; i <= 1000; i++){
		if(suma[i] <= 1000) ans[suma[i]] = max(ans[suma[i]], i);
	}
	int S, caso = 1;
	while(cin >> S && S != 0){
		cout << "Case " << (caso++) << ": " << ans[S] << "\n";
	}
	return 0;
}