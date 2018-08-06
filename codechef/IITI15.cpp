#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int S, n;
vector<int> bit;

inline void update(int pos, int value){
	while(pos < n){
		bit[pos] += value;
		pos |= pos + 1;
	}
}

inline int query(int r){
	if(r >= n) return 0;
	int res = 0;
	while(r >= 0){
		res += bit[r];
		r = (r & (r + 1)) - 1;
	}
	return res;
}

inline int query(int l, int r){
	return query(r) - query(l - 1);
}

struct MOquery{
	int l, r, index, block;
	bool operator<(const MOquery & q) const{
		if(block == q.block)
			return r < q.r;
		return block < q.block;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int q;
	cin >> n;
	vector<pair<int, int>> arr(n);
	vector<int> comp(n);
	bit = vector<int>(n);
	for(int i = 0; i < n; ++i){
		cin >> arr[i].first;
		arr[i].second = i;
	}
	sort(arr.begin(), arr.end());
	for(int i = 0; i < n; ++i){
		comp[arr[i].second] = i;
	}
	S = sqrt(n);
	cin >> q;
	vector<MOquery> queries(q);
	int current = 0;
	for(int i = 0; i < q; ++i){
		cin >> queries[i].l >> queries[i].r;
		--queries[i].l, --queries[i].r;
		queries[i].index = i;
		queries[i].block = queries[i].l / S;
	}

	sort(queries.begin(), queries.end());
	vector<int> ans(q);
	int prevL = 0, prevR = -1;
	int i, j;
	for(const MOquery & q : queries){
		for(i = prevL, j = min(prevR, q.l - 1); i <= j; ++i){
			//remove from the left
			current -= query(0, comp[i] - 1);
			update(comp[i], -1);
		}
		for(i = prevL - 1; i >= q.l; --i){
			//add to the left
			current += query(0, comp[i] - 1);
			update(comp[i], 1);
		}
		for(i = max(prevR + 1, q.l); i <= q.r; ++i){
			//add to the right
			current += query(comp[i] + 1, n - 1);
			update(comp[i], 1);
		}
		for(i = prevR; i >= q.r + 1; --i){
			//remove from the right
			current -= query(comp[i] + 1, n - 1);
			update(comp[i], -1);
		}
		prevL = q.l, prevR = q.r;
		ans[q.index] = current;
	}
	for(int & x : ans){
		cout << x << "\n";
	}
	return 0;
}