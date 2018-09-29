#include <bits/stdc++.h>
using namespace std;
double eps = 1e-7;

struct person{
	double run, cyc;
	double time(double r, double k){
		return r / run + k / cyc;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	double t;
	while(cin >> t){
		cin >> n;
		vector<person> persons(n);
		for(int i = 0; i < n; ++i){
			cin >> persons[i].run >> persons[i].cyc;
		}
		auto can = [&](double r){
			double k = t - r;
			double time = persons[n-1].time(r, k);
			double mini = 1e9;
			for(int i = 0; i < n-1; ++i){
				mini = min(mini, persons[i].time(r, k));
			}
			return mini - time;
		};
		double left = 0, right = t, r, ans;
		while(true){
			if(abs(right - left) < eps){
				r = (left + right) / 2;
				break;
			}
			double leftThird = left + (right - left) / 3.0;
			double rightThird = right - (right - left) / 3.0;
			if(can(leftThird) < can(rightThird)) left = leftThird;
			else right = rightThird;
		}
		ans = can(r);
		if(ans >= -eps){
			cout << "The cheater can win by " << (int)round(ans*3600) << " seconds with r = " << fixed << setprecision(2) << r << "km and k = " << (t-r) << "km.\n";
		}else{
			cout << "The cheater cannot win.\n";
		}
	}
	return 0;
}