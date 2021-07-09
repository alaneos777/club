#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct SegmentTree{
	int n;
	vector<lli> t;
	vector<int> pos;

	void add_pos(int y){pos.push_back(y);}

	void build(){
		sort(pos.begin(), pos.end());
		pos.erase(unique(pos.begin(), pos.end()), pos.end());
		n = pos.size();
		t.resize(n<<1);
	}

	int lo(int y){return lower_bound(pos.begin(), pos.end(), y) - pos.begin();}
	int hi(int y){return upper_bound(pos.begin(), pos.end(), y) - pos.begin();}

	lli query(int y1, int y2){
		y1 = lo(y1), y2 = hi(y2);
		if(y1 == y2) return 0;
		y2--;
		lli res = 0;
		for(y1 += n, y2 += n; y1 <= y2; y1 >>= 1, y2 >>= 1){
			if(y1 & 1) res += t[y1++];
			if(!(y2 & 1)) res += t[y2--];
		}
		return res;
	}

	void update(int y, lli val){
		y = lo(y);
		for(y += n; y; y >>= 1) t[y] += val;
	}
};

struct SegmentTree2D{
	int m;
	vector<SegmentTree> t;
	vector<int> pos;

	void add_pos(int x){pos.push_back(x);}

	void build(){
		sort(pos.begin(), pos.end());
		pos.erase(unique(pos.begin(), pos.end()), pos.end());
		m = pos.size();
		t.resize(m<<1);
	}

	int lo(int x){return lower_bound(pos.begin(), pos.end(), x) - pos.begin();}
	int hi(int x){return upper_bound(pos.begin(), pos.end(), x) - pos.begin();}

	void add_pos(int x, int y){
		x = lo(x);
		for(x += m; x; x >>= 1) t[x].add_pos(y);
	}

	void build_y(){
		for(int i = 0; i < t.size(); ++i) t[i].build();
	}

	lli query(int x1, int y1, int x2, int y2){
		x1 = lo(x1), x2 = hi(x2);
		if(x1 == x2) return 0;
		x2--;
		lli res = 0;
		for(x1 += m, x2 += m; x1 <= x2; x1 >>= 1, x2 >>= 1){
			if(x1 & 1) res += t[x1++].query(y1, y2);
			if(!(x2 & 1)) res += t[x2--].query(y1, y2);
		}
		return res;
	}

	void update(int x, int y, lli val){
		x = lo(x);
		for(x += m; x; x >>= 1) t[x].update(y, val);
	}
};

struct pt{
	int x, y, w;
};

struct query{
	int t;
	pt a, b;
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	SegmentTree2D st;
	vector<pt> points;
	vector<query> queries;
	for(int i = 0; i < n; ++i){
		int x, y, w;
		cin >> x >> y >> w;
		st.add_pos(x);
		points.push_back({x, y, w});
	}
	for(int i = 0; i < q; ++i){
		int t;
		cin >> t;
		if(t == 0){
			int x, y, w;
			cin >> x >> y >> w;
			st.add_pos(x);
			queries.push_back({0, pt{x, y, w}, pt{0, 0, 0}});
		}else{
			int l, d, r, u;
			cin >> l >> d >> r >> u;
			queries.push_back({1, pt{l, d, 0}, pt{r-1, u-1, 0}});
		}
	}
	st.build();

	for(const pt& p : points){
		st.add_pos(p.x, p.y);
	}
	for(const query& q : queries){
		if(q.t == 0){
			st.add_pos(q.a.x, q.a.y);
		}
	}
	st.build_y();

	for(const pt& p : points){
		st.update(p.x, p.y, p.w);
	}
	for(const query& q : queries){
		if(q.t == 0){
			st.update(q.a.x, q.a.y, q.a.w);
		}else{
			cout << st.query(q.a.x, q.a.y, q.b.x, q.b.y) << "\n";
		}
	}
	return 0;
}