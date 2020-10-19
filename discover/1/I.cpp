#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; ++i)
#define rep(i, a, b) for(int i = a; i < b; ++i)
#define eb emplace_back
#define pb push_back
#define fi first
#define se second
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

const int MX = 1000;
const int INF = 1e5;

ll A[MX + 2][MX + 2];

pair<ll, ll> menor[MX + 2];
ll acc_izq[MX + 2];
ll acc_der[MX + 2];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int N, M;
    cin >> N >> M;
    for(int i = 1; i <= N; i++){    
        for(int j = 1; j <= M; j++){
            cin >> A[i][j];
        }
    }

    for(int j = 1; j <= M; j++){
        menor[j] = pair<ll, ll>(INF, INF);
        for(int i = 1; i <= N; i++){
            if(A[i][j] < menor[j].fi){
                menor[j].se = menor[j].fi;
                menor[j].fi = A[i][j];
            }else if(A[i][j] < menor[j].se){
                menor[j].se = A[i][j];
            }
        }
    }

    for(int j = 1; j <= M; j++) acc_izq[j] = acc_izq[j - 1] + menor[j].fi;
    for(int j = M; j >= 1; j--) acc_der[j] = acc_der[j + 1] + menor[j].fi;

    ll res = acc_der[1];
    for(int j = 1; j <= M; j++){
        ll aux = acc_izq[j - 1] + acc_der[j + 1];
        aux += min(menor[j].se, 2 * menor[j].fi);
        res = max(res, aux);
    }
    cout << res << endl;

    return 0;
}
