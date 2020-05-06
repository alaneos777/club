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
const int MAXV = 15000;

vi ini[MAXV + 2];
vi valor[MAXV + 2];

ll precio[MX + 2];

ll dp[MAXV + 2];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int m, n;
    cin >> m >> n;
    for(int i = 1; i <= m; i++){
        cin >> precio[i];
    }

    for(int i = 1; i <= n; i++){
        int s, e;
        cin >> s >> e;
        int t;
        cin >> t;
        ini[e].pb(s);
        ll V = (e - s) * precio[t];
        valor[e].pb(V);
    }
    for(int x = 1; x <= MAXV; x++){
        ll aux = 0;
        ll mejor = 0;
        int tam = ini[x].size();
        forn(i, tam){
            aux = dp[ini[x][i]] + valor[x][i];
            mejor = max(mejor, aux);
        }
        dp[x] = max(mejor, dp[x - 1]);
    }
    cout << dp[MAXV] << endl;

	return 0;
}
