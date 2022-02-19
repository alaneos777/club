#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

inline bool get(uint32_t x, int i){
	return (x >> (31-i)) & 1;
}
 
int gauss(vector<uint32_t> & A){
	int m = A.size(), n = 63, i = 0, j = 0;
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
	vector<uint32_t> A(n);
	for(uint32_t & ai : A){
		cin >> ai;
	}
	for(int i = 1; i < n; ++i){
		A[i] ^= A[i-1];
	}
	if(A[n-1] == 0){
		cout << "-1\n";
	}else{
		int rank = gauss(A);
		cout << rank << "\n";
	}
	return 0;
}