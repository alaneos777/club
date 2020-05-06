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

const int MAXV = 1e6;

int cubeta[MAXV + 2];

priority_queue<ii> cola;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k;

    for(int i = 1; i <= n; i++){
        int num;
        cin >> num;
        cubeta[num]++;
    }

    for(int i = 1; i <= MAXV; i++) if(cubeta[i] > 0) cola.push(ii(cubeta[i], i));

    if(cola.size() < k){
        cout << "impossible" << endl;
        return 0;
    }

    vii arr(k);

    while(cola.size() >= k){
        forn(idx, k){
            arr[idx] = cola.top(); cola.pop();
        }
        forn(idx, k){
            cout << arr[idx].se << " \n"[idx == k-1];
            arr[idx].fi--;
            if(arr[idx].fi > 0){
                cola.push(arr[idx]);
            }
        }
    }

	return 0;
}
