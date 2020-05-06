#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto lpSieve(int n){
	vector<int> lp(n+1, 2);
	for(int i = 1; i <= n; i += 2) lp[i] = i;
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j){
					lp[j] = i;
				}
			}
		}
	}
	return lp;
}

const int M = 120000 - 1;
const auto lp = lpSieve(M);

int getRad(int n){
	int ans = 1;
	while(n > 1){
		int p = lp[n];
		while(n % p == 0){
			n /= p;
		}
		ans *= p;
	}
	return ans;
}

vector<int> rad(M+1);

int main(){
	for(int i = 1; i <= M; ++i){
		rad[i] = getRad(i);
	}
	lli sum = 0;
	for(int c = 2; c <= M; ++c){
		for(int a = 1, b = c-1; a < b; ++a, --b){
			if(__gcd(a, b) == 1 && (lli)rad[a] * rad[b] * rad[c] < c){
				cout << a << " " << b << " " << c << "\n";
				sum += c;
			}
		}
	}
	cout << sum << "\n";
	return 0;
}