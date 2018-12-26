#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct StPer{
	StPer *left, *right;
	int l, r;
	T sum;
 
	StPer(int start, int end): left(NULL), right(NULL), l(start), r(end), sum(0){
		if(l != r){
			int half = l + ((r - l) >> 1);
			left = new StPer(l, half);
			right = new StPer(half+1, r);
		}
	}

	StPer(int start, int end, T val): left(NULL), right(NULL), l(start), r(end), sum(val){}
	StPer(int start, int end, StPer* left, StPer* right): left(left), right(right), l(start), r(end){
		sum = left->sum + right->sum;
	}
 
	T sum_query(int start, int end){
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return sum;
		else return left->sum_query(start, end) + right->sum_query(start, end);
	}
 
	StPer* update(int pos, T val){
		if(l == r) return new StPer(l, r, sum + val);
		int half = l + ((r - l) >> 1);
		if(pos <= half) return new StPer(l, r, left->update(pos, val), right);
		return new StPer(l, r, left, right->update(pos, val));
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, q, ai, l, r, a, b, last = 0;
	cin >> n >> m >> q;
	vector<StPer<int>*> versions(n + 1);
	versions[0] = new StPer<int>(0, m);
	for(int i = 1; i <= n; ++i){
		cin >> ai;
		versions[i] = versions[i - 1]->update(ai, 1);
	}
	while(q--){
		cin >> l >> r >> a >> b;
		l = (l + last) % n + 1;
		r = (r + last) % n + 1;
		a = (a + last) % m + 1;
		b = (b + last) % m + 1;
		if(l > r) swap(l, r);
		if(a > b) swap(a, b);
		cout << (last = versions[r]->sum_query(a, b) - versions[l - 1]->sum_query(a, b)) << "\n";
	}
	return 0;
}