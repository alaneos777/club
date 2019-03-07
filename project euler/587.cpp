#include <iostream>
#include <cmath>
using namespace std;
const double PI = acos(-1);

int main(){
	double A = (4 - PI) / 16;
	for(int n = 2000; n <= 3000; ++n){
		double y = (n+1-sqrt(2*n))/(2*n*n+2);
		double r = (1-acos(1-2*y)-2*y*(n-1)) / (8*A);
		cout << n << " " << r*100 << "\n";
	}
	return 0;
}