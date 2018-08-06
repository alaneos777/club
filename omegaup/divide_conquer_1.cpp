#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	vector<ull> A(n);
	for(int i = 0; i < n; ++i){
		cin >> A[i];
	}
	ull ans = A[0];
	ull tmp_max = A[0];
	for(int i = 1; i < n; ++i){
		tmp_max = max(tmp_max + A[i], A[i]);
		ans = max(tmp_max, ans);
	}
	cout << ans;
	return 0;
}