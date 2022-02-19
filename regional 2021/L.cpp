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
 
const int MX = 2 * 1e5;
const ll INF = (1LL << 62);
 
pii lista[MX + 2];
ll pre_div[MX + 2];
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int N, X;
    cin >> N >> X;
 
    for(int i = 1, cnt = 1; i <= MX; i++, cnt++){
        pre_div[i] = pre_div[i - 1];
        if(cnt == X){
            pre_div[i]++;
            cnt = 0;
        }
    }
 
    forn(i, N){
        cin >> lista[i].fi;
        cin >> lista[i].se;
    }
 
    int T = -1;
    ll C = INF;
 
    for(int ini = 0; ini <= 8 * 60; ini++){
        ll act_C = 0;
        forn(i, N){
            int A = lista[i].fi;
            int B = A + lista[i].se;
            if(ini > B) continue;
            act_C += pre_div[B-ini] + 1;
            if(ini >= A) continue;
            act_C -= pre_div[A-1-ini] + 1;
        }
        if(act_C < C){
            T = ini;
            C = act_C;
        }
    }
    cout << T << " " << C << endl;
 
    return 0;
}