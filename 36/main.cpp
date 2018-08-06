#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ull k;
    cin >> n >> k;
    vector<ull> a(n), c(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    ull m = 1000000000+7;
    c[0] = 1;
    for(int i=1;i<n;i++){
        c[i] = (c[i-1]*(i+k-1)/i) % m;
    }
    for(int i=0;i<n;i++){
        ull ans = 0;
        for(int j=i;j>=0;j--){
            ans = (ans + a[j]*c[i-j]) % m;
        }
        cout << ans << " ";
    }
    return 0;
}
