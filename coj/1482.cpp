#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int a, b, c;
	while(cin >> a >> b >> c){
		if(a+b>=c && a+c>=b && b+c>=a){
			double s = 0.5 * (a + b + c);
			double area = sqrt(s * (s - a) * (s - b) * (s - c));
			double r = area / s;
			double R = 0;
			if(a+b==c || a+c==b || b+c==a){
				R = 0.5 * max({a, b, c});
			}else{
				R = ((double)a * b * c) / (4 * area);
			}
			cout << fixed << setprecision(2) << r << " " << R << "\n";
		}else{
			cout << "ERROR\n";
		}
	}
	return 0;
}