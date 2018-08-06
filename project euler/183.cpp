#include <bits/stdc++.h>
using namespace std;

int p(int n){
	return (int)round(n / exp(1));
}

int gcd(int a, int b){
	int r;
	while(b != 0){
		r = a % b, a = b, b = r;
	}
	return a;
}

bool terminating(int num, int den){
	den /= gcd(num, den);
	while(den % 2 == 0) den /= 2;
	while(den % 5 == 0) den /= 5;
	return den == 1;
}

int main(){
	int sum = 0;
	for(int n = 5; n <= 10000; n++){
		if(terminating(n, p(n))){
			sum -= n;
		}else{
			sum += n;
		}
	}
	cout << sum << "\n";
	return 0;
}