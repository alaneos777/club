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

ii cuerda[MX + 2];

bool f(int n, ll D){
    ll fin = 0;
    forn(i, n){
        ll l = cuerda[i].fi;
        ll r = cuerda[i].se;
        if(r < fin) return false;
        ll pos = max(fin, l);
        fin = pos + D;
    }
    return true;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    forn(i, n){
        cin >> cuerda[i].fi;
        cin >> cuerda[i].se;
        cuerda[i].se += cuerda[i].fi;
    }
    sort(cuerda, cuerda + n);

    ll izq = 0, der = 1e15;
    while(izq < der){
        ll medio = (1LL + izq + der) / 2;
        if(f(n, medio)){
            izq = medio;
        }else{
            der = medio - 1;
        }
    }
    cout << izq << endl;

	return 0;
}
