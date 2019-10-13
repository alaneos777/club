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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<event> events;
	vector<int> ranges;
	for(int i = 0; i < n; ++i){
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		events.emplace_back(x1, y1, y2, 1);
		events.emplace_back(x2, y1, y2, 0);
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
		if(events[i].type == 1){
			st.update(l, r, 1);
		}else if(events[i].type == 0){
			st.update(l, r, -1);
		}
		prev = events[i].x;
	}
	cout << area << "\n";
	return 0;
}