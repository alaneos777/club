#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld pi = acosl(-1);
using comp = complex<ld>;

int main(){
	clock_t start = clock();
	int times = 2020;
	comp z = 1;
	ld sum = 0;
	int n = 1;
	while(true){
		ld len = z.real()*z.real() + z.imag()*z.imag();
		ld root = sqrt(4/len - 1);
		sum += acos(0.5l * (z.real() + root*z.imag()));
		z = (0.5l * n*len * comp(1.0l, root) + 1.0l) / ld(n+1);
		n++;
		if(sum >= 2*pi*times) break;
	}
	cout << n << "\n";
	cout << fixed << setprecision(3) << ld(clock() - start) / CLOCKS_PER_SEC << "\n";
	return 0;
}