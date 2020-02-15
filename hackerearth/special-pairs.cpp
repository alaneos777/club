#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int near(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

void fwt(vector<lli> & A, int inv){
	int n = A.size();
	for(int k = 1; k < n; k <<= 1)
		for(int i = 0; i < n; i += k << 1)
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = A[i + j + k];
				if(inv == -1){
					A[i + j] = u - v;
				}else{
					A[i + j] = u + v;
				}
			}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<lli> a;
		for(int i = 0; i < n; ++i){
			int pos;
			cin >> pos;
			if(pos >= a.size()) a.resize(pos+1);
			a[pos]++;
		}
		a.resize(near(a.size()));
		fwt(a, 1);
		for(lli & ai : a){
			ai *= ai;
		}
		fwt(a, -1);
		cout << a[0] << "\n";
	}
	return 0;
}