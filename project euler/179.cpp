#include <bits/stdc++.h>
using namespace std;

vector<int> nDivisors;

void criba(int n){
	nDivisors.resize(n + 1, 0);
	for(int i = 1; i <= n; i++){
		for(int j = i; j <= n; j += i){
			nDivisors[j]++;
		}
	}
}

int main(){
	int n = 10000000;
	criba(n);
	int count = 0;
	for(int i = 2; i < n; i++){
		if(nDivisors[i] == nDivisors[i + 1]) count++;
	}
	cout << count << "\n";
}