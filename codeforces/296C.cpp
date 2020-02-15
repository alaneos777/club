#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

template<typename T>
struct SegmentTreeDin{
	SegmentTreeDin *left, *right;
	int l, r;
	T sum, lazy;
 
	SegmentTreeDin(int start, int end, const vector<T> & arr): left(NULL), right(NULL), l(start), r(end), sum(0), lazy(0){
		if(l == r) sum = arr[l];
		else{
			int half = l + ((r - l) >> 1);
			left = new SegmentTreeDin(l, half, arr);
			right = new SegmentTreeDin(half+1, r, arr);
			sum = left->sum + right->sum;
		}
	}
 
	void propagate(T dif){
		sum += (r - l + 1) * dif;
		if(l != r){
			left->lazy += dif;
			right->lazy += dif;
		}
	}
 
	T sum_query(int start, int end){
		if(lazy != 0){
			propagate(lazy);
			lazy = 0;
		}
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return sum;
		else return left->sum_query(start, end) + right->sum_query(start, end);
	}
 
	void add_range(int start, int end, T dif){
		if(lazy != 0){
			propagate(lazy);
			lazy = 0;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end) propagate(dif);
		else{
			left->add_range(start, end, dif);
			right->add_range(start, end, dif);
			sum = left->sum + right->sum;
		}
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<lli> a(n);
	for(lli & ai : a){
		cin >> ai;
	}
	SegmentTreeDin<lli> st(0, n-1, a);
	SegmentTreeDin<lli> st_oper(0, m-1, vector<lli>(m));
	vector<tuple<int, int, lli>> operations;
	for(int i = 0; i < m; ++i){
		int l, r; lli d;
		cin >> l >> r >> d;
		operations.emplace_back(l, r, d);
	}
	for(int i = 0; i < k; ++i){
		int x, y;
		cin >> x >> y;
		st_oper.add_range(x-1, y-1, 1);
	}
	for(int i = 0; i < m; ++i){
		int l, r; lli d;
		tie(l, r, d) = operations[i];
		st.add_range(l-1, r-1, d*st_oper.sum_query(i, i));
	}
	for(int i = 0; i < n; ++i){
		cout << st.sum_query(i, i) << " ";
	}
	cout << "\n";
	return 0;
}