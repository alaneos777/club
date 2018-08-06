#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 1e9 + 7;

void multByOne(lli *polynomial, lli *original, int degree){
	lli first = polynomial[degree - 1];
	for(int i = degree - 1; i >= 0; --i){
		polynomial[i] = first * original[i];
		if(i > 0){
			polynomial[i] += polynomial[i - 1];
		}
	}
	for(int i = 0; i < degree; ++i){
		polynomial[i] %= mod;
	}
}

lli *mult(lli *P, lli *Q, lli **residues, int degree){
	lli *R = new lli[degree]();
	lli *S = new lli[degree - 1]();
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
		S[i] %= mod;
	}
	for(int i = 0; i < degree - 1; i++){
		for(int j = 0; j < degree; j++){
			R[j] += S[i] * residues[i][j];
		}
	}
	for(int i = 0; i < degree; i++){
		R[i] %= mod;
	}
	return R;
}

lli solveRecurrence(lli *charPoly, lli *initValues, lli **residues, int degree, lli n){
	lli *tmp = new lli[degree]();
	lli *ans = new lli[degree]();
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
	lli nValue = 0;
	for(int i = 0; i < degree; i++){
		nValue += ans[i] * initValues[i];
	}
	return nValue % mod;
}

lli solveProblem(int k, lli *numbers, lli n){
	int degree = *max_element(numbers, numbers + k);
	lli *charPoly = new lli[degree]();
	for(int i = 0; i < k; i++){
		charPoly[degree - numbers[i]] = 1;
	}

	lli **residues = new lli*[degree - 1];
	lli *current = new lli[degree];
	copy(charPoly, charPoly + degree, current);
	for(int i = 0; i < degree - 1; i++){
		residues[i] = new lli[degree];
		copy(current, current + degree, residues[i]);
		if(i != degree - 2) multByOne(current, charPoly, degree);
	}

	lli *initial = new lli[degree]();
	initial[0] = 1;
	for(int i = 1; i < degree; i++){
		for(int j = 0; j < k; j++){
			int pos = i - numbers[j];
			if(pos >= 0){
				initial[i] += initial[pos];
			}
		}
		initial[i] %= mod;
	}

	return solveRecurrence(charPoly, initial, residues, degree, n);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n;
		cin >> n;
		int k; //2 <= k <= 600
		cin >> k;
		lli *numbers = new lli[k];
		for(int i = 0; i < k; i++){
			cin >> numbers[i]; //1 <= numbers[i] <= 600
		}
		cout << solveProblem(k, numbers, n) << "\n";
	}
	return 0;
}