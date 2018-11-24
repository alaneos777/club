#include <bits/stdc++.h>
using namespace std;

struct SegmentTreeDin{
	SegmentTreeDin *left, *right;
	int l, r;
	int gcd;
 
	SegmentTreeDin(int start, int end, vector<int> & arr): left(NULL), right(NULL), l(start), r(end), gcd(0){
		if(l == r) gcd = arr[l];
		else{
			int half = l + ((r - l) >> 1);
			left = new SegmentTreeDin(l, half, arr);
			right = new SegmentTreeDin(half+1, r, arr);
			gcd = __gcd(left->gcd, right->gcd);
		}
	}
 
	void gcd_query(int start, int end, int x, int & cnt){
		if(cnt > 1) return;
		if(end < l || r < start) return;
		if(start <= l && r <= end){
			if(gcd % x != 0){
				if((!left || (left && left->gcd % x != 0)) && (!right || (right && right->gcd % x != 0))){
					cnt += r-l+1;
				}else if(left && left->gcd % x != 0){
					left->gcd_query(start, end, x, cnt);
				}else if(right && right->gcd % x != 0){
					right->gcd_query(start, end, x, cnt);
				}
			}
		}else{
			left->gcd_query(start, end, x, cnt);
			right->gcd_query(start, end, x, cnt);
		}
	}
 
	void update(int pos, int val){
		if(l == r) gcd = val;
		else{
			int half = l + ((r - l) >> 1);
			if(pos <= half) left->update(pos, val);
			else right->update(pos, val);
			gcd = __gcd(left->gcd, right->gcd);
		}
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q, type, l, r, x, pos, y;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a) cin >> ai;
	SegmentTreeDin st(0, n-1, a);
	cin >> q;
	while(q--){
		cin >> type;
		if(type == 1){
			cin >> l >> r >> x;
			int res = 0;
			st.gcd_query(l-1, r-1, x, res);
			cout << (res <= 1 ? "YES" : "NO") << "\n";
		}else{
			cin >> pos >> y;
			st.update(pos-1, y);
		}
	}
	return 0;
}