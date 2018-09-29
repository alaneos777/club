#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long int lli;

struct segment{
	int start, end, axis;
	segment(): start(0), end(0), axis(0) {}
	segment(int start, int end, int axis): start(start), end(end), axis(axis) {}

	bool operator<(const segment & s) const{
		if(axis != s.axis) return axis < s.axis;
		if(start != s.start) return start < s.start;
		return end < s.end;
	}
	bool operator>(const segment & s) const{
		if(axis != s.axis) return axis > s.axis;
		if(start != s.start) return start > s.start;
		return end > s.end;
	}
};

struct event{
	int p;
	char t;
	segment s;
	event(): p(0), t(0){}
	event(int p, char t, segment s): p(p), t(t), s(s) {}

	bool operator<(const event & e) const{
		if(p == e.p) return t < e.t;
		return p < e.p;
	}
	bool operator>(const event & e) const{
		if(p == e.p) return t > e.t;
		return p > e.p;
	}
};

typedef tree<segment, null_type, less<segment>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	int xi, yi, xf, yf;
	vector<segment> segmentsH, segmentsV;
	vector<event> events;
	for(int i = 0; i < n; ++i){
		cin >> xi >> yi >> xf >> yf;
		if(yi == yf){
			if(xi > xf) swap(xi, xf);
			events.emplace_back(xi, 'a', segment(xi, xf, yi)); //start
			events.emplace_back(xf, 'c', segment(xi, xf, yi)); //end
		}else if(xi == xf){
			if(yi > yf) swap(yi, yf);
			events.emplace_back(xi, 'b', segment(yi, yf, xi)); //vertical line
		}
	}
	sort(events.begin(), events.end());
	ordered_set active;
	lli cnt = 0;
	for(event & e : events){
		if(e.t == 'a') active.insert(e.s);
		else if(e.t == 'c') active.erase(e.s);
		else if(e.t == 'b'){
			cnt += active.order_of_key(segment(0, 0, e.s.end + 1)) - active.order_of_key(segment(0, 0, e.s.start));
		}
	}
	cout << cnt << "\n";
	return 0;
}