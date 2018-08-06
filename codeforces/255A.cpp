#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, actual;
	cin >> n;
	vector< pair<int, string> > ans(3);
	ans[0].second = "chest";
	ans[1].second = "biceps";
	ans[2].second = "back";
	for(int i = 0; i < n; i++){
		cin >> actual;
		ans[i % 3].first += actual;
	}
	sort(ans.begin(), ans.end());
	cout << ans[2].second;
	return 0;
}