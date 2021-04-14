#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
using lli = long long int;

int S = 0;

struct query{
	int l, r, time, index;
	query() {}
	query(int l, int r, int time, int index): l(l), r(r), time(time), index(index) {}
	bool operator<(const query & q) const{
		int timeLhs = time/S, timeRhs = q.time/S;
		if(timeLhs != timeRhs){
			return timeLhs < timeRhs;
		}else{
			int leftLhs = l/S, leftRhs = q.l/S;
			if(leftLhs != leftRhs){
				return leftLhs < leftRhs;
			}else{
				return r < q.r;
			}
		}
	}
};

struct update{
	int prev, next, pos;
	update(){}
	update(int prev, int next, int pos): prev(prev), next(next), pos(pos) {}
};

const int inf = 2e9;

struct MEX{
	int M;
	vector<int> freq;
	MEX(int M): M(M), freq(M+2){}
	void insert(int v){
		freq[v]++;
	}
	void remove(int v){
		freq[v]--;
	}
	int get(){
		for(int i = 0; i <= M+1; ++i){
			if(freq[i] == 0) return i;
		}
		return M+2;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	S = powl(n, 2.0l/3.0l);
	vector<int> a(n);
	gp_hash_table<int, int> mp; int sz = 0;
	vector<int> cnts(int(2e5) + 1);
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		if(mp.find(ai) == mp.end()){
			mp[ai] = sz++;
		}
		a[i] = mp[ai];
		cnts[a[i]]++;
	}
	vector<int> prev_a = a;
	vector<query> queries;
	vector<update> updates;
	for(int i = 0; i < q; ++i){
		int t;
		cin >> t;
		if(t == 1){
			int l, r;
			cin >> l >> r;
			queries.emplace_back(l-1, r-1, updates.size(), queries.size());
		}else{
			int p, x;
			cin >> p >> x;
			--p;
			if(mp.find(x) == mp.end()){
				mp[x] = sz++;
			}
			x = mp[x];
			cnts[x]++;
			updates.emplace_back(prev_a[p], x, p);
			prev_a[p] = x;
		}
	}

	int M = *max_element(cnts.begin(), cnts.end());

	sort(queries.begin(), queries.end());
	vector<int> answers(queries.size());
	vector<int> freq(sz);
	MEX mex(M);
	mex.insert(0);
	mex.freq[0] = 1e9;
	int prevL = 0, prevR = -1, updatesCnt = 0;

	auto remove = [&](int v){
		int& f = freq[v];
		mex.remove(f);
		f--;
		mex.insert(f);
	};

	auto add = [&](int v){
		int& f = freq[v];
		mex.remove(f);
		f++;
		mex.insert(f);
	};

	auto change = [&](int pos, int next){
		if(prevL <= pos && pos <= prevR){
			remove(a[pos]);
			a[pos] = next;
			add(a[pos]);
		}else{
			a[pos] = next;
		}
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

		answers[q.index] = mex.get();
		prevL = q.l, prevR = q.r;
	}

	for(int ans : answers){
		cout << ans << "\n";
	}
	return 0;
}