#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
#define all(v) v.begin(), v.end()
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

const int MX = 1e5;
const ld eps = 1e-9;

struct point{
    ll x, y, z;
    point(): x(0), y(0),z(0) {}
    point(ll x, ll y, ll z): x(x), y(y), z(z) {}
    point operator+(const point & p) const{return point(x+p.x, y+p.y, z+p.z);}
    point operator+=(const point & p){*this = *this + p; return *this;}
    point operator-(const point & p) const{return point(x-p.x, y-p.y, z-p.z);}
    ld len() const{return x*x + y*y + z*z;}
    ll dot(const point & p) const{return x*p.x + y*p.y + z*p.z;}
    point cross(const point & p) const{return point(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);}
    bool operator==(const point & p) const{return x==p.x && y==p.y && z==p.z;}
    bool operator<(const point & p) const{
        if(x != p.x) return x < p.x;
        return y < p.y;
    }
};

ld variance(const vector<point> & points){
    int n = points.size();
    if(n == 0) return 0;
    ld ans1 = 0; point s;
    forn(i, n){
        ans1 += points[i].len();
        s += points[i];
    }
    ld ans = ans1 - s.len() / n;
    return ans;
}

ld variance(const vector<int> & idxs, const vector<point> & points){
    int n = idxs.size();
    if(n == 0) return 0;
    ld ans1 = 0; point s;
    forn(i, n){
        ans1 += points[idxs[i]].len();
        s += points[idxs[i]];
    }
    ld ans = ans1 - s.len() / n;
    return ans;
}

ld brute(const vector<point> & points){
    int n = points.size();
    ld ans = 1e18;
    for(int i = 0; i < (1<<n); ++i){
        vector<point> A, B;
        for(int j = 0; j < n; ++j){
            if(i & (1<<j)){
                A.push_back(points[j]);
            }else{
                B.push_back(points[j]);
            }
        }
        ans = min(ans, variance(A) + variance(B));
    }
    return ans;
}

ld solve(const vector<point> & points){
    auto p = points;
    sort(all(p));
    p.erase(unique(all(p)), p.end());
    int n = p.size();
    ld ans = 1e18;
    vector<int> A, B, C;
    for(int i = 0; i < n-2; ++i){
        for(int j = i+1; j < n-1; ++j){
            for(int k = j+1; k < n; ++k){
                A.clear(), B.clear(), C.clear();
                point u = (p[j] - p[i]).cross(p[k] - p[i]);
                for(int l = 0; l < points.size(); ++l){
                    ll side = u.dot(points[l] - p[i]);
                    if(side > 0){
                        A.pb(l);
                    }else if(side < 0){
                        B.pb(l);
                    }else{
                        C.pb(l);
                    }
                }
                int m = C.size();
                assert(m);
                for(int mask = 0; mask < (1<<m); ++mask){
                    int cnt_a = 0, cnt_b = 0;
                    for(int l = 0; l < m; ++l){
                        if(mask&(1<<l)){
                            A.pb(C[l]);
                            cnt_a++;
                        }else{
                            B.pb(C[l]);
                            cnt_b++;
                        }
                    }
                    ans = min(ans, variance(A, points) + variance(B, points));
                    while(cnt_a--) A.pop_back();
                    while(cnt_b--) B.pop_back();
                }
            }
        }
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<point> points(n);
    forn(i, n){
        cin >> points[i].x >> points[i].y >> points[i].z;
    }
    ld ans = 0;
    if(n == 1){
        ans = 0;
    }else if(k == 1){
        ans = variance(points);
    }else if(n == 2 && k == 2){
        ans = 0;
    }else if(n <= 21){
        ans = brute(points);
    }else{
        ans = solve(points);
    }
    cout << fixed << setprecision(6) << ans << "\n";
    return 0;
}