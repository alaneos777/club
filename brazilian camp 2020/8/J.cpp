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

int m[MX + 2];
int g[MX + 2];

void calcula(int n){
    int menor_m = max(m[n - 1], g[n - 1] + 1);
    int act_g = g[n - 1] + 1;

    for(int i = 2; i <= n - 2; i++){
        int aux = max({m[n - i], m[i + 1], 2 + g[n - i] + g[i + 1]});
        if(aux < menor_m){
            menor_m = aux;
            act_g = max(g[n - i], g[i + 1]) + 1;
        }else if(aux == menor_m){
            int aux_g = max(g[n - i], g[i + 1]) + 1;
            act_g = min(act_g, aux_g);
        }
    }
    m[n] = menor_m;
    g[n] = act_g;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    /*
    int N;
    cin >> N;

    m[3] = 0;
    g[3] = 0;

    cout << "[3] : 0 0" << endl;

    for(int n = 4; n <= N; n++){
        calcula(n);
        cout << "[" << n << "] : " << m[n] << " " << g[n] << endl;
    }
    */

    int n;
    cin >> n;

    int ant = 2;
    int fin = 4;
    int r = 0;

    while(n > fin){
        ant = fin;
        fin <<= 1;
        r += 2;
    }
    fin = (fin + ant) / 2;
    if(n > fin) r++;
    cout << r << endl;
    
    return 0;
}

