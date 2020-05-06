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

int orden[MX + 2];
int cubeta[MX + 2];
int p[MX + 2];
int v[MX + 2];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int c, n;
    cin >> c >> n;
    for(int i = 1; i <= n; i++){
        cin >> v[i];
    }
    for(int i = 1; i <= c; i++) p[i] = i;

    for(int i = 2; i <= n; i++){
        p[v[i - 1]] = p[v[i]];
        int x = p[v[i]];
        cubeta[x]++;
    }
    
    for(int i = 1; i <= c; i++) orden[i] = i;
    sort(orden + 1, orden + c + 1, [&](const int i, const int j){
        return cubeta[i] > cubeta[j];
    });

    ll total = 0;
    ll pos = 1;
    vi sol(c - 1);
    for(int i = 1; i <= c; i++){
        int x = orden[i];
        if(x == v[1]) continue;

        total += (ll)cubeta[x] * pos;
        sol[pos - 1] = x;
        pos++;
    }

    cout << total << endl;
    for(int i = 0; i < c - 1; i++) cout << sol[i] << " \n"[i == c-2];

	return 0;
}
