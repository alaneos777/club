#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct node{
	lli freq[12];
	node(){
		memset(freq, 0, sizeof(freq));
	}
	node(int val, lli len){
		memset(freq, 0, sizeof(freq));
		freq[val] = len;
	}
	node operator+(const node& e) const{
		node n;
		for(int i = 0; i < 12; ++i){
			n.freq[i] = freq[i] + e.freq[i];
		}
		return n;
	}
	node rotate(int k) const{
		node n;
		for(int i = 0; i < 12; ++i){
			n.freq[(i+k)%12] = freq[i];
		}
		return n;
	}
	lli value() const{
		lli ans = 0;
		for(int i = 1; i <= 12; ++i){
			ans += i*freq[i%12];
		}
		return ans;
	}
};

struct SegmentTree{
	SegmentTree *left, *right;
	int l, r;
	node n; int lazy;
 
	SegmentTree(int start, int end, const vector<int>& arr): left(NULL), right(NULL), l(start), r(end), n(), lazy(0){
		if(l == r) n = node(11, arr[l]);
		else{
			int half = l + ((r - l) >> 1);
			left = new SegmentTree(l, half, arr);
			right = new SegmentTree(half+1, r, arr);
			n = left->n + right->n;
		}
	}
 
	void propagate(int dif){
		n = n.rotate(dif);
		if(l != r){
			left->lazy = (left->lazy + dif) % 12;
			right->lazy = (right->lazy + dif) % 12;
		}
	}
 
	node query(int start, int end){
		if(lazy != 0){
			propagate(lazy);
			lazy = 0;
		}
		if(end < l || r < start) return node();
		if(start <= l && r <= end) return n;
		else return left->query(start, end) + right->query(start, end);
	}
 
	void update(int start, int end, int dif){
		if(lazy != 0){
			propagate(lazy);
			lazy = 0;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end) propagate(dif);
		else{
			left->update(start, end, dif);
			right->update(start, end, dif);
			n = left->n + right->n;
		}
	}
};

struct event{
	int x, y0, y1, type;
	event(int x, int y0, int y1, int type): x(x), y0(y0), y1(y1), type(type){}
	bool operator<(const event& e) const{
		return x < e.x || (x == e.x && type < e.type);
	}
};

int main(){
	int dim = 50515093;
	int N = 1e5;

	vector<int> S = {290797};
	while(S.size() < 4*N){
		S.push_back((lli)S.back() * S.back() % dim);
	}

	vector<event> events;
	events.emplace_back(0, 0, dim, 1);
	events.emplace_back(dim, 0, dim, -1);
	vector<int> distinct = {0, dim};
	for(int i = 0; i < N; ++i){
		int x0 = S[4*i], x1 = S[4*i+1];
		int y0 = S[4*i+2], y1 = S[4*i+3];
		if(x0 > x1) swap(x0, x1);
		if(y0 > y1) swap(y0, y1);
		events.emplace_back(x0, y0, y1 + 1, 1);
		events.emplace_back(x1 + 1, y0, y1 + 1, -1);
		distinct.push_back(y0);
		distinct.push_back(y1 + 1);
	}
	sort(events.begin(), events.end());
	sort(distinct.begin(), distinct.end());
	distinct.resize(distance(distinct.begin(), unique(distinct.begin(), distinct.end())));

	int sz = distinct.size()-1;
	vector<int> lengths(sz);
	for(int i = 0; i < sz; ++i){
		lengths[i] = distinct[i+1] - distinct[i];
	}

	SegmentTree* st = new SegmentTree(0, sz-1, lengths);

	auto change = [&](int l, int r, int c){
		if(c < 0) c += 12;
		st->update(l, r, c);
	};

	auto get = [&](int l, int r){
		node n = st->query(l, r);
		lli ans = 0;
		for(int i = 1; i <= 12; ++i){
			ans += i*n.freq[i%12];
		}
		return ans;
	};

	lli ans = 0;

	int prev_x = 0;
	for(const auto&[x, y0, y1, type] : events){
		ans += (x - prev_x) * get(0, sz-1);
		int l = lower_bound(distinct.begin(), distinct.end(), y0) - distinct.begin();
		int r = lower_bound(distinct.begin(), distinct.end(), y1) - distinct.begin() - 1;
		change(l, r, type);
		prev_x = x;
	}

	cout << ans << "\n";

	return 0;
}