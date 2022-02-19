#include <bits/stdc++.h>
using namespace std;
 
inline bool get(uint64_t x, int i){
	return (x >> (63-i)) & 1;
}
 
int gauss(vector<uint64_t> & A){
	int m = A.size(), n = 64, i = 0, j = 0;
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
	int n;
	cin >> n;
	vector<uint64_t> A(n);
	for(uint64_t & ai : A){
		cin >> ai;
	}
	int rank = gauss(A);
	uint64_t ans = 0;
	for(int i = 0; i < rank; ++i){
		if((ans ^ A[i]) > ans){
			ans ^= A[i];
		}
	}
	cout << ans << "\n";
	return 0;
}