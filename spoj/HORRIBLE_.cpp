#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
 
template<typename T>
struct SegmentTree{
	int size;
	vector<T> sum, lazy;
 
	void rec(int pos, int l, int r){
		if(l != r){
			int half = l + ((r - l) >> 1);
			rec(2*pos+1, l, half);
			rec(2*pos+2, half+1, r);
		}
	}

	SegmentTree(int n): size(n){
		int h = ceil(log2(n));
		sum.resize((1 << (h + 1)) - 1);
		lazy.resize((1 << (h + 1)) - 1);
		rec(0, 0, n - 1);
	}
 
	void propagate(int pos, int l, int r, T dif){
		sum[pos] += (r - l + 1) * dif;
		if(l != r){
			lazy[2*pos+1] += dif;
			lazy[2*pos+2] += dif;
		}
	}
 
	T sum_query_rec(int start, int end, int pos, int l, int r){
		if(lazy[pos] != 0){
			propagate(pos, l, r, lazy[pos]);
			lazy[pos] = 0;
		}
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
 
	void add_range_rec(int start, int end, int pos, int l, int r, T dif){
		if(lazy[pos] != 0){
			propagate(pos, l, r, lazy[pos]);
			lazy[pos] = 0;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end) propagate(pos, l, r, dif);
		else{
			int half = l + ((r - l) >> 1);
			add_range_rec(start, end, 2*pos+1, l, half, dif);
			add_range_rec(start, end, 2*pos+2, half+1, r, dif);
			sum[pos] = sum[2*pos+1] + sum[2*pos+2];
		}
	}

	void add_range(int start, int end, T dif){
		add_range_rec(start, end, 0, 0, size - 1, dif);
	}
};
 
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n, c, accion, p, q;
		lli v;
		cin >> n >> c;
		SegmentTree<lli> st(n);
		while(c--){
			cin >> accion;
			if(accion == 0){
				cin >> p >> q >> v;
				st.add_range(p-1, q-1, v);
			}else{
				cin >> p >> q;
				cout << st.sum_query(p-1, q-1) << "\n";
			}
		}
	}
	return 0;
}