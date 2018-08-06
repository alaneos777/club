#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
 
struct SegmentTree{
	SegmentTree *left, *right;
	int l, r;
	lli value = 0, lazy = 0;
 
	SegmentTree(int start, int end){
		left = right =NULL;
		l = start, r = end;
		value = 0;
		if(l != r){
			int half = l + ((r - l) >> 1);
			left = new SegmentTree(l, half);
			right = new SegmentTree(half+1, r);
		}
	}
 
	void propagate(lli dif){
		value += (r - l + 1) * dif;
		if(l != r){
			left->lazy += dif;
			right->lazy += dif;
		}
	}
 
	lli query(int start, int end){
		if(lazy != 0){
			propagate(lazy);
			lazy = 0;
		}
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return value;
		else return left->query(start, end) + right->query(start, end);
	}
 
	void update_range(lli dif, int start, int end){
		if(lazy != 0){
			propagate(lazy);
			lazy = 0;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end) propagate(dif);
		else{
			left->update_range(dif, start, end);
			right->update_range(dif, start, end);
			value = left->value + right->value;
		}
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
		SegmentTree st(0, n-1);
		while(c--){
			cin >> accion;
			if(accion == 0){
				cin >> p >> q >> v;
				st.update_range(v, p-1, q-1);
			}else{
				cin >> p >> q;
				cout << st.query(p-1, q-1) << "\n";
			}
		}
	}
	return 0;
}