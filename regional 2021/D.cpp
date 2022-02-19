#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	int M = 2e5;
	vector<lli> A(M);
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		A[ai]++;
	}
	lli carry = 0;
	for(int i = 0; i < M; ++i){
		A[i] += carry;
		carry = A[i]/2;
		A[i] %= 2;
	}
	while(carry){
		A.push_back(carry % 2);
		carry /= 2;
	}
	int cnt = 0;
	for(int i = 0; i < A.size(); ++i){
		if(A[i] == 1) cnt++;
	}
	if(cnt <= 2 && n > 1){
		cout << "Y\n";
	}else{
		cout << "N\n";
	}
	return 0;
}