#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

vector<double> lengths;
int n, k;

int sum(double value){
	int ans = 0;
	for(int i = 0; i < lengths.size(); i++){
		ans += int(lengths[i] / value);
	}
	return ans;
}

double ans(int x, double m){
	double left = 0.0, right = m, mid;
	while((right - left) > 1e-5){
		mid = (left + right) / 2;
		double s = sum(mid);
		if(sum(mid) < x){
			right = mid;
		}else{
			left = mid;
		}
	}
	return right;
}

int main(){
	scanf("%d %d", &n, &k);
	lengths.resize(n);
	double m = 0;
	for(int i = 0; i < n; i++){
		scanf("%lf", &lengths[i]);
		m = max(m, lengths[i]);
	}
	printf("%.2f\n", 0.01 * int(ans(k, m) * 100));
	return 0;
}