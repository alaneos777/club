#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> c(n), t(n);
	for(int& ci : c){
		cin >> ci;
	}
	for(int& ti : t){
		cin >> ti;
	}
	vector<int> x(n-1), y(n-1);
	for(int i = 0; i+1 < n; ++i){
		x[i] = c[i+1] - c[i];
		y[i] = t[i+1] - t[i];
	}
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());
	if(c[0] == t[0] && x == y){
		cout << "Yes\n";
	}else{
		cout << "No\n";
	}
	return 0;
}