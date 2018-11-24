#include <bits/stdc++.h>
using namespace std;

const int M = 1e6 + 10;

int Two[M+1], Five[M+1];

inline void calc(int x, int & two, int & five, int & zero){
	two += Two[x];
	five += Five[x];
	zero += (x == 0);
}

struct SegmentTreeDin{
	SegmentTreeDin *left, *right;
	int l, r;
	int two, five, zero, lazy;
 
	SegmentTreeDin(int start, int end, vector<int> & arr): left(NULL), right(NULL), l(start), r(end), two(0), five(0), zero(0), lazy(-1){
		if(l == r) calc(arr[l], two, five, zero);
		else{
			int half = l + ((r - l) >> 1);
			left = new SegmentTreeDin(l, half, arr);
			right = new SegmentTreeDin(half+1, r, arr);
			two = left->two + right->two;
			five = left->five + right->five;
			zero = left->zero + right->zero;
		}
	}
 
	void propagate(int dif){
		two = five = zero = 0;
		calc(dif, two, five, zero);
		two *= r - l + 1;
		five *= r - l + 1;
		zero *= r - l + 1;
		if(l != r){
			left->lazy = dif;
			right->lazy = dif;
		}
	}
 
	tuple<int, int, int> query(int start, int end){
		if(lazy != -1){
			propagate(lazy);
			lazy = -1;
		}
		if(end < l || r < start) return {0, 0, 0};
		if(start <= l && r <= end) return {two, five, zero};
		else{
			auto l = left->query(start, end);
			auto r = right->query(start, end);
			return {get<0>(l) + get<0>(r), get<1>(l) + get<1>(r), get<2>(l) + get<2>(r)};
		}
	}
 
	void update(int start, int end, int dif){
		if(lazy != -1){
			propagate(lazy);
			lazy = -1;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end) propagate(dif);
		else{
			left->update(start, end, dif);
			right->update(start, end, dif);
			two = left->two + right->two;
			five = left->five + right->five;
			zero = left->zero + right->zero;
		}
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int pot = 2;
	while(pot <= M){
		for(int i = pot; i <= M; i += pot)
			Two[i]++;
		pot *= 2;
	}
	pot = 5;
	while(pot <= M){
		for(int i = pot; i <= M; i += pot)
			Five[i]++;
		pot *= 5;
	}
	int n, q, t, l, r, v;
	cin >> n;
	vector<int> arr(n);
	for(int & ai : arr)
		cin >> ai;
	SegmentTreeDin st(0, n - 1, arr);
	cin >> q;
	while(q--){
		cin >> t;
		if(t == 0){
			cin >> l >> r >> v;
			st.update(l - 1, r - 1, v);
		}else if(t == 1){
			cin >> l >> r;
			int two, five, zero;
			tie(two, five, zero) = st.query(l - 1, r - 1);
			cout << (zero > 0 ? 1 : min(two, five)) << "\n";
		}
	}
	return 0;
}