#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> operator*(const vector<int>& a, const vector<int>& b){
	vector<int> c(a.size()+b.size()-1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i+j] += a[i]*b[j];
		}
	}
	return c;
}

vector<int> operator+(const vector<int>& a, const vector<int>& b){
	vector<int> c(max(a.size(), b.size()));
	for(int i = 0; i < c.size(); ++i){
		if(i < a.size()) c[i] = a[i];
		if(i < b.size()) c[i] += b[i];
	}
	return c;
}

vector<int> operator/(vector<int> a, int x){
	for(int& ai : a){
		ai /= x;
	}
	return a;
}

vector<int> shift(const vector<int>& a, int x){
	vector<int> b(x*(a.size()-1)+1);
	for(int i = 0; i < a.size(); ++i){
		b[x*i] = a[i];
	}
	return b;
}

int main(){
	vector<int> F(61);
	F[0]++;
	for(int i = 1; i <= 20; ++i){
		F[i]++;
		F[2*i]++;
		F[3*i]++;
	}
	F[25]++;
	F[50]++;
	F = (F*F + shift(F,2)) / 2;
	int N = 99;
	F.resize(N+1);
	lli ans = 0;
	for(int s = 1; s <= N; ++s){
		for(int t = 1; t <= 20 && 2*t <= s; ++t){
			ans += F[s - 2*t];
		}
		if(s >= 50) ans += F[s - 50];
	}
	cout << ans << "\n";
	return 0;
}