#include <bits/stdc++.h>
#define endl '\n'
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define eb emplace_back
#define pb(x) push_back(x)
#define fi first
#define se second
#define all(v) v.begin(), v.end()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 1000;

int LIM = 0;

struct Seg{
    ll desde, hasta;
    ll mejor, total;
    ll mayor_pref, mayor_suf;
    Seg *izq, *der;

    Seg(ll i, ll d) : desde(i), hasta(d), total(0), mejor(0), mayor_suf(0), mayor_pref(0), izq(NULL), der(NULL) {}
    ~Seg(){
        if(izq != NULL) delete izq;
        if(der != NULL) delete der;
    }

    void combina(){
        mejor = max({izq->mejor, der->mejor, izq->mayor_suf + der->mayor_pref});
        mayor_pref = max(izq->mayor_pref, izq->total + der->mayor_pref);
        mayor_suf = max(der->mayor_suf, der->total + izq->mayor_suf);
        total = izq->total + der->total;
    }

    void update(ll pos, ll val){
        if(desde > pos || hasta < pos) return;
        if(desde >= hasta){
            total += val;
            mejor += val;
            mayor_pref += val;
            mayor_suf += val;
        }else{
            if(izq == NULL){
                ll mitad = (desde + hasta) / 2LL;
                izq = new Seg(desde, mitad);
                der = new Seg(mitad + 1, hasta);
            }
            izq->update(pos, val);
            der->update(pos, val);
            combina();
        }
    }

    ll query(){
        return mejor;
    }
};

struct EVENTO{
    ii punto;
    int tipo;

    EVENTO(ii p, int t) : punto(p), tipo(t) {}

    const bool operator < (const EVENTO& otro) const{
        if(punto == otro.punto) return tipo < otro.tipo;
        return punto < otro.punto;
    }
};

ii P1[MX + 2];
ii P2[MX + 2];
ll c1, c2;

void comprime(int n1, int n2){
    set<ll> x_cord, y_cord;
    forn(i, n1) x_cord.insert(P1[i].fi);
    forn(i, n2) x_cord.insert(P2[i].fi);
    forn(i, n1) y_cord.insert(P1[i].se);
    forn(i, n2) y_cord.insert(P2[i].se);

    map<ll, int> map_x, map_y;
    int cnt_x = 0, cnt_y = 0;
    set<ll>::iterator it_x = x_cord.begin();
    while(it_x != x_cord.end()){
        map_x[*it_x] = cnt_x;
        cnt_x++;
        it_x++;
    }
    set<ll>::iterator it_y = y_cord.begin();
    while(it_y != y_cord.end()){
        map_y[*it_y] = cnt_y;
        cnt_y++;
        it_y++;
    }

    forn(i, n1) P1[i].fi = map_x[P1[i].fi];
    forn(i, n2) P2[i].fi = map_x[P2[i].fi];
    forn(i, n1) P1[i].se = map_y[P1[i].se];
    forn(i, n2) P2[i].se = map_y[P2[i].se];
    LIM = max(cnt_x, cnt_y);
}

vector<EVENTO> eventos;

ll resuelve(){
    int N = eventos.size();
    ll res = 0;

    forn(i, N){
        Seg* tree = new Seg(0, 2 * LIM);
        int j = i;
        while(j < N){
            ii P = eventos[j].punto;
            ll val = (eventos[j].tipo == 1 ? c1 : -c2);
            tree->update(P.se, val);
            res = max(res, tree->query());
            j++;
        }
        delete tree;
    }
    return res;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n1;
    cin >> n1;
    forn(i, n1){
        cin >> P1[i].fi;
        cin >> P1[i].se;
    }
    int n2;
    cin >> n2;
    forn(i, n2){
        cin >> P2[i].fi;
        cin >> P2[i].se;
    }
    comprime(n1, n2);
    forn(i, n1) eventos.eb(P1[i], 1);
    forn(i, n2) eventos.eb(P2[i], 2);
    sort(all(eventos));

    cin >> c1 >> c2;

    cout << resuelve() << endl;

	return 0;
}
