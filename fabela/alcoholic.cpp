#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, x;
	cin >> n >> x;
	vector<int> v(n), p(n);
	for(int i = 0; i < n; ++i){
		cin >> v[i] >> p[i];
	}
	x *= 100;
	int total = 0;
	int ans = -1;
	for(int i = 0; i < n; ++i){
		total += v[i]*p[i];
		if(total > x){
			ans = i+1;
			break;
		}
	}
	cout << ans << "\n";
	return 0;
}