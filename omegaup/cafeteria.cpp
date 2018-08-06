#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int tiempos[1010];
int c, n, d, t;

lli suma(lli ti){
	lli ans = 0;
	for(int i = 0; i < c; i++){
		ans += ti / tiempos[i];
	}
	return ans;
}

int main(){
	scanf("%d %d %d %d", &c, &n, &d, &t);
	int menor = 1 << 30;
	for(int i = 0; i < c; i++){
		scanf("%d", &tiempos[i]);
		menor = min(menor, tiempos[i]);
	}
	lli left = 1, k, right = 1ll << 40;
	while(right - left > 1){
		k = left + ((right - left) >> 1);
		lli sum = suma(k);
		if(sum < n){
			left = k;
		}else{
			right = k;
		}
	}
	if(right + 2 * d + menor <= t){
		printf("SI\n");
	}else{
		printf("NO\n");
	}
	return 0;
}