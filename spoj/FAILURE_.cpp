#include <bits/stdc++.h>
using namespace std;
typedef __int128 lli;

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

istream &operator>>(istream &is, __int128 & value){
	char buffer[64];
	is >> buffer;
	char *pos = begin(buffer);
	int sgn = 1;
	value = 0;
	if(*pos == '-'){
		sgn = -1;
		++pos;
	}else if(*pos == '+'){
		++pos;
	}
	while(*pos != '\0'){
		value = (value << 3) + (value << 1) + (*pos - '0');
		++pos;
	}
	value *= sgn;
	return is;
}

lli eps = 0, inf = numeric_limits<lli>::max();
bool geq(lli a, lli b){return a-b >= -eps;}     //a >= b
bool leq(lli a, lli b){return b-a >= -eps;}     //a <= b
bool ge(lli a, lli b){return a-b > eps;}        //a > b
bool le(lli a, lli b){return b-a > eps;}        //a < b
bool eq(lli a, lli b){return abs(a-b) <= eps;}  //a == b
bool neq(lli a, lli b){return abs(a-b) > eps;}  //a != b

struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}
	bool operator==(const point & p) const{
		return eq(x, p.x) && eq(y, p.y);
	}
	bool operator<(const point & p) const{
		if(eq(x, p.x)) return le(y, p.y);
		return le(x, p.x);
	}
	lli dot(const point & p) const{
		return x * p.x + y * p.y;
	}
	lli cross(const point & p) const{
		return x * p.y - y * p.x;
	}
	point operator-(const point&p) const{
		return point(x - p.x, y - p.y);
	}
	lli length() const{
		return hypot(x, y);
	}
};

int sgn(lli x){
	if(ge(x, 0)) return 1;
	if(le(x, 0)) return -1;
	return 0;
}

istream &operator>>(istream &is, point & p){
	is >> p.x >> p.y;
	return is;
}

const point inf_pt(inf, inf);

struct QuadEdge{
	point origin;
	QuadEdge* rot = nullptr;
	QuadEdge* onext = nullptr;
	bool used = false;
	QuadEdge* rev() const{return rot->rot;}
	QuadEdge* lnext() const{return rot->rev()->onext->rot;}
	QuadEdge* oprev() const{return rot->onext->rot;}
	point dest() const{return rev()->origin;}
};

QuadEdge* make_edge(const point & from, const point & to){
	QuadEdge* e1 = new QuadEdge;
	QuadEdge* e2 = new QuadEdge;
	QuadEdge* e3 = new QuadEdge;
	QuadEdge* e4 = new QuadEdge;
	e1->origin = from;
	e2->origin = to;
	e3->origin = e4->origin = inf_pt;
	e1->rot = e3;
	e2->rot = e4;
	e3->rot = e2;
	e4->rot = e1;
	e1->onext = e1;
	e2->onext = e2;
	e3->onext = e4;
	e4->onext = e3;
	return e1;
}

void splice(QuadEdge* a, QuadEdge* b){
	swap(a->onext->rot->onext, b->onext->rot->onext);
	swap(a->onext, b->onext);
}

void delete_edge(QuadEdge* e){
	splice(e, e->oprev());
	splice(e->rev(), e->rev()->oprev());
	delete e->rot;
	delete e->rev()->rot;
	delete e;
	delete e->rev();
}

QuadEdge* connect(QuadEdge* a, QuadEdge* b){
	QuadEdge* e = make_edge(a->dest(), b->origin);
	splice(e, a->lnext());
	splice(e->rev(), b);
	return e;
}

bool left_of(const point & p, QuadEdge* e){
	return ge((e->origin - p).cross(e->dest() - p), 0);
}

bool right_of(const point & p, QuadEdge* e){
	return le((e->origin - p).cross(e->dest() - p), 0);
}

template <class T>
T det3(T a1, T a2, T a3, T b1, T b2, T b3, T c1, T c2, T c3) {
	return a1 * (b2 * c3 - c2 * b3) - a2 * (b1 * c3 - c1 * b3) +
		   a3 * (b1 * c2 - c1 * b2);
}

bool in_circle(const point & a, const point & b, const point & c, const point & d) {
	lli det = -det3<lli>(b.x, b.y, b.dot(b), c.x, c.y, c.dot(c), d.x, d.y, d.dot(d));
	det += det3<lli>(a.x, a.y, a.dot(a), c.x, c.y, c.dot(c), d.x, d.y, d.dot(d));
	det -= det3<lli>(a.x, a.y, a.dot(a), b.x, b.y, b.dot(b), d.x, d.y, d.dot(d));
	det += det3<lli>(a.x, a.y, a.dot(a), b.x, b.y, b.dot(b), c.x, c.y, c.dot(c));
	return ge(det, 0);
}

pair<QuadEdge*, QuadEdge*> builli_tr(int l, int r, vector<point> & P){
	if(r - l + 1 == 2){
		QuadEdge* res = make_edge(P[l], P[r]);
		return make_pair(res, res->rev());
	}
	if(r - l + 1 == 3){
		QuadEdge *a = make_edge(P[l], P[l + 1]), *b = make_edge(P[l + 1], P[r]);
		splice(a->rev(), b);
		int sg = sgn((P[l + 1] - P[l]).cross(P[r] - P[l]));
		if(sg == 0)
			return make_pair(a, b->rev());
		QuadEdge* c = connect(b, a);
		if(sg == 1)
			return make_pair(a, b->rev());
		else
			return make_pair(c->rev(), c);
	}
	int mid = (l + r) / 2;
	QuadEdge *llio, *llii, *rdo, *rdi;
	tie(llio, llii) = builli_tr(l, mid, P);
	tie(rdi, rdo) = builli_tr(mid + 1, r, P);
	while(true){
		if(left_of(rdi->origin, llii)){
			llii = llii->lnext();
			continue;
		}
		if(right_of(llii->origin, rdi)){
			rdi = rdi->rev()->onext;
			continue;
		}
		break;
	}
	QuadEdge* basel = connect(rdi->rev(), llii);
	auto valid = [&basel](QuadEdge* e){return right_of(e->dest(), basel);};
	if(llii->origin == llio->origin)
		llio = basel->rev();
	if(rdi->origin == rdo->origin)
		rdo = basel;
	while(true){
		QuadEdge* lcand = basel->rev()->onext;
		if(valid(lcand)){
			while(in_circle(basel->dest(), basel->origin, lcand->dest(), lcand->onext->dest())){
				QuadEdge* t = lcand->onext;
				delete_edge(lcand);
				lcand = t;
			}
		}
		QuadEdge* rcand = basel->oprev();
		if(valid(rcand)){
			while(in_circle(basel->dest(), basel->origin, rcand->dest(), rcand->oprev()->dest())){
				QuadEdge* t = rcand->oprev();
				delete_edge(rcand);
				rcand = t;
			}
		}
		if(!valid(lcand) && !valid(rcand))
			break;
		if(!valid(lcand) || (valid(rcand) && in_circle(lcand->dest(), lcand->origin, rcand->origin, rcand->dest())))
			basel = connect(rcand, basel->rev());
		else
			basel = connect(basel->rev(), lcand->rev());
	}
	return make_pair(llio, rdo);
}

vector<tuple<point, point, point>> delaunay(vector<point> P){
	sort(P.begin(), P.end());
	auto res = builli_tr(0, (int)P.size() - 1, P);
	QuadEdge* e = res.first;
	vector<QuadEdge*> edges = {e};
	while(le((e->dest() - e->onext->dest()).cross(e->origin - e->onext->dest()), 0))
		e = e->onext;
	auto add = [&P, &e, &edges](){
		QuadEdge* curr = e;
		do{
			curr->used = true;
			P.push_back(curr->origin);
			edges.push_back(curr->rev());
			curr = curr->lnext();
		}while(curr != e);
	};
	add();
	P.clear();
	int kek = 0;
	while(kek < (int)edges.size())
		if(!(e = edges[kek++])->used)
			add();
	vector<tuple<point, point, point>> ans;
	for(int i = 0; i < (int)P.size(); i += 3){
		ans.push_back(make_tuple(P[i], P[i + 1], P[i + 2]));
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<point> points(n);
		for(int i = 0; i < n; ++i){
			cin >> points[i];
		}
		map<point, lli> ans;
		bool collineal = true;
		for(int i = 2; i < n; ++i){
			collineal &= ((points[1] - points[0]).cross(points[i] - points[0]) == 0);
		}
		if(collineal){
			auto sorted = points;
			sort(sorted.begin(), sorted.end());
			for(int i = 0; i < n; ++i){
				ans[sorted[i]] = min((i == 0 ? inf : (sorted[i-1]-sorted[i]).dot(sorted[i-1]-sorted[i])), (i == n-1 ? inf : (sorted[i+1]-sorted[i]).dot(sorted[i+1]-sorted[i])));
			}
		}else{
			auto triangulation = delaunay(points);
			for(auto & triangle : triangulation){
				const point & a = get<0>(triangle);
				const point & b = get<1>(triangle);
				const point & c = get<2>(triangle);
				if(ans.find(a) == ans.end()) ans[a] = inf;
				if(ans.find(b) == ans.end()) ans[b] = inf;
				if(ans.find(c) == ans.end()) ans[c] = inf;
				ans[a] = min({ans[a], (b - a).dot(b - a), (c - a).dot(c - a)});
				ans[b] = min({ans[b], (a - b).dot(a - b), (c - b).dot(c - b)});
				ans[c] = min({ans[c], (a - c).dot(a - c), (b - c).dot(b - c)});
			}
		}
		for(auto & p : points){
			cout << ans[p] << "\n";
		}
	}
	return 0;
}