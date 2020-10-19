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

const int MX = 1e6;

ll B[MX + 2];
ll G[MX + 2];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int N, M;
    cin >> N >> M;
    forn(i, N){
        int x;
        cin >> x;
        B[x]++;
    }
    forn(i, M){
        int x;
        cin >> x;
        G[x]++;
    }

    ll res = 0;
    for(int x = 1; x <= MX; x++)
        for(int i = 1, j = x; j <= MX; i++, j += x)
            res += i * B[j] * G[x];

    cout << res << endl;
    return 0;
}
