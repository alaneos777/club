#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
#define all(v) v.begin(), v.end()
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

const int MX = 1e5;
const ld eps = 1e-9;

struct PUNTO{
    ll x, y;
    const bool operator < (const PUNTO& otro) const{
        if(x == otro.x) return y < otro.y;
        return x < otro.x;
    }
};

PUNTO punto[MX + 2];
ll sol[MX + 2];

void matate(){
    cout << -1 << endl;
    exit(0);
}

void resuelve(int n){
    int inicios[4 + 2];
    rep(i, 1, 4) inicios[i] = -1;
    
    forn(i, n){
        if(inicios[punto[i].x] != -1) continue;
        inicios[punto[i].x] = i;
    }

    rep(i, 1, 4) if(inicios[i] == -1) matate();

    int a, b;

    // de x=2 a x=3
    a = inicios[2];
    b = inicios[3];
    while(punto[a].x == 2){
        while(b < n && punto[b].x == 3 && (punto[b].y < punto[a].y || sol[b] == -1)) b++;

        if(sol[a - 1] != -1 && punto[a - 1].x == 2) sol[a] = sol[a - 1] + abs(punto[a].y - punto[a - 1].y);
        if(b < n && punto[b].x == 3 && sol[b] != -1){
            ll aux = sol[b];
            aux += abs(punto[b].y - punto[a].y) + 1;
            if(sol[a] == -1 || sol[a] > aux) sol[a] = aux;
        }
        a++;
    }

    // de x=1 a x=2
    a = inicios[1];
    b = inicios[2];
    while(punto[b].x == 2) b++;
    b--;
    while(punto[a].x == 1) a++;
    a--;

    while(a >= inicios[1]){
        while(b >= inicios[2] && (punto[b].y > punto[a].y || sol[b] == -1)) b--;

        if(sol[a + 1] != -1 && punto[a + 1].x == 1) sol[a] = sol[a + 1] + abs(punto[a].y - punto[a + 1].y);
        if(b >= inicios[2] && sol[b] != -1){
            ll aux = sol[b];
            aux += abs(punto[b].y - punto[a].y) + 1;
            if(sol[a] == -1 || sol[a] > aux) sol[a] = aux;
        }
        a--;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int s, t;
    int n;
    cin >> n >> s >> t;

    forn(i, n){
        cin >> punto[i].x;
        cin >> punto[i].y;
    }
    sort(punto, punto + n);

    forn(i, n){
        sol[i] = -1;
        if(punto[i].x == 3 && punto[i].y >= t){
            sol[i] = punto[i].y - t + 1;
        }
    }

    resuelve(n);

    ll res = -1;
    forn(i, n){
        if(sol[i] == -1) continue;
        if(punto[i].x == 1 && punto[i].y >= s){
            ll aux = punto[i].y - s + sol[i];
            if(res == -1 || res > aux) res = aux;
        }
    }

    cout << res << endl;

    return 0;
}

