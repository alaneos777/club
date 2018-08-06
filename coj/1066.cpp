#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    double PI = 3.141592653589793;
    int t;
    double r, n;
    cin >> t;
    for(int i=0;i<t;i++){
        cin >> r >> n;
        double p1 = 2.0*r*n*sin(PI/n);
        double p2 = 2.0*r*n*tan(PI/n);
        cout << fixed << setprecision(4) << p1;
        cout << " ";
        cout << fixed << setprecision(4) << p2;
        cout << "\n";
    }
    return 0;
}
