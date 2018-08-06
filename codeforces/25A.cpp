#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, v;
	vector<int> pares, impares;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> v;
		if(v % 2 == 0) pares.push_back(i + 1);
		else impares.push_back(i + 1);
	}
	if(pares.size() == 1) cout << pares[0];
	else cout << impares[0];
	return 0;
}