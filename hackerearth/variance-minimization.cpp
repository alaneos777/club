#include <stdio.h>
typedef long long int lli;

lli x[10010], y[10010];

lli round(lli a, lli b){
	return (2 * a + b) / (2 * b);
}

int main(){
	int t, n;
	scanf("%d", &t);
	for(int test = 1; test <= t; ++test){
		scanf("%d", &n);
		lli sum_xi = 0, sum_yi = 0, sum_xi2 = 0, sum_yi2 = 0;
		for(int i = 0; i < n; ++i){
			scanf("%lld %lld", &x[i], &y[i]);
			sum_xi += x[i];
			sum_yi += y[i];
			sum_xi2 += x[i] * x[i];
			sum_yi2 += y[i] * y[i];
		}
		lli min_var = n * (sum_xi2 + sum_yi2) - sum_xi * sum_xi - sum_yi * sum_yi;
		for(int idx = 0; idx < n; ++idx){
			lli xi = round(sum_xi - x[idx], n - 1);
			lli yi = round(sum_yi - y[idx], n - 1);
			lli new_sum_xi = sum_xi - x[idx] + xi;
			lli new_sum_yi = sum_yi - y[idx] + yi;
			lli new_sum_xi2 = sum_xi2 - x[idx] * x[idx] + xi * xi;
			lli new_sum_yi2 = sum_yi2 - y[idx] * y[idx] + yi * yi;
			lli new_var = n * (new_sum_xi2 + new_sum_yi2) - new_sum_xi * new_sum_xi - new_sum_yi * new_sum_yi;
			if(min_var == -1 || new_var < min_var){
				min_var = new_var;
			}
		}
		printf("%lld\n", min_var);
	}
	return 0;
}