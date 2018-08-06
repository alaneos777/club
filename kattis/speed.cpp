#include <bits/stdc++.h>

using namespace std;

double epsilon = 1e-10;

bool esIgual(double x, double y){
	return abs(x - y) < epsilon;
}

double suma(double c, int n, vector<double> & d, vector<double> & s){
	double ans = 0;
	for(int i = 0; i < n; i++){
		ans += d[i] / (s[i] + c);
	}
	return ans;
}

double answer(double lower, double upper, int n, double t, vector<double> & d, vector<double> & s){
	double mitad, sum;
	while(!esIgual(lower, upper)){
		mitad = (lower + upper) / 2.0;
		sum = suma(mitad, n, d, s);
		if(esIgual(sum, t)){
			break;
		}else if(sum > t){
			lower = mitad;
		}else{
			upper = mitad;
		}
	}
	return mitad;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, t;
	double lower = -1001, upper = 0;
	cin >> n >> t;
	vector<double> d(n);
	vector<double> s(n);
	for(int i = 0; i < n; i++){
		cin >> d[i] >> s[i];
		lower = max(lower, -s[i]);
		upper = max(upper, d[i]);
	}
	upper = (double)n * upper / (double)t + lower + 10;
	cout << fixed << setprecision(9) << answer(lower + epsilon, upper, n, (double)t, d, s);
	return 0;
}