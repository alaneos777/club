#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a) cin >> ai;
	sort(a.begin(), a.end());
	if(n & 1) cout << a[n/2] << "\n";
	else cout << a[n/2-1] << "\n";
	return 0;
}