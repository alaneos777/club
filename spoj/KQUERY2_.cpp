#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using pii = pair<int, int>;

int inf = 1<<30;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
ordered_set<T> merge(ordered_set<T> & a, ordered_set<T> & b){
	vector<T> arra(a.begin(), a.end()), arrb(b.begin(), b.end()), arrc(a.size() + b.size());
	merge(arra.begin(), arra.end(), arrb.begin(), arrb.end(), arrc.begin());
	ordered_set<T> c(arrc.begin(), arrc.end());
	return c;
}

struct SegmentTree{
	int N;
	vector<ordered_set<pii>> ST;

	SegmentTree(int N): N(N){
		ST.resize(N << 1);
	}

	void build(vector<int> & arr){
		for(int i = 0; i < N; ++i)
			ST[N + i].insert({arr[i], i});
		for(int i = N - 1; i > 0; --i)
			ST[i] = merge<pii>(ST[i << 1], ST[i << 1 | 1]);
	}

	void update(const int & oldVal, const int & newVal, int pos){
		int i = pos;
		pos += N;
		ST[pos].erase({oldVal, i});
		ST[pos].insert({newVal, i});
		while(pos >>= 1){
			ST[pos].erase({oldVal, i});
			ST[pos].insert({newVal, i});
		}
	}

	int ge(int l, int r, int k){
		int res = r-l+1;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1){
				res -= ST[l].order_of_key({k, inf});
				l++;
			}
			if(!(r & 1)){
				res -= ST[r].order_of_key({k, inf});
				r--;
			}
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, type, q, i, v, l, r, k;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	SegmentTree st(n);
	st.build(a);
	cin >> q;
	while(q--){
		cin >> type;
		if(type == 0){
			cin >> i >> v;
			--i;
			st.update(a[i], v, i);
			a[i] = v;
		}else if(type == 1){
			cin >> l >> r >> k;
			--l, --r;
			cout << st.ge(l, r, k) << "\n";
		}
	}
	return 0;
}