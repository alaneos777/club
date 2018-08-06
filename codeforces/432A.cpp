#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, k, v, ans = 0;
	cin >> n >> k;
	for(int i = 0; i < n; i++){
		cin >> v;
		if(v + k <= 5) ans++;
	}
	cout << (ans / 3);
	return 0;
}