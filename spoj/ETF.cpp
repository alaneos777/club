#include <bits/stdc++.h>
using namespace std;

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

int phi(int n){
	int ans = n;
	for(int & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			while(n % p == 0){
				n /= p;
			}
			ans -= ans / p;
		}
	}
	if(n > 1) ans -= ans / n;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(1000);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		cout << phi(n) << "\n";
	}
	return 0;
}