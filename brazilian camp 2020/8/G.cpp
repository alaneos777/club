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
const int INF = 1e9;

int dp[MX + 2];

struct Seg{
    int desde, hasta;
    int menor;
    Seg *izq, *der;

    Seg(int i, int d) : desde(i), hasta(d), menor(-1), izq(NULL), der(NULL) {}

    void build(){
        if(desde >= hasta){
            menor = INF;
        }else{
            int mitad = (desde + hasta) / 2;
            izq = new Seg(desde, mitad);
            der = new Seg(mitad + 1, hasta);
            izq->build();
            der->build();
            menor = min(izq->menor, der->menor);
        }
    }

    void update(int i, int v){
        if(desde > i || hasta < i) return;
        if(desde >= hasta){
            menor = v;
        }else{
            izq->update(i, v);
            der->update(i, v);
            menor = min(izq->menor, der->menor);
        }
    }

    int query(int ri, int rf){
        if(desde > rf || hasta < ri) return INF;
        if(desde >= ri && hasta <= rf) return menor;
        return min(izq->query(ri, rf), der->query(ri, rf));
        return 0;
    }
};

int x[MX + 2];
int color[MX + 2];
int pos_ultimo[MX + 2];

int n;

Seg *tree;

void resuelve(int idx){
    int p = pos_ultimo[idx];
    if(p == n-1){
        tree->update(idx, 1);
        return;
    }

    int d = x[p] - x[idx];
    int l = lower_bound(x, x + n, x[p] + d) - x;

    d = x[p + 1] - x[idx];
    int r = upper_bound(x, x + n, x[p + 1] + d) - x - 1;

    int no_poner = INF;

    l = max(l, p + 1);
    r = min(r, pos_ultimo[p + 1]);

    if(l <= r) no_poner = tree->query(l, r) + 1;

    int poner = INF;

    l = idx + 1;
    r = p;
    if(l <= r) poner = tree->query(l, r) + 1;

    tree->update(idx, min(poner, no_poner));
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int m;
    cin >> m >> n;

    tree = new Seg(0, n - 1);
    tree->build();

    forn(i, n) cin >> x[i];
    forn(i, n) cin >> color[i];

    pos_ultimo[n - 1] = n - 1;
    for(int i = n - 2; i >= 0; i--){
        if(color[i] == color[i + 1]) pos_ultimo[i] = pos_ultimo[i + 1];
        else pos_ultimo[i] = i;
    }

    for(int i = n - 1; i >= 0; i--) resuelve(i);
    cout << tree->query(0, pos_ultimo[0]) << endl;

    return 0;
}

