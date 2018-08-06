#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b){
    while(b!=0){
        int res = a%b;
        a = b, b = res;
    }
    return a;
}

int main()
{
    while(true){
        ios_base::sync_with_stdio(0);
        int a, b, c;
        cin >> a >> b >> c;
        if(a==0 && b==0 && c==0) break;
        int d = gcd(a,b);
        if(c%d==0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
