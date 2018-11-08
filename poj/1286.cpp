#include <iostream>
#include <vector>
#include <cmath>
typedef long long int lli;
using namespace std;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	lli k = 3;
	vector<lli> phi(31);
	for(int i = 1; i <= 30; ++i) phi[i] = i;
	for(int i = 2; i <= 30; ++i){
		if(phi[i] == i)
			for(int j = i; j <= 30; j += i)
				phi[j] -= phi[j] / i;
	}
	while(cin >> n && n != -1){
		if(n == 0){
			cout << "0\n";
			continue;
		}
		lli ans = 0;
		for(int d = 1, l = sqrt(n); d <= l; ++d){
			if(n % d > 0) continue;
			int d2 = n / d;
			ans += phi[d] * power(k, d2);
			if(d != d2)
				ans += phi[d2] * power(k, d);
		}
		ans /= n;
		if(n & 1){
			ans = (ans + power(k, (n + 1) / 2)) / 2;
		}else{
			ans = (2 * ans + (k + 1) * power(k, n / 2)) / 4;
		}
		cout << ans << "\n";
	}
	return 0;
}