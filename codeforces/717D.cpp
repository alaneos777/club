#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
using ld = long double;

void fwt(vector<ld> & A, int op, int inv){
	int n = A.size();
	for(int k = 1; k < n; k <<= 1)
		for(int i = 0; i < n; i += k << 1)
			for(int j = 0; j < k; ++j){
				ld u = A[i + j], v = A[i + j + k];
				ld sum = u + v;
				ld rest = u - v;
				if(inv == -1){
					if(op == 0)
						A[i + j + k] = -rest;
					else if(op == 1)
						A[i + j] = rest;
					else if(op == 2)
						A[i + j] = sum, A[i + j + k] = rest;
				}else{
					if(op == 0)
						A[i + j + k] = sum;
					else if(op == 1)
						A[i + j] = sum;
					else if(op == 2)
						A[i + j] = sum, A[i + j + k] = rest;
				}
			}
	if(inv == -1 && op == 2){
		for(int i = 0; i < n; ++i)
			A[i] = A[i] / n;
	}
}

int near(int x){
	int a = 1;
	while(a < x) a <<= 1;
	return a;
}

vector<ld> mul(vector<ld> a, vector<ld> b){
	fwt(a, 2, 1), fwt(b, 2, 1);
	for(int i = 0; i < a.size(); ++i){
		a[i] *= b[i];
	}
	fwt(a, 2, -1);
	return a;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, x;
	cin >> n >> x;
	vector<ld> a(x+1), ans(x+1);
	for(ld & ai : a) cin >> ai;
	a.resize(near(a.size())), ans.resize(near(ans.size()));
	ans[0] = 1;
	while(n){
		if(n&1) ans = mul(ans, a);
		n >>= 1;
		a = mul(a, a);
	}
	cout << fixed << setprecision(10) << 1-ans[0] << "\n";
	return 0;
}