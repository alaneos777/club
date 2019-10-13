#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct event{
	int x, y1, y2;
	int type;
	event(){}
	event(int x, int y1, int y2, int type): x(x), y1(y1), y2(y2), type(type){}
	bool operator<(const event & e) const{
		return x < e.x;
	}
};

struct SegmentTree{
	SegmentTree *left, *right;
	int l, r;
	int covered, score, length;
 
	SegmentTree(int start, int end, vector<int> & arr): left(NULL), right(NULL), l(start), r(end), covered(0), score(0), length(0){
		if(l == r) length = arr[l];
		else{
			int half = l + ((r - l) >> 1);
			left = new SegmentTree(l, half, arr);
			right = new SegmentTree(half+1, r, arr);
			length = left->length + right->length;
		}
	}
 
	void update(int start, int end, int dif){
		if(end < l || r < start) return;
		if(start <= l && r <= end) covered += dif;
		else{
			left->update(start, end, dif);
			right->update(start, end, dif);
		}
		if(covered == 0){
			if(!left && !right){
				score = 0;
			}else{
				score = left->score + right->score;
			}
		}else{
			score = length;
		}
	}
};

struct rect{
	int x1, y1, x2, y2;
	rect(){}
	void read(){cin >> x1 >> y1 >> x2 >> y2;}
};

lli solve(const vector<rect> & rects){
	int n = rects.size();
	vector<event> events;
	vector<int> ranges;
	for(const rect & r : rects){
		int x1 = r.x1, y1 = r.y1, x2 = r.x2, y2 = r.y2;
		events.emplace_back(x1, y1, y2, 1);
		events.emplace_back(x2, y1, y2, -1);
		ranges.push_back(y1);
		ranges.push_back(y2);
	}
	sort(events.begin(), events.end());
	sort(ranges.begin(), ranges.end());
	ranges.resize(distance(ranges.begin(), unique(ranges.begin(), ranges.end())));
	int sz = ranges.size() - 1;
	vector<int> lengths(sz);
	for(int i = 0; i < sz; ++i){
		lengths[i] = ranges[i + 1] - ranges[i];
	}
	SegmentTree st(0, sz - 1, lengths);
	int prev = events[0].x;
	lli area = 0;
	for(int i = 0; i < events.size(); ++i){
		area += lli(events[i].x - prev) * st.score;
		int l = lower_bound(ranges.begin(), ranges.end(), events[i].y1) - ranges.begin();
		int r = lower_bound(ranges.begin(), ranges.end(), events[i].y2) - ranges.begin() - 1;
		st.update(l, r, events[i].type);
		prev = events[i].x;
	}
	return area;
}

struct segment{
	int start, end;
	int pos;
	int type; //0: horizontal, 1: vertical
	segment(){}
};

bool can(const vector<segment> & segments, int r, const rect & country, lli p){
	int n = segments.size();
	vector<rect> rects;
	for(const segment & seg : segments){
		rect curr;
		if(seg.type == 0){
			curr.x1 = seg.start - r;
			curr.y1 = seg.pos - r;
			curr.x2 = seg.end + r;
			curr.y2 = seg.pos + r;
		}else{
			curr.x1 = seg.pos - r;
			curr.y1 = seg.start - r;
			curr.x2 = seg.pos + r;
			curr.y2 = seg.end + r;
		}
		curr.x1 = max(country.x1, curr.x1);
		curr.x2 = min(country.x2, curr.x2);
		curr.y1 = max(country.y1, curr.y1);
		curr.y2 = min(country.y2, curr.y2);
		rects.push_back(curr);
	}
	return 100*solve(rects) >= p * (country.x2 - country.x1) * (country.y2 - country.y1);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, p;
	rect country;
	cin >> n;
	vector<segment> segments(n);
	for(int i = 0; i < n; ++i){
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if(x1 == x2){
			segments[i].start = y1;
			segments[i].end = y2;
			segments[i].pos = x1;
			segments[i].type = 1;
		}else{
			segments[i].start = x1;
			segments[i].end = x2;
			segments[i].pos = y1;
			segments[i].type = 0;
		}
	}
	cin >> p;
	country.read();
	int l = 0, r = 2e5, m;
	while(true){
		m = (l + r) / 2;
		if(can(segments, m, country, p)){
			if(!can(segments, m - 1, country, p)){
				cout << m << "\n";
				break;
			}else{
				r = m - 1;
			}
		}else{
			l = m + 1;
		}
	}
	return 0;
}