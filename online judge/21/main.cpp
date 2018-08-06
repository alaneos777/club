#include <bits/stdc++.h>

using namespace std;

int f(int n){
    int ans = 0;
    while(n != 0){
        ans += n%10;
        n /= 10;
    }
    return ans;
}

int g(int n){
    int ans = f(n);
    while(ans/10 != 0){
        ans = f(ans);
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    while(true){
        int n;
        cin >> n;
        if(n == 0) break;
        cout << g(n) << "\n";
    }
    return 0;
}
