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

int main(){
	clock_t begin = clock();
	int count = 0;
	for(int i = 1; i <= 10000; i++){
		if(ContinuedFraction(i).size() % 2 == 0){
			count++;
		}
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << count << "\n";
	cout << fixed << setprecision(4) << elapsed_secs << "s";
	return 0;
}