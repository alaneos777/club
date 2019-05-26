#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
using ld = double;
const ld pi = acosl(-1.0l);

const int M = 4e6+10;
vector<ld> fact(M+1);

bool can(int n, int a){
	//ld lhs = 0.5*(log(2.0*pi)-log(n)) + n*(log(n+1.0/(12.0*n-1.0/(10.0*n)))-1.0);
	return fact[n]-n*log(a) > 1e-9;
}

int main(){
	for(int i = 1; i <= M; ++i){
		fact[i] = fact[i-1] + log(i);
	}
	int t, a;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &a);
		int l = 1, r = M;
		while(1){
			int m = (l + r) / 2;
			if(!can(m, a)){
				l = m + 1;
			}else{
				if(!can(m-1, a)){
					printf("%d\n", m);
					break;
				}else{
					r = m - 1;
				}
			}
		}
	}
	return 0;
}