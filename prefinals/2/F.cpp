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

const int MX = 2 * 1e5;

const ll INF = 1e9 + 1;

ll a[MX + 2];
ll b[MX + 2];

int impresos;

stack<int> pendientes;

void activa(int idx){
    if(impresos) cout << " ";
    cout << idx;
    impresos++;
}

void resuelve(int N){
    int idx = 1;
    while(!pendientes.empty() || idx <= N){
        if(pendientes.empty()) pendientes.push(idx++);

        // checa si puedo despachar a este
        int p = pendientes.top();
        if(b[p] < a[p]){
            activa(p);
            pendientes.pop();
        }else{
            // checa si me va a tomar a mi
            ll d1 = abs(b[p] - a[p]);
            ll d2 = idx <= N ? abs(b[p] - a[idx]) : INF;
            if(d1 <= d2){
                // si, me toma a mi
                activa(p);
                pendientes.pop();
            }else{
                pendientes.push(idx++);
            }
        }
    }
    cout << endl;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int N;
    cin >> N;

    for(int i = 1; i <= N; i++){
        cin >> a[i];
    }
    ll total = 0;
    for(int i = 1; i <= N; i++){
        cin >> b[i];
        total += abs(a[i] - b[i]);
    }

    cout << total << endl;
    resuelve(N);

	return 0;
}
