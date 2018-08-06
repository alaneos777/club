#include <bits/stdc++.h>

using namespace std;

typedef long long int ull;

vector<ull> euclides_rec(ull a, ull b, ull x0, ull y0, ull x1, ull y1){
    if(b==0) return {a, x0, y0};
    ull q=a/b, r=a%b;
    return euclides_rec(b, r, x1, y1, x0-x1*q, y0-y1*q);
}

int main()
{
    ios_base::sync_with_stdio(0);
    ull a, b;
    while(cin >> a && cin >> b){
        vector<ull> info = euclides_rec(a, b, 1, 0, 0, 1);
        cout << info[1] << " " << info[2] << " " << info[0] << "\n";
    }
    return 0;
}
