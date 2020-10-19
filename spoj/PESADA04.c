#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dist[11][11], mem[2048][11];
int n;

int min(int a, int b){
	return a < b ? a : b;
}

int f(int mask, int i){
	int *ans = &mem[mask][i];
	if(*ans != -1) return *ans;
	if(__builtin_popcount(mask) == 2){
		return *ans = dist[0][i];
	}else{
		*ans = 2e9;
		for(int j = 1; j < n; ++j){
			if(j != i && (mask & (1 << j))){
				*ans = min(*ans, f(mask & ~(1 << i), j) + dist[j][i]);
			}
		}
		return *ans;
	}
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		++n;
		memset(dist, 0, sizeof(dist));
		memset(mem, -1, sizeof(mem));
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				if(i != j) scanf("%d", &dist[i][j]);
			}
		}
		int ans = 2e9;
		for(int i = 1; i < n; ++i){
			ans = min(ans, f((1 << n) - 1, i) + dist[i][0]);
		}
		printf("%d\n", ans);
	}
	return 0;
}