#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<lli> lp;
void sieve(lli n){
    lp.resize(n + 1, 1);
    lp[0] = lp[1] = 0;
    for(lli i = 2; i <=n; ++i) lp[i] = (i & 1 ? i : 2);
    lli limit = sqrt(n);
    for(lli i = 3; i <= limit; i += 2){
        if(lp[i] == i){
            for(lli j = i * i; j <= n; j += 2*i){
                if(lp[j] == j) lp[j] = i;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    sieve(1e6+10);
    while(t--){
        int ans = 0;
        int n;
        cin >> n;
        while(n != 1){
            int p = lp[n];
            int pot = 0;
            while(n % p == 0) ++pot, n /= p;
            ans = max(ans, pot);
        }
        cout << ans << "\n";
    }
    return 0;
}