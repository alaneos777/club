#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for(int i = 0; i < n; ++i){
		cin >> a[i];
	}
	lli acum = 0;
	for(int i = 0; i < n; ++i){
		lli bef = acum / m;
		acum += a[i];
		lli aft = acum / m;
		cout << (aft - bef) << "\n";
	}
	return 0;
}