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

int divisores(int n){
	int ans = 1;
	for(int & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			int pot = 0;
			while(n % p == 0){
				n /= p;
				pot++;
			}
			ans *= pot + 1;
		}
	}
	if(n > 1) ans *= 2;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(sqrt(1e9) + 1);
	int a, b, n, cnt = 0;
	cin >> a >> b >> n;
	for(int i = a; i <= b; i++){
		if(divisores(i) == n) cnt++;
	}
	cout << cnt << "\n";
	return 0;
}