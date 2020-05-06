#include <bits/stdc++.h>
#define endl '\n'
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define pb(x) push_back(x)
#define eb emplace_back
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

const int MX = 2 * 1e5;

const int ABRE = 0;
const int CIERRA = 1;

struct EVENTO{
    ll x;
    int tipo;
    EVENTO(ll a = 0, int b = 0) : x(a), tipo(b) {}
    const bool operator < (const EVENTO& otro) const{
        if(x == otro.x) return tipo < otro.tipo;
        return x < otro.x;
    }
};

vector<EVENTO> eventos;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    ll H, L;
    cin >> H >> L;
    int n;
    cin >> n;
    forn(i, n){
        ll P, V;
        cin >> P >> V;

        ll low = 0;
        if(P > L) low = ( (P - L) * V + H - 1LL) / H;
        ll upp = (P * V) / H;
        eventos.eb(low, ABRE);
        eventos.eb(upp, CIERRA);
    }
    sort(all(eventos));

    int mayor = 0, aux = 0;
    ll resp = 0;

    for(EVENTO e : eventos){
        if(e.tipo == ABRE) aux++;
        else aux--;
        if(aux > mayor){
            mayor = aux;
            resp = e.x;
        }
    }
    cout << resp << endl;

	return 0;

}
