#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, s, fi, ti, ans = 0;
	cin >> n >> s;
	vector<int> info(s + 1, 0);
	for(int i = 1; i <= n; i++){
		cin >> fi >> ti;
		info[fi] = max(info[fi], ti);
	}
	for(int i = s; i >= 1; i--){
		if(ans < info[i]) ans = info[i];
		ans++;
	}
	cout << ans;
	return 0;
}