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

const int MX = 20;
const ld eps = 1e-9;

int visitado[MX + 2][MX + 2];

int res = 0;

string s;
int n;

void avanza(int &i, int &j, char dir){
    if(dir == 'U') i--;
    if(dir == 'R') j++;
    if(dir == 'D') i++;
    if(dir == 'L') j--;
}

bool valida(int i, int j){
    if(i < 1 || j < 1) return false;
    if(i > 3 || j > 3) return false;
    return visitado[i][j] == 0;
}

void dfs(int i, int j, int idx){
    if(idx == n){
        res++;
        return;
    }

    visitado[i][j] = 1;
    int ant_i = i, ant_j = j;

    avanza(i, j, s[idx]);
    if(valida(i, j)){
        dfs(i, j, idx + 1);

        visitado[i][j] = 1;
        int i2=i, j2=j;

        avanza(i, j, s[idx]);
        if(valida(i, j)){
            dfs(i, j, idx + 1);
        }
        visitado[i2][j2] = 0;
    }

    i = ant_i;
    j = ant_j;

    visitado[i][j] = 0;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> s;
    n = s.size();

    for(int i = 1; i <= 3; i++){
        for(int j = 1; j <= 3; j++){
            dfs(i, j, 0);
        }
    }

    cout << res << endl;

    return 0;
}

