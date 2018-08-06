#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, total = 0, suma = 0, ans = 0;
	cin >> n;
	vector<int> monedas(n);
	for(int i=0;i<n;i++){
		cin >> monedas[i];
		total += monedas[i];
	}
	sort(monedas.begin(), monedas.end());
	for(int i=n-1;i>=0;i--){
		total -= monedas[i];
		suma += monedas[i];
		ans++;
		if(suma > total) break;
	}
	cout << ans;
	return 0;
}