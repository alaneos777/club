#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
using ld = long double;
using vec = vector<ld>;

vec mult(const vec & a, const vec & b){
	vec c(a.size()+b.size()-1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i+j] += a[i]*b[j];
		}
	}
	return c;
}

int main(){
	vec P = {1};
	vec C = {1};
	for(int i = 1; i <= 9; ++i){
		P = mult(P, {0,1,1,1,1});
	}
	for(int i = 1; i <= 6; ++i){
		C = mult(C, {0,1,1,1,1,1,1});
	}
	ld sumP = 0, sumC = 0;
	for(int i = 1; i <= 36; ++i){
		sumP += P[i];
	}
	for(int i = 1; i <= 36; ++i){
		sumC += C[i];
	}
	for(int i = 1; i <= 36; ++i){
		P[i] /= sumP;
	}
	for(int i = 1; i <= 36; ++i){
		C[i] /= sumC;
	}
	ld Pwin = 0, Cwin = 0, draw = 0;
	for(int i = 1; i <= 36; ++i){
		for(int j = 1; j <= 36; ++j){
			if(i > j) Pwin += P[i]*C[j];
			else if(i < j) Cwin += P[i]*C[j];
			else draw += P[i]*C[j];
		}
	}
	cout << fixed << setprecision(7) << Pwin << " " << Cwin << " " << draw << " " << Pwin+Cwin+draw << "\n";
	return 0;
}