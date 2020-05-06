#include <bits/stdc++.h>
#define endl '\n'
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
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

const int MX = 1e5;
const ll INF = (1LL << 45);

struct Seg{
    int desde, hasta;
    ll menor;
    Seg *izq, *der;

    Seg(int i, int d) : desde(i), hasta(d), menor(INF), izq(NULL), der(NULL) {}

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

    void update(int pos, ll v){
        if(desde > pos || hasta < pos) return;
        if(desde >= hasta){
            menor = min(v, INF);
        }else{
            izq->update(pos, v);
            der->update(pos, v);
            menor = min(izq->menor, der->menor);
        }
    }
    
    ll query(int ri, int rf){
        if(desde > rf || hasta < ri) return INF;
        if(desde >= ri && hasta <= rf) return menor;
        return min(izq->query(ri, rf), der->query(ri, rf));
    }
};

Seg* tree;

ll x[MX + 2];
int color[MX + 2];

int ultimo_de_bloque[MX + 2];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int m, n;
    cin >> m >> n;

    forn(i, n) cin >> x[i];
    forn(i, n) cin >> color[i];

    ultimo_de_bloque[n - 1] = n - 1;
    for(int i = n - 2; i >= 0; i--){
        if(color[i] == color[i + 1]) ultimo_de_bloque[i] = ultimo_de_bloque[i + 1];
        else ultimo_de_bloque[i] = i;
    }

    if(ultimo_de_bloque[0] == n - 1){
        // solo hay un bloque
        cout << 1 << endl;
        return 0;
    }

    tree = new Seg(0, n - 1);
    tree->build();

    int i = n - 1;
    while(ultimo_de_bloque[i] == n - 1){
        tree->update(i, 1);
        i--;
    }

    int l, r;
    ll dp;
    while(i >= 0){
        // tomar del mismo bloque
        l = i + 1;
        r = ultimo_de_bloque[i];
        dp = (l <= r) ? tree->query(l, r) + 1 : INF;

        // tomar del siguiente bloque
        ll min_x = (x[r] << 1) - x[i];
        ll max_x = (x[r + 1] << 1) - x[i];
        int pos_min = lower_bound(x, x + n, min_x) - x;
        int pos_max = upper_bound(x, x + n, max_x) - x - 1;
        pos_max = min(pos_max, ultimo_de_bloque[r + 1]);
        l = pos_min;
        r = pos_max;
        if(l <= r) dp = min(dp, tree->query(l, r) + 1);
        tree->update(i, dp);
        i--;
    }
    i = 0;
    dp = tree->query(i, ultimo_de_bloque[i]);

    assert(dp <= n);

    cout << dp << endl;

	return 0;

}
