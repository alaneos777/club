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

vector<bs> inverse(vector<bs> & A){
	int m = A.size(), n = A[0].sz, i = 0, j = 0;
	vector<bs> B(m, bs(n));
	for(int d = 0; d < m && d < n; ++d){
		B[d].set(d);
	}
	while(i < m && j < n){
		if(A[i][j] == 0){
			for(int k = i + 1; k < m; k++){
				if(A[k][j] != 0){
					swap(A[i], A[k]);
					swap(B[i], B[k]);
					break;
				}
			}
		}
		if(A[i][j] != 0){
			for(int k = 0; k < m; k++){
				if(k != i && A[k][j] != 0){
					A[k] ^= A[i];
					B[k] ^= B[i];
				}
			}
			i++;
		}
		j++;
	}
	return B;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<bs> A(n, bs(n));
	vector<pair<int, int>> pairs;
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;
		pairs.emplace_back(u-1, v-1);
		A[u-1].set(v-1);
	}
	A = inverse(A);
	for(const auto & par : pairs){
		int u, v;
		tie(u, v) = par;
		if(!A[v][u]){
			cout << "YES\n";
		}else{
			cout << "NO\n";
		}
	}
	return 0;
}