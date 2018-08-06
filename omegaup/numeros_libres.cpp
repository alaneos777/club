#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;

ull gcd(ull a, ull b){
    while(b != 0){
        ull r = a%b;
        a = b, b = r;
    }
    return a;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    ull a, b, d;
    for(int i=0;i<n;i++){
        cin >> a >> b;
        d = gcd(a, b);
        if(d == 1) cout << "SI\n";
        else cout << "NO\n";
    }
    return 0;
}
