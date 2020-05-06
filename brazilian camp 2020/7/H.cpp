#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

const int MX = 1e6;
const ld eps = 1e-9;

pair<char, int> par[MX + 2];
pair<char, int> par_tmp[MX + 2];

int cubeta[MX + 2];

int sig[MX + 2];
string cad;

char resp[MX + 2];

void orden(int n){
    forn(i, n){
        cubeta[par[i].fi]++;
    }
    rep(i, 1, 300) cubeta[i] += cubeta[i - 1];
    for(int i = n - 1; i >= 0; i--){
        int pos = par[i].fi;
        par_tmp[cubeta[pos] - 1] = par[i];
        cubeta[pos]--;
    }
    
    forn(i, n) par[i] = par_tmp[i];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int idx;
    cin >> idx;
    idx--;

    cin >> cad;
    int n = cad.size();

    forn(i, n) par[i] = pair<char, int>(cad[i], i);
    orden(n);

    forn(i, n){
        sig[par[i].se] = i;
    }

    forn(i, n){
        resp[i] = cad[idx];
        idx = sig[idx];
    }

    for(int i = n - 1; i >= 0; i--) cout << resp[i];
    cout << endl;

    return 0;
}

