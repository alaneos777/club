#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int i=1;i<=t;i++){
        int n;
        cin >> n;
        int ans = 315 * n + 36962;
        if(ans < 0) ans *= -1;
        ans = (ans / 10) % 10;
        cout << ans << "\n";
    }
    return 0;
}
