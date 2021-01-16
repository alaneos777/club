#include <bits/stdc++.h>
using namespace std;

struct bs{
	vector<uint64_t> a;
	size_t sz;

	bs(){}
	bs(size_t sz): sz(sz), a((sz + 63) >> 6) {}

	bool operator[](size_t i) const{
		return (a[i >> 6] >> (63-(i & 63))) & 1;
	}

	bool operator>(const bs& rhs) const{
		return a > rhs.a;
	}

	void set(size_t i){
		a[i >> 6] |= (1ll << (63-(i & 63)));
	}

	void flip(size_t i){
		a[i >> 6] ^= (1ll << (63-(i & 63)));
	}

	bs& operator^=(const bs& rhs){
		for(size_t i = 0; i < a.size(); ++i){
			a[i] ^= rhs.a[i];
		}
		return *this;
	}
};

inline bool get(int x, int i){
	return (x >> (9-i)) & 1;
}

int gauss(vector<int> & A){
	int m = A.size(), n = 10, i = 0, j = 0;
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
		int n, k;
		cin >> n >> k;
		vector<int> A(n);
		for(int & ai : A){
			cin >> ai;
		}
		int rank = gauss(A);
		int ans = k;
		for(int i = 0; i < rank; ++i){
			if((ans ^ A[i]) > ans){
				ans ^= A[i];
			}
		}
		cout << ans << "\n";
	}
	return 0;
}