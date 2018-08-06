#include <bits/stdc++.h>

using namespace std;

int modulo(int a, int b){
    int ans = a%b;
    if(ans < 0) ans += b;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    string linea;
    int l = 40;
    int g = 360;
    while(getline(cin, linea)){
        stringstream ss(linea);
        int pos, a, b, c;
        ss >> pos >> a >> b >> c;
        if(pos == 0 && a == 0 && b == 0 && c == 0) break;
        int ans = 2*g;
        ans += modulo(pos - a, l) * (g / l);
        ans += g;
        ans += modulo(b - a, l) * (g / l);
        ans += modulo(b - c, l) * (g / l);
        cout << ans << "\n";
    }
    return 0;
}
