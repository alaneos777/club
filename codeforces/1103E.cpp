#include <bits/stdc++.h>
using namespace std;
using lli = uint64_t;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

struct num{
	lli a, b, c, d;
	num(lli a = 0, lli b = 0, lli c = 0, lli d = 0): a(a), b(b), c(c), d(d) {}
	num operator+(const num& n) const{
		return num(a + n.a, b + n.b, c + n.c, d + n.d);
	}
	num operator*(lli k) const{
		return num(a*k, b*k, c*k, d*k);
	}
	num operator*(const num& n) const{
		lli r = b*n.d + c*n.c + d*n.b;
		return num(a*n.a - (c*n.d + d*n.c) - r, a*n.b + b*n.a - d*n.d + r, a*n.c + b*n.b + c*n.a - r, a*n.d + b*n.c + c*n.b + d*n.a + r);
	}
	num operator^(lli n) const{
		num ans = 1, a = *this;
		while(n){
			if(n&1) ans = ans * a;
			n >>= 1;
			a = a * a;
		}
		return ans;
	}
	num operator>>(int n) const{
		return num(a>>n, b>>n, c>>n, d>>n);
	}
};

vector<num> w(10);

void fwt(vector<num>& A, int inv = 1){
	int n = A.size();
	vector<num> block(10);
	for(int sz = 10; sz <= n; sz *= 10){
		for(int start = 0; start < n; start += sz){
			for(int j = 0; j < sz/10; ++j){
				for(int k = 0; k < 10; ++k){
					block[k] = A[start+j+sz/10*k];
				}
				for(int k = 0; k < 10; ++k){
					num s = 0;
					for(int l = 0; l < 10; ++l){
						int idx = k*l%10;
						if(inv == -1 && idx != 0) idx = 10-idx;
						s = s + block[l]*w[idx];
					}
					A[start+j+sz/10*k] = s;
				}
			}
		}
	}
	if(inv == -1){
		lli five_rev = power(3125, (lli(1)<<63)-1);
		for(num& ni : A){
			ni = ni * five_rev;
			ni = ni>>5;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	w[0] = 1;
	for(int i = 1; i < 10; ++i){
		w[i] = w[i-1] * num(0, 1);
	}
	int n;
	cin >> n;
	vector<num> F(1e5);
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		F[ai] = F[ai]+1;
	}
	fwt(F);
	for(num& fi : F){
		fi = fi^n;
	}
	fwt(F, -1);
	for(int i = 0; i < n; ++i){
		lli xi = F[i].a & ((lli(1)<<58)-1);
		cout << xi << "\n";
	}
	return 0;
}