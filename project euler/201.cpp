#include <bits/stdc++.h>
using namespace std;

const int M = 100;
const int S = M * (M+1) * (2*M+1) / 6;

int8_t P[M/2+1][S+1];

int main(){
	P[0][0] = 1;
	for(int i = 1; i <= M; ++i){
		int r = i*i;
		int s = i*(i+1)*(2*i+1)/6;
		for(int j = min(i, M/2)-1; j >= 0; --j){
			for(int sum = 0; sum+r <= s; ++sum){
				P[j+1][sum+r] = min(P[j+1][sum+r] + P[j][sum], 2);
			}
		}
	}
	int ans = 0;
	for(int sum = 0; sum <= S; ++sum){
		if(P[M/2][sum] == 1) ans += sum;
	}
	cout << ans << "\n";
	return 0;
}