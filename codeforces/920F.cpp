#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 1e6;
vector<int> divs(M + 1);

template<typename T>
struct SegmentTree{
	int size;
	vector<T> sum, maxi;
 
	void rec(int pos, int l, int r, vector<T> & arr){
		if(l != r){
			int half = l + ((r - l) >> 1);
			rec(2*pos+1, l, half, arr);
			rec(2*pos+2, half+1, r, arr);
			sum[pos] = sum[2*pos+1] + sum[2*pos+2];
			maxi[pos] = max(maxi[2*pos+1], maxi[2*pos+2]);
		}else{
			sum[pos] = maxi[pos] = arr[l];
		}
	}
 
	SegmentTree(int n, vector<T> & arr): size(n){
		int h = ceil(log2(n));
		sum.resize((1 << (h + 1)) - 1);
		maxi.resize((1 << (h + 1)) - 1);
		rec(0, 0, n - 1, arr);
	}
 
	T sum_query_rec(int start, int end, int pos, int l, int r){
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return sum[pos];
		else{
			int half = l + ((r - l) >> 1);
			return sum_query_rec(start, end, 2*pos+1, l, half) + sum_query_rec(start, end, 2*pos+2, half+1, r);
		}
	}
 
	T sum_query(int start, int end){
		return sum_query_rec(start, end, 0, 0, size - 1);
	}
 
	void update_rec(int start, int end, int pos, int l, int r){
		if(end < l || r < start) return 0;
		if(l == r){
			maxi[pos] = sum[pos] = divs[sum[pos]];
		}else{
			int half = l + ((r - l) >> 1);
			if(maxi[2*pos+1] != 1 && maxi[2*pos+1] != 2) update_rec(start, end, 2*pos+1, l, half);
			if(maxi[2*pos+2] != 1 && maxi[2*pos+2] != 2) update_rec(start, end, 2*pos+2, half+1, r);
			sum[pos] = sum[2*pos+1] + sum[2*pos+2];
			maxi[pos] = max(maxi[2*pos+1], maxi[2*pos+2]);
		}
	}
 
	void update(int start, int end){
		update_rec(start, end, 0, 0, size - 1);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int i = 1; i <= M; ++i)
		for(int j = i; j <= M; j += i)
			divs[j]++;
	int n, q, t, l, r;
	cin >> n >> q;
	vector<lli> a(n);
	for(lli & ai : a)
		cin >> ai;
	SegmentTree<lli> st(n, a);
	while(q--){
		cin >> t >> l >> r;
		--l, --r;
		if(t == 1){
			st.update(l, r);
		}else{
			cout << st.sum_query(l, r) << "\n";
		}
	}
	return 0;
}