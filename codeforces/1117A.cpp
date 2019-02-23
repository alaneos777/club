#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, M = 0;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
		M = max(M, ai);
	}
	int length = 0, consec = 0;
	for(int i = 0; i < n; ++i){
		if(a[i] == M){
			consec++;
		}else{
			if(consec > 0){
				length = max(length, consec);
			}
			consec = 0;
		}
	}
	if(consec > 0){
		length = max(length, consec);
	}
	cout << length << "\n";
	return 0;
}