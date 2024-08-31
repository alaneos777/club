#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int solve(const vector<int>& a){
    int n = a.size()-1;
    vector<bool> vis(n+1);
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        if(vis[i]) continue;
        int u = a[i];
        int len_cycle = 0;
        while(!vis[u]){
            vis[u] = true;
            u = a[u];
            len_cycle++;
        }
        ans += len_cycle - 1;
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n+1), b(n+1);
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
    }
    for(int i = 1; i <= n; ++i){
        cin >> b[i];
    }
    cout << solve(a) + solve(b) << "\n";
    return 0;
}