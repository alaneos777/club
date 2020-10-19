#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<lli> a(n);
	for(lli & ai : a){
		cin >> ai;
	}
	sort(a.begin(), a.end());
	bool can = false;
	for(int i = 0; i+2 < n; ++i){
		can |= a[i] + a[i+1] > a[i+2];
	}
	if(can) cout << "possible\n";
	else cout << "impossible\n";
	return 0;
}