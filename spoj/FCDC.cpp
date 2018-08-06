#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<int> primos;

void criba(int n){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
	int limit = sqrt(n);
	for(int i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(int j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

int pot(int n, int p){
	lli prod = p;
	int ans = 0;
	while(prod <= n){
		ans += n / prod;
		prod *= p;
	}
	return ans;
}

int exp_bin(int a, int b){
	int ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

int minimo(int p, int a){
	int left = 1, right = exp_bin(p, a), mid;
	while(left <= right){
		mid = left + (right - left) / 2;
		if(left == right) break;
		int exp = pot(mid, p);
		if(exp < a){
			left = mid + 1;
		}else if(exp > a){
			right = mid - 1;
		}else{
			right = mid;
		}
	}
	return mid;
}

int minimoFact(int n){
	int ans = 0;
	for(int & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			int exp = 0;
			while(n % p == 0){
				n /= p;
				exp++;
			}
			ans = max(ans, minimo(p, exp));
		}
	}
	if(n > 1) ans = max(ans, minimo(n, 1));
	return max(1, ans);
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(sqrt(1e7) + 1);
	int a, b;
	cin >> a >> b;
	cout << max(0, minimoFact(b) - minimoFact(a)) << "\n";
	return 0;
}