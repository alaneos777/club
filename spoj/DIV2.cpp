#include <bits/stdc++.h>
using namespace std;

#define n 1000000

int n_divisores[n + 1];
int sizes[n + 1];
int divisores[n + 1][250];

void criba(){
	for(int i = 1; i <= n; i++){
		for(int j = i; j <= n; j += i){
			divisores[j][sizes[j]++] = i;
			++n_divisores[j];
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	criba();
	int cnt = 1;
	for(int i = 1; i <= n; ++i){
		if(n_divisores[i] > 3){
			bool test = true;
			for(int j = 0; j < sizes[i]; ++j){
				test &= !(n_divisores[i] % n_divisores[divisores[i][j]]);
				if(!test) break;
			}
			if(test){
				if(cnt % 108 == 0) cout << i << "\n";
				cnt++;
			}
		}
	}
	return 0;
}