#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

void combine(int a, int b, vector<lli> & A, vector<lli> & ans){
	ans.push_back(0);
	for(int i = a; i <= b; i++){
		int size = ans.size();
		for(int j = 0; j < size; j++){
			ans.push_back(ans[j] + A[i]);
		}
	}
	sort(ans.begin(), ans.end());
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	lli a, b;
	cin >> n >> a >> b;
	vector<lli> A(n);
	for(int i = 0; i < n; i++){
		cin >> A[i];
	}
	vector<lli> first, second;
	combine(0, (n - 1) / 2, A, first);
	combine((n - 1) / 2 + 1, n - 1, A, second);
	lli ans = 0;
	for(int i = 0; i < first.size(); i++){
		int j = upper_bound(second.begin(), second.end(), b - first[i]) - lower_bound(second.begin(), second.end(), a - first[i]);
		ans += j;
	}
	cout << ans;
	return 0;
}