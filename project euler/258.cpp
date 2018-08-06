#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

const lli m = 20092010;
const int n = 2000;

lli *mult(lli *P, lli *Q){
	lli *R = new lli[n]();
	lli tmp;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			tmp = P[i] * Q[j];
			if(i + j < n){
				R[i + j] += tmp;
			}else{
				R[i + j - n] += tmp;
				R[i + j - n + 1] += tmp;
			}
		}
	}
	for(int i = 0; i < n; ++i){
		R[i] %= m;
	}
	return R;
}

int main(){
	lli k = 1e18;

	lli *coefAns = new lli[n]();
	lli *coefTmp = new lli[n]();
	coefAns[0] = 1;
	coefTmp[1] = 1;
	while(k){
		if(k & 1) coefAns = mult(coefAns, coefTmp);
		k >>= 1;
		if(k) coefTmp = mult(coefTmp, coefTmp);
	}

	lli F = 0;
	for(int i = 0; i < n; ++i){
		F += coefAns[i];
	}
	F %= m;
	cout << F << "\n";

	return 0;
}