#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template<typename T>
struct StPer{
	StPer *left, *right;
	int l, r;
	T mini;
 
	StPer(int start, int end): left(NULL), right(NULL), l(start), r(end), mini(){
		if(l != r){
			int half = l + ((r - l) >> 1);
			left = new StPer(l, half);
			right = new StPer(half+1, r);
		}
	}

	StPer(int start, int end, T val): left(NULL), right(NULL), l(start), r(end), mini(val){}
	StPer(int start, int end, StPer* left, StPer* right): left(left), right(right), l(start), r(end){
		mini = min(left->mini, right->mini);
	}
 
	T min_query(int start, int end){
		if(end < l || r < start) return {1<<30, 1<<30};
		if(start <= l && r <= end) return mini;
		else return min(left->min_query(start, end), right->min_query(start, end));
	}
 
	StPer* update(int pos, T val){
		if(l == r) return new StPer(l, r, val);
		int half = l + ((r - l) >> 1);
		if(pos <= half) return new StPer(l, r, left->update(pos, val), right);
		return new StPer(l, r, left, right->update(pos, val));
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q, l, r;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a) cin >> ai;
	vector<int> prev(n, -1);
	unordered_map<int, int> tmp;
	for(int i = 0; i < n; ++i){
		if(tmp.count(a[i])) prev[i] = tmp[a[i]];
		tmp[a[i]] = i;
	}
	vector<StPer<pii>*> versions(n);
	for(int i = 0; i < n; ++i){
		if(i == 0){
			versions[0] = new StPer<pii>(0, n - 1);
			versions[0] = versions[0]->update(i, {prev[i], a[i]});
		}else{
			StPer<pii>* curr = versions[i - 1];
			if(prev[i] != -1) curr = curr->update(prev[i], {1<<30, 1<<30});
			versions[i] = curr->update(i, {prev[i], a[i]});
		}
	}
	cin >> q;
	while(q--){
		cin >> l >> r;
		--l, --r;
		pii ans = versions[r]->min_query(l, r);
		if(ans.first < l) cout << ans.second << "\n";
		else cout << "0\n";
	}
	return 0;
}