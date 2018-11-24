#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct SegmentTreeDin{
	SegmentTreeDin *left, *right;
	int l, r;
	T sum;
 
	SegmentTreeDin(int start, int end, vector<T> & arr): left(NULL), right(NULL), l(start), r(end), sum(0){
		if(l == r) sum = arr[l];
		else{
			int half = l + ((r - l) >> 1);
			left = new SegmentTreeDin(l, half, arr);
			right = new SegmentTreeDin(half+1, r, arr);
			sum = left->sum + right->sum;
		}
	}

	SegmentTreeDin(int start, int end, int val): left(NULL), right(NULL), l(start), r(end), sum(val){}
	SegmentTreeDin(int start, int end, SegmentTreeDin* left, SegmentTreeDin* right): left(left), right(right), l(start), r(end), sum(0){
		sum = left->sum + right->sum;
	}
 
	T sum_query(int start, int end){
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return sum;
		else return left->sum_query(start, end) + right->sum_query(start, end);
	}
 
	SegmentTreeDin* update(int pos, T val){
		if(l == r) return new SegmentTreeDin(l, r, sum + val);
		int half = l + ((r - l) >> 1);
		if(pos <= half) return new SegmentTreeDin(l, r, left->update(pos, val), right);
		return new SegmentTreeDin(l, r, left, right->update(pos, val));
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q, type, pos, v, idx, l, r, k = 0;
	cin >> n;
	vector<SegmentTreeDin<int>*> versions(1e5 + 10);
	vector<int> a(n);
	for(int & ai : a) cin >> ai;
	versions[0] = new SegmentTreeDin<int>(0, n - 1, a);
	cin >> q;
	while(q--){
		cin >> type;
		if(type == 1){
			cin >> idx >> pos >> v;
			versions[++k] = versions[idx]->update(pos - 1, v);
		}else{
			cin >> idx >> l >> r;
			cout << versions[idx]->sum_query(l - 1, r - 1) << "\n";
		}
	}
	return 0;
}