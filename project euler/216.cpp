#include <iostream>
using namespace std;
using lli = __int128;

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	b %= m;
	while(e){
		if(e & 1) ans = (ans * b) % m;
		e >>= 1;
		b = (b * b) % m;
	}
	return ans;
}

bool isPrime(lli n){
	if(n < 2) return false;
	if(n == 2) return true;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int i = 0; i < 16; ++i){
		lli a = 1 + rand() % (n - 1);
		lli m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) goto exit;
		for(int k = 0; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) goto exit;
		}
		return false;
		exit:;
	}
	return true;
}

int main(){
	srand(time(0));
	lli L = 5e7;
	int cnt = 0;
	for(lli n = 2; n <= L; ++n){
		if(isPrime(n*n*2-1)) cnt++;
	}
	cout << cnt << "\n";
	return 0;
}