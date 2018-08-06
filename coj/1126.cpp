#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    double PI = 3.141592653589793;
    double x1, y1, x2, y2, x3, y3;
    while(cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3){
        double a = hypot(x3-x2, y3-y2);
        double b = hypot(x3-x1, y3-y1);
        double c = hypot(x2-x1, y2-y1);
        double area = abs(x1*y2+x2*y3+x3*y1-x2*y1-x3*y2-x1*y3)/2.0;
        double r = (a*b*c)/(4.0*area);
        double perimetro = 2.0*PI*r;
        cout << fixed << setprecision(2) << perimetro << "\n";
    }
    return 0;
}
