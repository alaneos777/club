#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<lli> ContinuedFraction(lli n){
	lli a0 = sqrt(n);
	vector<lli> coef = {a0};
	if(a0 * a0 != n){
		lli a = a0, p = 0, q = 1;
		do{
			p = a * q - p;
			q = (n - p * p) / q;
			a = (a0 + p) / q;
			coef.push_back(a);
		}while(q != 1);
	}
	return coef;
}

vector<lli> PellEquation(lli n){
	vector<lli> cf = ContinuedFraction(n);
	lli num = 0, den = 1;
	int k = cf.size() - 1;
	for(int i = ((k & 1) ? (2 * k - 1) : (k - 1)); i >= 0; i--){
		lli tmp = den;
		int pos = i % k;
		if(pos == 0 && i != 0) pos = k;
		den = num + cf[pos] * den;
		num = tmp;
	}
	return {den, num};
}

int main(){
	clock_t begin = clock();
	int dAns = 0, periodMax = 0;
	for(int d = 1; d <= 1000; d++){
		int k = ContinuedFraction(d).size() - 1;
		if(k & 1) k = 2 * k - 1;
		if(k >= periodMax){
			periodMax = k;
			dAns = d;
		}
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << dAns << "\n";
	cout << fixed << setprecision(4) << elapsed_secs << "s";
	return 0;
}