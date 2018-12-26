#include <bits/stdc++.h>
using namespace std;

int sum(int x){
	int s = 0;
	do{
		int r = x % 10;
		s += r;
		x /= 10;
	}while(x);
	return s;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, ans = 0;
	cin >> n;
	for(int a = 1; a < n; ++a){
		int b = n - a;
		int t = sum(a) + sum(b);
		if(a == 1 || t < ans) ans = t;
	}
	cout << ans << "\n";
	return 0;
}