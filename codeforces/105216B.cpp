#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int q;
    cin >> q;
    while(q--){
        int n, t;
        cin >> n >> t;
        t--;
        if(t == 0){
            cout << n << "\n";
        }else{
            int ans = 0;
            for(int d = 1; d*d <= t; ++d){
                if(t%d != 0) continue;
                int e = t/d;
                if(d <= n) ans++;
                if(e != d && e <= n) ans++;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}