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

const int MX = 500;

const int NO_VISITADO = 0xFF;

const int mov[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

unsigned char max_tiempo[MX + 2][MX + 2];
unsigned char resp[MX + 2][MX + 2][250 + 2];

int dfs(int i, int j, int tiempo){
    if(tiempo > max_tiempo[i][j]) return 0;
    if(resp[i][j][tiempo] != NO_VISITADO) return resp[i][j][tiempo];
    int temp = dfs(i, j, tiempo + 1);
    for(int dir = 0; dir < 4; dir++){
        int sig_i = i + mov[dir][0];
        int sig_j = j + mov[dir][1];
        temp = max(temp, dfs(sig_i, sig_j, tiempo + 1));
    }
    resp[i][j][tiempo] = temp + 1;
    return temp + 1;
}

void resuelve(int N){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(max_tiempo[i][j] == 0){
                resp[i][j][1] = 0;
                continue;
            }
            dfs(i, j, 1);
        }
    }
}

void init(int N){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(max_tiempo[i][j] == 0xFF){
                max_tiempo[i][j] = 0;
                continue;
            }
            max_tiempo[i][j] = min({i, j, N - i + 1, N - j + 1});
        }
    }
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int N;
    cin >> N;

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            for(int k = 0; k <= (N / 2) + 1; k++){
                resp[i][j][k] = NO_VISITADO;
            }
        }
    }

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            char c;
            cin >> c;
            if(c == '#') max_tiempo[i][j] = 0xFF;
        }
    }

    init(N);

    resuelve(N);

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cout << (int)(resp[i][j][1]) << " ";
        } cout << endl;
    }

	return 0;
}
