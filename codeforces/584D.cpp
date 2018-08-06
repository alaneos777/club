#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<bool> es_primo;
vector<lli> primos;

void criba(lli n){
	es_primo.resize(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	es_primo[2] = true;
	primos.push_back(2);
	for(lli i = 4; i <= n; i += 2){
		es_primo[i] = false;
	}
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

bool primeTest(lli n){
	if(n <= 31622){
		return es_primo[n];
	}else{
		for(lli & p : primos){
			if(p * p > n) break;
			if(n % p == 0) return false;
		}
		return true;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(31622);
	lli n;
	cin >> n;
	if(n == 3){
		cout << "1\n3\n";
	}else if(n == 4){
		cout << "2\n2 2\n";
	}else if(n == 5){
		cout << "2\n2 3\n";
	}else if(n == 6){
		cout << "2\n3 3\n";
	}else{
		n -= 3;
		lli a = 1, b = n - 1;
		while(a <= b){
			if(primeTest(a) && primeTest(b)) break;
			++a, --b;
		}
		cout << "3\n3 " << a << " " << b << "\n";
	}
	return 0;
}