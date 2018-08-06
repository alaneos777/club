#include <bits/stdc++.h>

using namespace std;
typedef long long int ull;

ull mod(ull a, ull b){
    ull ans = a%b;
    if(ans<0) ans += b;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n;
    ull suma = 0, m = 1000000007;
    cin >> n;
    vector<ull> x(n), y(n), x_b(n+1), y_b(n+1);
    for(int i=0;i<n;i++){
        cin >> x[i] >> y[i];
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x_b[0] = y_b[0] = 0;
    for(int i=0;i<n;i++){
        x_b[i+1] = x[i] + x_b[i];
        y_b[i+1] = y[i] + y_b[i];
    }
    for(ull i=n-1;i>=1;i--){
        suma = mod(suma + x_b[n] - x_b[i] - i*x[n-i-1], m);
        suma = mod(suma + y_b[n] - y_b[i] - i*y[n-i-1], m);
    }
    cout << suma;
    return 0;
}
