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
 
const int MX = 1e4;
const int MAX_K = 750;
const ll MOD = 1e9 + 7;
 
ll T_min[MAX_K+2][MAX_K+2];
ll T_max[MAX_K+2][MAX_K+2];
ll P[MX+2];
 
ll dp[2][MAX_K + 2];
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int K;
    ll L;
    cin >> K;
    cin >> L;
 
    for(int i = 1; i <= K; i++){
        for(int j = 1; j <= K; j++){
            cin >> T_min[i][j];
            T_max[i][j] = T_min[i][j];
            T_min[i][j] -= L;
            T_max[i][j] += L;
        }
    }
 
    int N;
    cin >> N;
    for(int i = 1; i < N; i++) cin >> P[i];
 
    int act = 0, ant = 1;
    for(int i = 1; i <= K; i++) dp[act][i] = i;
 
    for(int n = N-1; n >= 1; n--){
        swap(act, ant);
 
        for(int i = 1; i <= K; i++){
            dp[act][i] = dp[act][i - 1];
 
            int A = lower_bound(T_max[i]+1, T_max[i]+K+1, P[n]) - T_max[i];
            int B = upper_bound(T_min[i]+1, T_min[i]+K+1, P[n]) - T_min[i];
            B--;
 
            if(A > B) continue;
            dp[act][i] = (dp[act][i] + dp[ant][B]) % MOD;
            dp[act][i] = (dp[act][i] + MOD - dp[ant][A - 1]) % MOD;
        }
    }
 
    cout << dp[act][K] << endl;
 
    return 0;
}