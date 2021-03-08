#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e7 + 19;

lli solveRecurrence(const vector<lli> & P, const vector<lli> & init, lli n){
	int deg = P.size();
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				(R[i + j + d] += ans[i] * ans[j]) %= mod;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				(R[i + j] += R[i + deg] * P[j]) %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		(nValue += ans[i] * init[i]) %= mod;
	return nValue;
}

lli solveProblem(int k, const vector<lli> & numbers, lli n){
	int degree = *max_element(numbers.begin(), numbers.end());
	vector<lli> charPoly(degree), initial(degree);
	for(int i = 0; i < k; i++){
		charPoly[degree - numbers[i]] = 1;
	}

	initial[0] = 1;
	for(int i = 1; i < degree; i++){
		for(int j = 0; j < k; j++){
			int pos = i - numbers[j];
			if(pos >= 0){
				initial[i] += initial[pos];
				if(initial[i] >= mod) initial[i] -= mod;
			}
		}
	}

	return solveRecurrence(charPoly, initial, n);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int k; //2 <= k <= 600
	cin >> k;
	vector<lli> numbers(k);
	for(int i = 0; i < k; i++){
		cin >> numbers[i]; //1 <= numbers[i] <= 600
	}
	lli n;
	cin >> n;
	cout << solveProblem(k, numbers, n) << "\n";
	return 0;
}