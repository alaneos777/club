#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct rect{
	int x1, y1, x2, y2;
	rect(): x1(0), y1(0), x2(0), y2(0) {}
	rect(int x1, int y1, int x2, int y2): x1(x1), y1(y1), x2(x2), y2(y2) {}
	bool operator<(const rect & r) const{
		if(x1 != r.x1) return x1 < r.x1;
		if(y1 != r.y1) return y1 < r.y1;
		if(x2 != r.x2) return x2 < r.x2;
		return y2 < r.y2;
	}
};

struct event_rect{
	int x, y1, y2;
	int type;
	event_rect(){}
	event_rect(int x, int y1, int y2, int type): x(x), y1(y1), y2(y2), type(type){}
	bool operator<(const event_rect & e) const{
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

	~SegmentTree(){
		if(left) delete left;
		if(right) delete right;
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

int solve_rect(const set<rect> & rects){
	int n = rects.size();
	if(n == 0) return 0;
	vector<event_rect> events;
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
	SegmentTree* st = new SegmentTree(0, sz - 1, lengths);
	int prev = events[0].x;
	lli area = 0;
	for(int i = 0; i < events.size(); ++i){
		area += lli(events[i].x - prev) * st->score;
		int l = lower_bound(ranges.begin(), ranges.end(), events[i].y1) - ranges.begin();
		int r = lower_bound(ranges.begin(), ranges.end(), events[i].y2) - ranges.begin() - 1;
		st->update(l, r, events[i].type);
		prev = events[i].x;
	}
	delete st;
	return area;
}

struct cube{
	int x1, y1, z1;
	int x2, y2, z2;
	cube(): x1(0), y1(0), z1(0), x2(0), y2(0), z2(0) {}
	cube(int x1, int y1, int z1, int x2, int y2, int z2): x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2) {}
};

struct event_cube{
	int x;
	rect r;
	int type;
	event_cube(){}
	event_cube(int x, const rect & r, int type): x(x), r(r), type(type) {}
	bool operator<(const event_cube & e) const{
		return x < e.x;
	}
};

const int N = 5e4;

int main(){
	vector<int> f;
	for(lli k = 0; k <= 55; ++k){
		f.push_back((100003 - 200003*k + 300007*k*k*k) % 1000000);
		if(f.back() < 0) f.back() += 1000000;
	}
	for(int k = 56; k <= 6*N; ++k){
		f.push_back((f[k-24] + f[k-55]) % 1000000);
	}
	vector<cube> cubes;
	for(int i = 1; i <= N; ++i){
		int x1 = f[6*i-5]%10000, y1 = f[6*i-4]%10000, z1 = f[6*i-3]%10000;
		int x2 = x1 + 1 + f[6*i-2]%399, y2 = y1 + 1 + f[6*i-1]%399, z2 = z1 + 1 + f[6*i]%399;
		cubes.emplace_back(x1, y1, z1, x2, y2, z2);
	}
	vector<event_cube> events;
	for(const cube & c : cubes){
		events.emplace_back(c.x1, rect(c.y1, c.z1, c.y2, c.z2), 1);
		events.emplace_back(c.x2, rect(c.y1, c.z1, c.y2, c.z2), -1);
	}
	sort(events.begin(), events.end());
	lli volume = 0;
	int prev = events[0].x;
	set<rect> rects;
	for(const event_cube & e : events){
		volume += lli(e.x - prev) * solve_rect(rects);
		if(e.type == 1) rects.insert(e.r);
		else rects.erase(e.r);
		prev = e.x;
	}
	cout << volume << "\n";
	return 0;
}