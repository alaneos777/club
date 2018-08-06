#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

template<typename T>
struct FenwickTree{
	int N;
	vector<T> bit;

	FenwickTree(int N){
		this->N = N;
		bit.assign(N, 0);
	}

	void update(int pos, T value){
		while(pos < N){
			bit[pos] += value;
			pos |= pos + 1;
		}
	}

	T query(int r){
		T res = 0;
		while(r >= 0){
			res += bit[r];
			r = (r & (r + 1)) - 1;
		}
		return res;
	}

	T query(int l, int r){
		return query(r) - query(l - 1);
	}
};

lli megaInversions(vector<int> & A){
	lli count = 0;
	int maximum = *max_element(A.begin(), A.end());
	FenwickTree<lli> BIT1(maximum + 1);
	FenwickTree<lli> BIT2(maximum + 1);
	for(int & a : A){
		BIT1.update(a, 1);
		BIT2.update(a, BIT1.query(a + 1, maximum));
		count += BIT2.query(a + 1, maximum);
	}
	return count;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	vector<int> A(n);
	for(int i = 0; i < n; ++i){
		cin >> A[i];
	}
	cout << megaInversions(A) << "\n";
	return 0;
}