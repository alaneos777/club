#include <bits/stdc++.h>
using namespace std;
using ld = long double;

ld eps = 1e-9, inf = numeric_limits<ld>::max();

bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

struct point{
    ld x, y;
    int idx = -1;
    point() {}
    point(ld x, ld y): x(x), y(y) {}

    point operator+(const point & p) const{
        return point(x + p.x, y + p.y);
    }

    point operator-(const point & p) const{
        return point(x - p.x, y - p.y);
    }

    point operator*(ld k) const{
        return point(x * k, y * k);
    }

    point operator/(ld k) const{
        return point(x / k, y / k);
    }

    ld dot(const point & p) const{
        return x * p.x + y * p.y;
    }

    ld cross(const point & p) const{
        return x * p.y - y * p.x;
    }

    ld norm() const{
        return x * x + y * y;
    }

    ld length() const{
        return sqrtl(x*x + y*y);
    }

    point perpendicular() const{
        return point(-y, x);
    }

    bool operator<(const point & p) const{
        if(eq(x, p.x)) return le(y, p.y);
        return le(x, p.x);
    }

    bool operator>(const point & p) const{
        if(eq(x, p.x)) return ge(y, p.y);
        return ge(x, p.x);
    }

    bool operator==(const point & p) const{
        return eq(x, p.x) && eq(y, p.y);
    }
};

istream&operator>>(istream & s, point & p){
    return s >> p.x >> p.y;
}

ostream&operator<<(ostream & s, const point & p){
    return s << "(" << p.x << ", " << p.y << ")";
}

int sgn(ld x){
    if(ge(x, 0)) return 1;
    if(le(x, 0)) return -1;
    return 0;
}

//Delaunay triangulation in O(n log n)
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

ld det3(ld a1, ld a2, ld a3, ld b1, ld b2, ld b3, ld c1, ld c2, ld c3) {
    return a1 * (b2 * c3 - c2 * b3) - a2 * (b1 * c3 - c1 * b3) + a3 * (b1 * c2 - c1 * b2);
}

bool in_circle(const point & a, const point & b, const point & c, const point & d) {
    ld det = -det3(b.x, b.y, b.norm(), c.x, c.y, c.norm(), d.x, d.y, d.norm());
    det += det3(a.x, a.y, a.norm(), c.x, c.y, c.norm(), d.x, d.y, d.norm());
    det -= det3(a.x, a.y, a.norm(), b.x, b.y, b.norm(), d.x, d.y, d.norm());
    det += det3(a.x, a.y, a.norm(), b.x, b.y, b.norm(), c.x, c.y, c.norm());
    return ge(det, 0);
}

pair<QuadEdge*, QuadEdge*> build_tr(int l, int r, vector<point> & P){
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
    QuadEdge *ldo, *ldi, *rdo, *rdi;
    tie(ldo, ldi) = build_tr(l, mid, P);
    tie(rdi, rdo) = build_tr(mid + 1, r, P);
    while(true){
        if(left_of(rdi->origin, ldi)){
            ldi = ldi->lnext();
            continue;
        }
        if(right_of(ldi->origin, rdi)){
            rdi = rdi->rev()->onext;
            continue;
        }
        break;
    }
    QuadEdge* basel = connect(rdi->rev(), ldi);
    auto valid = [&basel](QuadEdge* e){return right_of(e->dest(), basel);};
    if(ldi->origin == ldo->origin)
        ldo = basel->rev();
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
    return make_pair(ldo, rdo);
}

vector<tuple<point, point, point>> delaunay(vector<point> P){
    sort(P.begin(), P.end());
    auto res = build_tr(0, (int)P.size() - 1, P);
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

point intersectLines(const point & a1, const point & v1, const point & a2, const point & v2){
    ld det = v1.cross(v2);
    return a1 + v1 * ((a2 - a1).cross(v2) / det);
}

pair<point, ld> getCircle(const point & m, const point & n, const point & p){
    point c = intersectLines((n + m) / 2, (n - m).perpendicular(), (p + n) / 2, (p - n).perpendicular());
    ld r = (c - m).length();
    return {c, r};
}

bool pointInLine(const point & a, const point & v, const point & p){
    return eq((p - a).cross(v), 0);
}

bool pointInSegment(point a, point b, const point & p){
    if(a > b) swap(a, b);
    return pointInLine(a, b - a, p) && !(p < a || p > b);
}

int intersectSegmentsInfo(const point & a, const point & b, const point & c, const point & d){
    point v1 = b - a, v2 = d - c;
    int t = sgn(v1.cross(c - a)), u = sgn(v1.cross(d - a));
    if(t == u){
        if(t == 0){
            if(pointInSegment(a, b, c) || pointInSegment(a, b, d) || pointInSegment(c, d, a) || pointInSegment(c, d, b)){
                return -1; //infinity points
            }else{
                return 0; //no point
            }
        }else{
            return 0; //no point
        }
    }else{
        return sgn(v2.cross(a - c)) != sgn(v2.cross(b - c)); //1: single point, 0: no point
    }
}

int pointInPolygon(vector<point> & P, const point & p){
    point bottomLeft = (*min_element(P.begin(), P.end())) - point(M_E, M_PI);
    int n = P.size();
    int rays = 0;
    for(int i = 0; i < n; i++){
        rays += (intersectSegmentsInfo(p, bottomLeft, P[i], P[(i + 1) % n]) == 1 ? 1 : 0);
    }
    return rays & 1; //0: point outside, 1: point inside
}

struct HASH{
  size_t operator()(const pair<int,int>&x)const{
    return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
  }
};

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<point> polygon(n);
    int idx = 0;
    for(auto & p : polygon) cin >> p, p.idx = idx++;
    auto t = delaunay(polygon);
    vector<point> candidates;
    unordered_map<pair<int, int>, vector<point>, HASH> edgesDelaunay;
    for(auto & triangle : t){
        point A, B, C, center;
        ld radius;
        tie(A, B, C) = triangle;
        tie(center, radius) = getCircle(A, B, C);
        if(pointInPolygon(polygon, center)) candidates.push_back(center);
        vector<int> indices = {A.idx, B.idx, C.idx};
        sort(indices.begin(), indices.end());
        int i = indices[0], j = indices[1], k = indices[2];
        edgesDelaunay[{i, j}].push_back(center);
        edgesDelaunay[{i, k}].push_back(center);
        edgesDelaunay[{j, k}].push_back(center);
        //cout << "triangle: " << A << " " << B << " " << C << ", center:" << center << " " << radius << "\n";
    }

    for(auto & edge : edgesDelaunay){
        int i, j;
        tie(i, j) = edge.first;
        auto & voronoiEdge = edge.second;
        if(voronoiEdge.size() == 1){
            //cout << "one:" << polygon[i] << " " << polygon[j] << "\n";
            point v = polygon[j] - polygon[i];
            v = v / v.length();
            point nuevo = (v * (voronoiEdge[0] - polygon[i]).dot(v) - (voronoiEdge[0] - polygon[i])) * 2 + voronoiEdge[0];
            voronoiEdge.push_back(nuevo);
            //cout << "new:" << nuevo << "\n";
        }
        if(voronoiEdge.size() == 2){
            //cout << "Voronoi edge: " << voronoiEdge[0] << " " << voronoiEdge[1] << "\n";
            for(int k = 0; k < n; ++k){
                if(intersectSegmentsInfo(polygon[k], polygon[(k+1)%n], voronoiEdge[0], voronoiEdge[1]) == 1){
                    candidates.push_back(intersectLines(polygon[k], polygon[(k+1)%n] - polygon[k], voronoiEdge[0], voronoiEdge[1] - voronoiEdge[0]));
                }
            }
        }
    }

    ld ans = 0;
    for(auto & candidate : candidates){
        //cout << "candidate: " << candidate << "\n";
        ld mini = inf;
        for(auto & p : polygon){
            mini = min(mini, (p - candidate).length());
        }
        ans = max(ans, mini);
    }
    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}