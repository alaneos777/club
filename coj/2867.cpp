#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long int lli;

vector<lli> lowestPrime;
void lowestPrimeSieve(lli n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(lli i = 2; i <= n; i++) lowestPrime[i] = (i & 1 ? i : 2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= limit; i += 2){
		if(lowestPrime[i] == i){
			for(lli j = i * i; j <= n; j += 2 * i){
				if(lowestPrime[j] == j) lowestPrime[j] = i;
			}
		}
	}
}

lli mod = 123457;

lli expBin(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli lcmSum(lli n){
	lli n0 = n;
	lli ans = 1;
	while(n > 1){
		lli p = lowestPrime[n];
		int a = 0;
		while(n % p == 0){
			n /= p;
			++a;
		}
		ans *= (1 + expBin(p, 2 * a + 1)) / (p + 1);
	}
	return n0 * (1 + ans) / 2 % mod;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	lowestPrimeSieve(1e6 +10);
	vector<lli> acum(1e6 + 1);
	for(int i = 1; i <= 1e6; ++i){
		acum[i] = (acum[i - 1] + lcmSum(i)) % mod;
	}
	int n;
	while(cin >> n){
		cout << acum[n] << "\n";
	}
	return 0;
}