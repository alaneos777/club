#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int S = 0;

struct query{
	int l, r, time, index;
	query() {}
	query(int l, int r, int time, int index): l(l), r(r), time(time), index(index) {}
	bool operator<(const query & q) const{
		int leftLhs = l/S, leftRhs = q.l/S;
		if(leftLhs != leftRhs){
			return leftLhs < leftRhs;
		}else{
			int rightLhs = r/S, rightRhs = q.r/S;
			if(rightLhs != rightRhs){
				return rightLhs < rightRhs;
			}else{
				return time < q.time;
			}
		}
	}
};

struct update{
	int prev, next, pos;
	update(){}
	update(int prev, int next, int pos): prev(prev), next(next), pos(pos) {}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	S = (int)powl(2ll*n*n, 1.0l/3.0l) + 1;
	vector<int> a(n);
	for(int& ai : a) cin >> ai;
	vector<int> prev_a = a;
	vector<query> queries;
	vector<update> updates;
	for(int i = 0; i < q; ++i){
		int t;
		cin >> t;
		if(t == 0){
			int pos, v;
			cin >> pos >> v;
			--pos;
			updates.emplace_back(prev_a[pos], v, pos);
			prev_a[pos] = v;
		}else{
			int l, r;
			cin >> l >> r;
			queries.emplace_back(l-1, r-1, updates.size(), queries.size());
		}
	}

	sort(queries.begin(), queries.end());
	vector<lli> answers(queries.size());
	unordered_map<int, int> freq;
	freq.reserve(1024); freq.max_load_factor(0.25);
	int prevL = 0, prevR = -1, updatesCnt = 0;
	lli sum = 0;

	auto remove = [&](int v){
		int& f = freq[v];
		f--;
		if(f == 0 && v%3 == 0) sum -= v;
	};

	auto add = [&](int v){
		int& f = freq[v];
		f++;
		if(f == 1 && v%3 == 0) sum += v;
	};

	auto change = [&](int pos, int next){
		if(prevL <= pos && pos <= prevR){
			remove(a[pos]);
			a[pos] = next;
			add(a[pos]);
		}
		a[pos] = next;
	};

	for(const query& q : queries){
		while(updatesCnt < q.time){
			change(updates[updatesCnt].pos, updates[updatesCnt].next);
			updatesCnt++;
		}

		while(updatesCnt > q.time){
			updatesCnt--;
			change(updates[updatesCnt].pos, updates[updatesCnt].prev);
		}

		for(int i = prevL, j = min(prevR, q.l - 1); i <= j; ++i) remove(a[i]);
		for(int i = prevL - 1; i >= q.l; --i) add(a[i]);
		for(int i = max(prevR + 1, q.l); i <= q.r; ++i) add(a[i]);
		for(int i = prevR; i >= q.r + 1; --i) remove(a[i]);

		answers[q.index] = sum;
		prevL = q.l, prevR = q.r;
	}

	for(lli ans : answers){
		cout << ans << "\n";
	}
	return 0;
}