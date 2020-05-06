#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, p;
	cin >> n >> m >> p;
	vector<int> a(n), b(m);
	for(int & ai : a){
		cin >> ai;
	}
	for(int & bi : b){
		cin >> bi;
	}
	int i_a, i_b;
	for(int i = 0; i < n; ++i){
		if(a[i] % p != 0){
			i_a = i;
			break;
		}
	}
	for(int i = 0; i < m; ++i){
		if(b[i] % p != 0){
			i_b = i;
			break;
		}
	}
	cout << i_a+i_b << "\n";
	return 0;
}