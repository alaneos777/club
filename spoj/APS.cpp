#include <bits/stdc++.h>
using namespace std;

vector<int> f;
vector<long long int> a;

void criba(int n){
	f.resize(n + 1, 0);
	a.resize(n + 1, 0);
	int limit = sqrt(n);
	for(int i = 2; i <= n; i++){
		if(f[i] == 0){
			f[i] = i;
			if(i <= limit){
				for(int j = i * i; j <= n; j += i){
					if(f[j] == 0){
						f[j] = i;
					}
				}
			}
		}
		a[i] = a[i - 1] + f[i];
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(10000000);
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		cout << a[n] << "\n";
	}
	return 0;
}