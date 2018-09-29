#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	double ans = 0;
	int d = 0;
	if(n <= 30){
		for(int i = 1; i <= n; ++i) ans += log10(i);
		d = floor(ans) + 1;
	}else{
		double PI = acos(-1.0);
		ans = n * log10(n) - n / log(10) + 0.5 * log10(2.0 * PI * n);
		d = floor(ans) + 1;
	}
	cout << n << "! tiene " << d << " digitos\n";
	return 0;
}