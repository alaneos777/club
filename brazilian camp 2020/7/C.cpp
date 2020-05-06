#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

const int MX = 3 * 1e5;
const ld eps = 1e-9;

struct SuffixAutomata{
    int t[MX + 2][26], lnk[MX + 2], len[MX + 2];
    int sz;
    int last;

    bool es_terminal[MX + 2];
    int dp[MX + 2];

    void init(){
        memset(t, 0, sizeof(t));
        memset(lnk, 0, sizeof(lnk));
        memset(len, 0, sizeof(len));
        
        memset(es_terminal, 0, sizeof(es_terminal));
        memset(dp, -1, sizeof(dp));

        sz = 3;
        last = 1;
        forn(i, 26) t[2][i] = 1;
        len[2] = -1;
        lnk[1] = 2;
    }

    int caminos(int nodo){
        if(dp[nodo] != -1) return dp[nodo];
        dp[nodo] = es_terminal[nodo];
        for(int c = 0; c < 26; c++)
            if(t[nodo][c]) dp[nodo] += caminos(t[nodo][c]);
        return dp[nodo];
    }

    void addchar(int c){
        int nlast = sz++;
        len[nlast] = len[last] + 1;
        int p = last;
        for(; !t[p][c]; p = lnk[p]){
            t[p][c] = nlast;
        }
        int q = t[p][c];
        if(len[p] + 1 == len[q]){
            lnk[nlast] = q;
        } else{
            int clone = sz++;
            len[clone] = len[p] + 1;
            lnk[clone] = lnk[q];
            lnk[q] = lnk[nlast] = clone;
            forn(i, 26) t[clone][i] = t[q][i];
            for(; t[p][c] == q; p = lnk[p]){
                t[p][c] = clone;
            }
        }
        last = nlast;
    }

    void marca_terminales(){
        int nodo = last;
        while(nodo != 1){
            es_terminal[nodo] = true;
            nodo = lnk[nodo];
        }
    }
};

int a[MX + 2];

SuffixAutomata SA;

void crea_a(const string& s, int n, const string& t, int m){
    SA.init();
    for(int i = 1; i < n; i++) SA.addchar(s[i] - 'a');
    SA.marca_terminales();

    int estado = 1;
    forn(i, m){
        int c = t[i] - 'a';
        if(!SA.t[estado][c]) break;
        estado = SA.t[estado][c];
        a[i] = SA.caminos(estado);
    }
}

int bruta(const string& S, int n, const string& T, int m){
    set<string> totales;

    rep(i, 1, n+1){
        rep(j, 1, m+1){
            totales.insert(S.substr(0, i) + T.substr(0, j));
        }
    }

    return totales.size();
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    string s, t;
    cin >> s >> t;
    vector<int> b(t.size());
    int i = 1, j = 0;
    while(i < t.size()){
        if(t[i] == t[j]){
            b[i++] = ++j;
        }else{
            if(j == 0) b[i++] = 0;
            else j = b[j-1];
        }
    }
    int n = s.size(), m = t.size();

    crea_a(s, n, t, m);
    ll ans = (ll)n*m;
    for(int idx = 0; idx < m; ++idx){
        //cout << b[idx] << " ";
        if(b[idx] == 0) continue;
        ans -= a[idx - b[idx]];
    }
    cout << ans << "\n";

    //cerr << bruta(s, n, t, m) << endl;
    return 0;
}

