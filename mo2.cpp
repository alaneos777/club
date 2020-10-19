#include <bits/stdc++.h>
using namespace std;

struct FenwickTree{
	int N;
	vector<int> bit;

	FenwickTree(int N): N(N){
		bit.resize(N);
	}

	void update(int pos, int value){
		while(pos < N){
			bit[pos] += value;
			pos |= pos + 1;
		}
	}

	int query(int r){
		int res = 0;
		while(r >= 0){
			res += bit[r];
			r = (r & (r + 1)) - 1;
		}
		return res;
	}

	int query(int l, int r){
		return query(r) - query(l - 1);
	}
};

struct query{
	int l, r, x, y, index, S;
	bool operator<(const query & q) const{
		int c_o = l / S, c_q = q.l / S;
		if(c_o == c_q)
			return r < q.r;
		return c_o < c_q;
	}
};

vector<int> MO(const vector<int> & A, vector<query> & queries){
	FenwickTree ft(int(1e5) + 1);
	vector<int> freq(int(1e5) + 1);
	vector<int> ans(queries.size());
	sort(queries.begin(), queries.end());
	int prevL = 0, prevR = -1;
	int i, j;
	for(const query & q : queries){
		for(i = prevL, j = min(prevR, q.l - 1); i <= j; ++i){
			freq[A[i]]--;
			if(freq[A[i]] == 0){
				ft.update(A[i], -1);
			}
		}
		for(i = prevL - 1; i >= q.l; --i){
			freq[A[i]]++;
			if(freq[A[i]] == 1){
				ft.update(A[i], 1);
			}
		}
		for(i = max(prevR + 1, q.l); i <= q.r; ++i){
			freq[A[i]]++;
			if(freq[A[i]] == 1){
				ft.update(A[i], 1);
			}
		}
		for(i = prevR; i >= q.r + 1; --i){
			freq[A[i]]--;
			if(freq[A[i]] == 0){
				ft.update(A[i], -1);
			}
		}
		prevL = q.l, prevR = q.r;
		ans[q.index] = ft.query(q.x, q.y);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> A(n);
	for(int & ai : A){
		cin >> ai;
	}
	int S = n / sqrt(q);
	vector<query> queries(q);
	for(int i = 0; i < q; ++i){
		cin >> queries[i].l >> queries[i].r >> queries[i].x >> queries[i].y;
		--queries[i].l;
		--queries[i].r;
		queries[i].S = S;
		queries[i].index = i;
	}
	auto ans = MO(A, queries);
	for(int a : ans){
		cout << a << "\n";
	}
	return 0;
}