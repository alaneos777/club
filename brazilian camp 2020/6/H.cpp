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
using ii = pair<int, int>;
using vi = vector<int>;

const int MX = 100005;
stack<int> st[MX];
int n, q, a[MX], b[MX];
priority_queue<ii> pq;
vi v[MX], res;

void no () {
    cout << "Impossible" << endl;
    exit(0);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> q >> n;
    for (int i = 0; i <= q + 1; i++)
        st[i].push(-1e9);
    
    for (int i = 1; i <= q; i++) {
        cin >> a[i];
        a[i]++;
        for (int j = 1; j < a[i]; j++) {
            int x;
            cin >> x;
            st[i].push(x);
        }
    }
    
    for (int i = 1; i <= q; i++) {
        cin >> b[i];
        b[i]++;
        v[i].pb(-1e9);
        for (int j = 1; j < b[i]; j++) {
            int x;
            cin >> x;
            v[i].pb(x);
        }
    }
    
    for (int i = 1; i <= q; i++)
        if (a[i] > b[i]) {
            pq.emplace(st[i].top(), i);
        }
        
    while (pq.size()) {
        int ind = pq.top().se;
        pq.pop();
        
        if (st[ind].top() > st[ind - 1].top() || st[ind].top() > st[ind + 1].top()) {
            if (st[ind].top() > st[ind - 1].top()) {
                res.pb(ind - 1);
            } else if (st[ind].top() > st[ind + 1].top()) {
                res.pb(ind);
            } else {
                assert(0);
            }
            
            st[ind].pop();
            
            if (st[ind].size() > b[ind]) {
                pq.emplace(st[ind].top(), ind);
            }
        } else {
            no();
        }
    }
    
    for (int i = 1; i <= q; i++) {
        if (st[i].size() != b[i]) no();
        
        while (st[i].size()) {
            if (st[i].top() != v[i].back()) no();
            st[i].pop();
            v[i].pop_back();
        }
    }
    
    int f = 0;
    cout << res.size() << endl;
    for (int r : res) {
        if (f) cout << " ";
        cout << r;
        f = 1;
    }
    cout << endl;
    
    return 0;
}

