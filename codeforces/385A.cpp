#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, c;
	cin >> n >> c;
	vector<int> info(n);
	for(int i = 0; i < n; i++) cin >> info[i];
	int ans = 0;
	for(int i = 0; i < n - 1; i++){
		int tmp = info[i] - info[i + 1] - c;
		if(tmp > ans) ans = tmp;
	}
	cout << ans;
}