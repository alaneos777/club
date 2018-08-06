#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b){
	int r;
	while(b != 0){
		r = a % b, a = b, b = r;
	}
	return a;
}

int main(){
	int N;
	while(cin >> N && N != 0){
		int cont = 0;
		int limit = (sqrt(2 * N - 1) - 1) / 2;
		for(int n = 1; n <= limit; n++){
			for(int m = n + 1; m <= sqrt(N - n * n); m += 2){
				if(gcd(m, n) == 1){
					cont += N / (m*m + n*n);
				}
			}
		}
		cout << cont << "\n";
	}
	return 0;
}