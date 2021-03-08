#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli pows[10][19];
int digits[10], N[10];

lli S(int len, int pos = 0, int prev = 0){
	if(pos == len){
		for(int p = 2; p <= len+1; p += 2){
			for(int sg : {-1, 1}){
				lli n = sg;
				for(int d = 0; d <= 9; ++d){
					n += digits[d]*pows[d][p];
					N[d] = 0;
				}
				lli x = n;
				for(int i = 0; i < len; ++i){
					N[x%10]++;
					x /= 10;
				}
				if(x == 0 && equal(N, N+10, digits)){
					return n;
				}
			}
		}
		return 0;
	}else{
		lli ans = 0;
		for(int d = prev; d <= 9; ++d){
			digits[d]++;
			ans += S(len, pos+1, d);
			digits[d]--;
		}
		return ans;
	}
}

int main(){
	for(int d = 0; d <= 9; ++d){
		pows[d][0] = 1;
		for(int i = 1; i <= 18; ++i){
			pows[d][i] = d*pows[d][i-1];
		}
	}
	cout << S(16) << "\n";
	return 0;
}