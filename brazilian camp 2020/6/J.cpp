#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
#define all(v) v.begin(), v.end()
using namespace std;

using ll = long long int;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

const int MX = 100005, inf = int(2e9) + 5;

struct ST {
    int st[4 * MX], p[MX];
    
    void build (int i, int j, int pos) {
        if (i == j) {
            p[i] = pos;
            return;
        }
        
        int m = (i + j) / 2;
        build(i, m, pos * 2);
        build(m + 1, j, pos * 2 + 1);
    }
    
    void update (int i, int k) {
        int pos = p[i];
        st[pos] = k;
        pos /= 2;
        
        while (pos) {
            st[pos] = max(st[pos * 2], st[pos * 2 + 1]);
            pos /= 2;
        }
    }
    
    int query (int i, int j, int pos, int a, int b) {
        if (a > b) return -inf;
        if (j < a || b < i) return -inf;
        if (a <= i && j <= b) return st[pos];
        int m = (i + j) / 2;
        return max(query(i, m, pos * 2, a, b), query(m + 1, j, pos * 2 + 1, a, b));
    }
}pos, neg;

int n, s, h[MX], x[MX];
map<int, set<int>> ma, mb;
ll res;

void erase (int s) {
    pos.update(s, -inf);
    neg.update(s, -inf);
    ma[h[s] + x[s]].erase(s);
    mb[h[s] - x[s]].erase(s);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> s;
    pos.build(1, n, 1);
    neg.build(1, n, 1);
    
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> h[i];
        pos.update(i, h[i] + x[i]);
        neg.update(i, h[i] - x[i]);
        ma[h[i] + x[i]].insert(i);
        mb[h[i] - x[i]].insert(i);
    }
    
    erase(s);
    
    for (int i = 1; i < n; i++) {
        int der = neg.query(1, n, 1, s + 1, n);
        int izq = pos.query(1, n, 1, 1, s - 1);
        if (der != -inf) der += x[s];
        if (izq != -inf) izq -= x[s];
        
        if (izq < der) {
            auto it = mb[der - x[s]].upper_bound(s);
            res += abs(x[s] - x[*it]);
            s = *it;
        } else if (izq > der) {
            auto jt = ma[izq + x[s]].upper_bound(s);
            jt--;
            res += abs(x[s] - x[*jt]);
            s = *jt;
        } else {
            auto it = mb[der - x[s]].upper_bound(s);
            auto jt = ma[izq + x[s]].upper_bound(s);
            jt--;
            
            if (abs(x[*jt] - x[s]) <= abs(x[*it] - x[s])) {
                res += abs(x[*jt] - x[s]);
                s = *jt;
            } else {
                res += abs(x[*it] - x[s]);
                s = *it;
            }
        }
        
        erase(s);
    }
    
    cout << res << endl;
    
    return 0;
}

