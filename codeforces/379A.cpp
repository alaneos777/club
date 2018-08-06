#include <bits/stdc++.h>

using namespace std;

int main(){
	int a, b, ans = 0, q, r = 0;
	cin >> a >> b;
	while(a >= 1){
		ans += a;
		q = (r + a) / b;
		r = (r + a) % b;
		a = q;
	}
	cout << ans;
	return 0;
}