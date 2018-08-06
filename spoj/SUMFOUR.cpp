#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	lli ans = 0;
	vector<int> A(n), B(n), C(n), D(n);
	for(int i = 0; i < n; i++){
		cin >> A[i] >> B[i] >> C[i] >> D[i];
	}
	vector<int> first;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			first.push_back(A[i] + B[j]);
		}
	}
	sort(first.begin(), first.end());
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			auto key = equal_range(first.begin(), first.end(), -C[i] - D[j]);
			ans += key.second - key.first;
		}
	}
	cout << ans << "\n";
	return 0;
}