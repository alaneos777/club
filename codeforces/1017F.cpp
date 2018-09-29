#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	unsigned int a, b, c, d;
	cin >> n >> a >> b >> c >> d;
	vector<bool> p1((n + 20) / 6, true), p5((n + 20) / 6, true);
	auto isPrime = [&](int n){
		if(n == 2 || n == 3) return true;
		int r = n % 6;
		if(r == 1) return p1[(n - 1) / 6]==true;
		if(r == 5) return p5[(n + 1) / 6]==true;
		return false;
	};
	auto markComp = [&](int n){
		if(n != 2 && n != 3){
			int r = n % 6;
			if(r == 1) p1[(n - 1) / 6] = false;
			if(r == 5) p5[(n + 1) / 6] = false;
		}
	};
	for(int i = 3, l = sqrt(n); i <= l; i += 2){
		if(isPrime(i))
			for(int j = i*i; j <= n; j += 2*i)
				markComp(j);
	}
	unsigned int ans = 0;
	for(unsigned int p = 2; p <= n; ++p){
		if(isPrime(p)){
			unsigned int pot = 0;
			int curr = n;
			while(curr /= p) pot += curr;
			ans += pot * (((a * p + b) * p + c) * p + d);
		}
	}
	cout << ans << "\n";
	return 0;
}