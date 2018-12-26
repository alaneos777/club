#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, h;
	cin >>n >> h;
	double h1 = h / sqrt(n);
	cout << fixed << setprecision(10) << h1 << " ";
	for(int i = 2; i < n; ++i){
		cout << fixed << setprecision(10) << h1 * sqrt(i) << " ";
	}
	return 0;
}