#include <bits/stdc++.h>

using namespace std;

int main(){
	int n;
	cin >> n;
	vector<int> valores(n);
	for(int i=0;i<n;i++) cin >> valores[i];
	int minimo = valores[0], maximo = valores[0], pos_max = 0, pos_min = 0;
	for(int i=1;i<n;i++){
		if(valores[i] > maximo){
			maximo = valores[i];
			pos_max = i;
		}
		if(valores[i] <= minimo){
			minimo = valores[i];
			pos_min = i;
		}
	}
	int ans = pos_max + n - pos_min - 1;
	if(pos_max > pos_min) ans--;
	cout << ans;
	return 0;
}