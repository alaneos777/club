#include <bits/stdc++.h>
using namespace std;
typedef double ld;

void multByOne(ld *polynomial, ld *original, int degree){
	ld first = polynomial[degree - 1];
	for(int i = degree - 1; i >= 0; --i){
		polynomial[i] = first * original[i];
		if(i > 0){
			polynomial[i] += polynomial[i - 1];
		}
	}
}

ld *mult(ld *P, ld *Q, ld **residues, int degree){
	ld *R = new ld[degree]();
	ld *S = new ld[degree - 1]();
	for(int i = 0; i < degree; i++){
		for(int j = 0; j < degree; j++){
			if(i + j < degree){
				R[i + j] += P[i] * Q[j];
			}else{
				S[i + j - degree] += P[i] * Q[j];
			}
		}
	}
	for(int i = 0; i < degree - 1; i++){
		for(int j = 0; j < degree; j++){
			R[j] += S[i] * residues[i][j];
		}
	}
	return R;
}

ld solveRecurrence(ld *charPoly, int degree, int n){
	ld **residues = new ld*[degree - 1];
	ld *current = new ld[degree];
	copy(charPoly, charPoly + degree, current);
	for(int i = 0; i < degree - 1; i++){
		residues[i] = new ld[degree];
		copy(current, current + degree, residues[i]);
		if(i != degree - 2) multByOne(current, charPoly, degree);
	}
	ld *tmp = new ld[degree]();
	ld *ans = new ld[degree]();
	ans[0] = 1;
	if(degree > 1){
		tmp[1] = 1;
	}else{
		tmp[0] = charPoly[0];
	}
	while(n){
		if(n & 1) ans = mult(ans, tmp, residues, degree);
		n >>= 1;
		if(n) tmp = mult(tmp, tmp, residues, degree);
	}
	return ans[degree - 1];
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int c, n;
		cin >> c >> n;
		if(c == 1){
			cout << n << "\n";
			continue;
		}
		int L = min(60, n);
		ld ans = 0;
		ld p = c;
		ld q = (p - 1) / p;
		for(int m = 1; m <= L; ++m){
			ld *charPoly = new ld[m];
			for(int i = 0; i < m; ++i){
				charPoly[i] = (p - 1) * pow((ld)1.0 / p, (ld)(m - i));
			}
			ld res = solveRecurrence(charPoly, m, n + m - 1);
			if(m == L) ans += L * res;
			else ans -= res;
		}
		ans /= q;
		cout << fixed << setprecision(10) << ans << "\n";
	}
	return 0;
}