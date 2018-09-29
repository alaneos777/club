#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

struct rectangle{
	int xi, xf, yi, yf, id;
	rectangle(): xi(0), xf(0), yi(0), yf(0), id(0) {}
	rectangle(int xi, int yi, int xf, int yf, int id): xi(xi), xf(xf), yi(yi), yf(yf), id(id) {}

	bool operator<(const rectangle & s) const{
		if(yi != s.yi) return yi < s.yi;
		/*if(yf != s.yf) return yf < s.yf;
		if(xi != s.xi) return xi < s.xi;
		if(xf != s.xf) return xf < s.xf;*/
		return id < s.id;
	}
	bool operator>(const rectangle & s) const{
		if(yi != s.yi) return yi > s.yi;
		/*if(yf != s.yf) return yf > s.yf;
		if(xi != s.xi) return xi > s.xi;
		if(xf != s.xf) return xf > s.xf;*/
		return id > s.id;
	}
};

struct event{
	int p;
	char t;
	rectangle s;
	event(): p(0), t(0){}
	event(int p, char t, rectangle s): p(p), t(t), s(s) {}

	bool operator<(const event & e) const{
		if(p == e.p) return t < e.t;
		return p < e.p;
	}
	bool operator>(const event & e) const{
		if(p == e.p) return t > e.t;
		return p > e.p;
	}
};

typedef tree<rectangle, null_type, less<rectangle>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	int xi, yi, xf, yf;
	vector<rectangle> rectangles;
	vector<event> events;
	for(int i = 0; i < n; ++i){
		cin >> xi >> yi >> xf >> yf;
		events.emplace_back(xi, 'a', rectangle(xi, yi, xf, yf, i));
		events.emplace_back(xf, 'c', rectangle(xi, yi, xf, yf, i));
	}
	sort(events.begin(), events.end());
	ordered_set active;
	vector<int> parent(n, -1);
	for(event & e : events){
		if(e.t == 'a'){
			int pos = active.order_of_key(e.s) - 1;
			if(pos != -1){
				parent[e.s.id] = active.find_by_order(pos)->id;
			}
			active.insert(e.s);
		}else if(e.t == 'c'){
			active.erase(e.s);
		}
	}
	for(int i = 0; i < n; ++i){
		cout << parent[i] << "\n";
	}
	return 0;
}