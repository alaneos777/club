#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct SegmentTree{
	int N;
	vector<int> ST;
	vector<pair<int, int>> range;
	vector<ordered_set<int>> positions;

	//build from an array in O(n)
	SegmentTree(int N): N(N){
		ST.resize(N << 1, -1);
		range.resize(N << 1);
        positions.resize(2e4 + 1);
		for(int i = 0; i < N; ++i)
			range[N + i] = {i, i};
		for(int i = N - 1; i > 0; --i)
			range[i] = {range[i << 1].first, range[i << 1 | 1].second};
	}

	int getCnt(int x, int l, int r){
		if(positions[x].empty()) return 0;
		int L = positions[x].order_of_key(l);
		if(L == positions[x].size()) return 0;
		int R = positions[x].order_of_key(r+1);
		return R - L;
	}

	int combine(int a, int b, int l, int r){
		if(ST[a] != -1 && 2*getCnt(ST[a], l, r) > r - l + 1){
			return ST[a];
		}else if(ST[b] != -1 && 2*getCnt(ST[b], l, r) > r - l + 1){
			return ST[b];
		}else{
			return -1;
		}
	}

	void update(int i, int value){
		ST[i + N] = value;
		positions[value].insert(i);
		i += N;
		while(i >>= 1){
			ST[i] = combine(i << 1, i << 1 | 1, range[i].first, range[i].second);
		}
	}

	pair<int, int> get(int a, int l, int r){
		if(ST[a] == -1) return {-1, 0};
		int cnt = getCnt(ST[a], l, r);
		if(2*cnt > r - l + 1) return {ST[a], cnt};
		return {-1, 0};
	}

	//range query, [l, r]
	pair<int, int> query(int l, int r){
		pair<int, int> res = {-1, 0};
		int L = l, R = r;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1){
				auto tmp = get(l++, L, R);
				if(tmp.first != -1) res = tmp;
			}
			if(!(r & 1)){
				auto tmp = get(r--, L, R);
				if(tmp.first != -1) res = tmp;
			}
		}
		return res;
	}
};

class MajorityChecker {
public:
    SegmentTree * st;
    MajorityChecker(const vector<int>& arr) {
        int n = arr.size();
        st = new SegmentTree(n);
        for(int i = 0; i < n; ++i){
            st->update(i, arr[i]);
        }
    }
    
    int query(int left, int right, int threshold) {
        auto tmp = st->query(left, right);
        return 2*tmp.second > threshold ? tmp.first : -1;
    }
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */

int main(){
	MajorityChecker* obj = new MajorityChecker({1,1,2,2,1,1,2,2});
	cout << obj->query(0, 5, 4) << endl;
	return 0;
}