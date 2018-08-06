#include <bits/stdc++.h>
using namespace std;

vector<int> primos;
vector<bool> es_primo;

void criba(int n){
	es_primo.resize(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	for(int i = 4; i <= n; i += 2){
		es_primo[i] = false;
	}
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

int main(){
	ios_base::sync_with_stdio(0);
	criba(10000);
	int t, n;
	cin >> t;
	for(int i = 1; i <= t; i++){
		cin >> n;
		cout << i << ":";
		if(!es_primo[n]){
			cout << "NOTPRIME\n";
		}else if(n == 3){
			cout << "2\n";
		}else{
			cout << "1\n";
		}
	}
	return 0;
}