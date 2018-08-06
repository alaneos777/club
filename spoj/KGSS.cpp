#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

struct SegmentTree{
	int N;
	vector<pii> ST;

	SegmentTree(int N){
		this->N = N;
		ST.assign(N << 1, make_pair(-1, -1));
	}

	pii combine(const pii & a, const pii & b){
		vector<int> tmp = {a.first, a.second, b.first, b.second};
		sort(tmp.begin(), tmp.end());
		return make_pair(tmp[3], tmp[2]);
	}

	void build(){
		for(int i = N - 1; i > 0; --i)
			ST[i] = combine(ST[i << 1], ST[i << 1 | 1]);
	}

	void update(int pos, int value){
		for(ST[pos += N].first = value; pos > 1; pos >>= 1)
			ST[pos >> 1] = combine(ST[pos], ST[pos ^ 1]);
	}

	int query(int l, int r){
		++r;
		pii res = make_pair(-1, -1);
		for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
			if(l & 1) res = combine(res, ST[l++]);
			if(r & 1) res = combine(res, ST[--r]);
		}
		return res.first + res.second;
	}
};

int main(){
	int n, q, x, y;
	char op;
	scanf("%d", &n);
	SegmentTree * st = new SegmentTree(n);
	for(int i = 0; i < n; ++i){
		scanf("%d", &st->ST[n + i].first);
		st->ST[n + i].second = -1;
	}
	st->build();
	scanf("%d", &q);
	while(q--){
		scanf(" %c %d %d", &op, &x, &y);
		if(op == 'U'){
			st->update(x - 1, y);
		}else{
			printf("%d\n", st->query(x - 1, y - 1));
		}
	}
	return 0;
}