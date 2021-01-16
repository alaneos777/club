#include <bits/stdc++.h>
using namespace std;

int k;

inline bool get(uint32_t x, int i){
	return (x >> (k-1-i)) & 1;
}

int gauss(vector<uint32_t> & A){
	int m = A.size(), n = k, i = 0, j = 0;
	while(i < m && j < n){
		if(get(A[i], j) == 0){
			for(int k = i + 1; k < m; k++){
				if(get(A[k], j) != 0){
					swap(A[i], A[k]);
					break;
				}
			}
		}
		if(get(A[i], j) != 0){
			for(int k = 0; k < m; k++){
				if(k != i && get(A[k], j) != 0){
					A[k] ^= A[i];
				}
			}
			i++;
		}
		j++;
	}
	return i;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int m;
		cin >> k >> m;
		vector<uint32_t> A(m);
		for(uint32_t & ai : A){
			cin >> ai;
		}
		int rank = gauss(A);
		cout << (uint32_t(1) << (k-rank)) << "\n";
	}
	return 0;
}