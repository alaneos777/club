#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int cover(int a, int b, int c, int n){
	return 2*(a*b + a*c + b*c) + 4*(n-1)*(a+b+c) + 4*(n-1)*(n-2);
}

int main(){
	int M = 20000;
	vector<int> cnt(M+1);
	for(int a = 1; cover(a, 1, 1, 1) <= M; ++a){
		for(int b = a; cover(a, b, 1, 1) <= M; ++b){
			for(int c = b; cover(a, b, c, 1) <= M; ++c){
				for(int n = 1; cover(a, b, c, n) <= M; ++n){
					cnt[cover(a, b, c, n)]++;
				}
			}
		}
	}
	for(int val = 1; val <= M; ++val){
		if(cnt[val] == 1000){
			cout << val << "\n";
			break;
		}
	}
	return 0;
}