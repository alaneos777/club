#include <bits/stdc++.h>
using namespace std;
using lli = long long;

template<typename T>
struct SegmentTreeDin{
	SegmentTreeDin *left, *right;
	int l, r;
	T value, lazy;
 
	SegmentTreeDin(int start, int end): left(NULL), right(NULL), l(start), r(end), value(0), lazy(0){
		if(l == r) return;
		else{
			int half = l + ((r - l) >> 1);
			left = new SegmentTreeDin(l, half);
			right = new SegmentTreeDin(half+1, r);
			value = left->value + right->value;
		}
	}
 
	void propagate(T dif){
		value += (r - l + 1) * dif;
		if(l != r){
			left->lazy += dif;
			right->lazy += dif;
		}
	}
 
	T query(int start, int end){
		if(lazy != 0){
			propagate(lazy);
			lazy = 0;
		}
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return value;
		else return left->query(start, end) + right->query(start, end);
	}
 
	void update(int start, int end, T dif){
		if(lazy != 0){
			propagate(lazy);
			lazy = 0;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end) propagate(dif);
		else{
			left->update(start, end, dif);
			right->update(start, end, dif);
			value = left->value + right->value;
		}
	}

	void update(int i, T value){
		update(i, i, value);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<lli> a(n);
	for(lli & ai : a) cin >> ai;
	SegmentTreeDin<lli> st(0, n - 1);
	while(q--){
		int l, r;
		cin >> l >> r;
		--l, --r;
		st.update(l, r, 1);
	}
	vector<lli> b(n);
	for(int i = 0; i < n; ++i) b[i] = st.query(i, i);
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	lli ans = 0;
	for(int i = 0; i < n; ++i){
		ans += a[i] * b[i];
	}
	cout << ans << "\n";
	return 0;
}