#include <bits/stdc++.h>
using namespace std;

int techo(int a, int b){
	return (a + b - 1) / b;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t, ang;
	cin >> t;
	while(t--){
		cin >> ang;
		int d = __gcd(180, ang);
		int m = techo(2 * d, 180 - ang);
		cout << 180 / d * m << "\n";
	}
	return 0;
}