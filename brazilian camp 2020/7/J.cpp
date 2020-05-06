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

const int MX = 100005;
map<char, int> nex[MX], dp[MX];
int fail[MX], out[MX], finish[MX], cnt[MX], sz = 1, mn[MX], len[MX];

void add (string &s, int ind) {
    int u = 0;
    
    for (char c : s) {
        if (!nex[u].count(c)) {
            nex[u][c] = sz;
            finish[sz] = -1;
            mn[sz] = 1e9;
            sz++;
        }
        
        u = nex[u][c];
    }
    
    finish[u] = 1;
    cnt[u] = 1;
    mn[u] = s.size();
}

int getFail (int u, int c) {
    if (dp[u].count(c)) return dp[u][c];
    if (u && !nex[u].count(c))
        return dp[u][c] = getFail(fail[u], c);
    return dp[u][c] = nex[u][c];
}

void build () {
    queue<int> q;
    
    for (auto it = nex[0].begin(); it != nex[0].end(); it++)
        q.push(it->se);
    
    while (q.size()) {
        int u = q.front();
        q.pop();
        
        for (auto it = nex[u].begin(); it != nex[u].end(); it++) {
            int v = it->se;
            
            fail[v] = getFail(fail[u], it->fi);
            cnt[v] += cnt[fail[v]];
            mn[v] = min(mn[v], mn[fail[v]]);
            q.push(v);
        }
    }
}

string s, in;
vector<string> t;

string match (string &s) {
    int u = 0;
    string res;
    stack<int> st, ch;
    st.push(0);
    
    for (char c : s) {
        if (nex[u].count(c))
            u = nex[u][c];
        else
            u = getFail(u, c);
        st.push(u);
        ch.push(c);
        
        if (cnt[u]) {
            int k = mn[u];
            while (k--) {
                st.pop();
                ch.pop();
            }
            u = st.top();
        }
    }
    
    while (ch.size()) {
        res.pb(ch.top());
        ch.pop();
    }
    
    reverse(all(res));
    return res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    mn[0] = 1e9;
    
    cin >> s;
    while (cin >> in) {
        t.pb(in);
        add(in, 0);
    }
    
    build();
    cout << match(s) << endl;
    
    return 0;
}

