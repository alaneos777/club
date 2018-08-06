#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli maxPot(lli n, lli p, lli pot){
	lli div = p, ans = 0;
	while(div <= n){
		ans += n / div;
		div *= p;
	}
	return ans / pot;
}

vector<int> lowestPrime;
void criba(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; i ++) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2){
		if(lowestPrime[i] == i){
			for(int j = i * i; j <= n; j += 2 * i){
				if(lowestPrime[j] == j) lowestPrime[j] = i;
			}
		}
	}
}

int exp(int a, int b){
	int ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

int s(int n){
	int ans = 0;
	while(n != 1){
		int p = lowestPrime[n];
		int pot = 0;
		int left = 1, right = 1, m;
		while(n % p == 0){
			n /= p;
			right *= p;
			pot++;
		}
		if(pot <= p){
			m = p * pot;
		}else{
			while(left <= right){
				m = (left + right) / 2;
				if(left == right) break;
				int tmp = maxPot(m, p, pot);
				if(tmp > 1){
					right = m - 1;
				}else if(tmp < 1){
					left = m + 1;
				}else{
					right = m;
				}
			}
		}
		ans = max(ans, m);
	}
	return ans;
}

int main(){
	clock_t begin = clock();
	int limit = 1e8;
	criba(limit);
	lli sum = 0;
	for(int i = 2; i <= limit; i++){
		int term = s(i);
		sum += term;
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << sum << "\n";
	cout << fixed << setprecision(4) << elapsed_secs << "s";
	return 0;
}