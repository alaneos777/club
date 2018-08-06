#include <bits/stdc++.h>
using namespace std;

void criba(int n, vector<bool> & es_primo){
	es_primo.resize(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	es_primo[2] = true;
	for(int i = 4; i <= n; i += 2){
		es_primo[i] = false;
	}
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2){
		if(es_primo[i]){
			for(int j = i * i; j <= n; j += 2 * i){
				es_primo[j] = false;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	vector<bool> es_primo;
	criba(1000000, es_primo);
	int n;
	while(cin >> n && n != 0){
		int a = 1, b = n - 1;
		while(a <= b){
			if(es_primo[a] && es_primo[b]) break;
			++a, --b;
		}
		cout << n << " = " << a << " + " << b << "\n";
	}
	return 0;
}