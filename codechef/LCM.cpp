#include <bits/stdc++.h>
using namespace std;
typedef unsigned int lli;

const int M = 4e6;

int H[M + 1], acum[M + 1];

void sieve(int n){
	H[0] = 0; H[1] = 1;
	for(int i = 2; i <= n; i++) H[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2){
		if(H[i] == i){
			for(int j = i * i; j <= n; j += 2 * i){
				if(H[j] == j) H[j] = i;
			}
		}
	}
	for(int i = 2; i <= M; ++i){
		if(H[i] == i){
			H[i] = 1 - i;
		}else{
			int p = H[i];
			int m = i / p;
			if(m % p == 0){
				m /= p;
				if(m % p == 0){
					H[i] = 0;
				}else{
					H[i] = -H[m] * p;
				}
			}else{
				H[i] = H[m] * (1 - p);
			}
		}
	}
}

inline lli P1(lli n){
	if(n & 1) return (n + 1) / 2 * n;
	else return n / 2 * (n + 1);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	sieve(M);
	for(int i = 1; i <= M; ++i){
		acum[i] = acum[i - 1] + i * H[i];
	}
	int t;
	cin >> t;
	while(t--){
		int A, B;
		cin >> A >> B;
		lli ans = 0;
		if(A > B) swap(A, B);
		int i = 1;
		while(i <= A){
			lli p1 = P1(A / i), p2 = P1(B / i);
			int u = min(A / (A / i), B / (B / i));
			ans += p1 * p2 * (acum[u] - acum[i - 1]);
			i = u + 1;
		}
		cout << (ans & ((1u << 30) - 1)) << "\n";
	}
	return 0;
}