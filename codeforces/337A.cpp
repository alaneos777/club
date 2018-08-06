#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, m, dif, minimo = 1e9;
	cin >> n >> m;
	vector<int> f(m);
	for(int i=0;i<m;i++) cin >> f[i];
	sort(f.begin(), f.end());
	for(int i=0;i<m-n+1;i++){
		dif = f[i+n-1] - f[i];
		if(dif < minimo) minimo = dif;
	}
	cout << minimo;
	return 0;
}