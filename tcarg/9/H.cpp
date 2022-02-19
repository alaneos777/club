#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n+1);
	for(int i = 1; i <= n; ++i){
		cin >> a[i];
		a[i] += i;
	}
	sort(a.begin()+1, a.end());
	for(int i = 1; i <= n; ++i){
		a[i] -= i;
		if(a[i] < a[i-1]){
			cout << ":(\n";
			return 0;
		}
	}
	for(int i = 1; i  <= n; ++i){
		cout << a[i] << " ";
	}
	cout << "\n";
	return 0;
}