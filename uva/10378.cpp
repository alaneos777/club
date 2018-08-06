#include <bits/stdc++.h>
using namespace std;

int str2int(string str){
	stringstream ss;
	ss << str;
	int n;
	ss >> n;
	return n;
}

bool comp(const complex<double> & a, const complex<double> & b){
	if(abs(a.real() - b.real()) > 1e-6)
		return a.real() > b.real();
	if(abs(a.imag() - b.imag()) < 1e-6)
		return false;
	return a.imag() > b.imag();
}

int main(){
	ios_base::sync_with_stdio(0);
	string numero;
	int n, a, b, i = 1;
	complex<double> z;
	while(cin >> numero >> n){
		int pos = numero.find("+", 1);
		if(pos == string::npos){
			pos = numero.find("-", 1);
		}
		a = str2int(numero.substr(0, pos));
		b = str2int(numero.substr(pos, numero.find("i") - pos));
		z = complex<double>(a, b);
		double r = pow(abs(z), 1.0 / n);
		double theta = arg(z) / n;
		vector< complex<double> > raices(n);
		for(int k = 0; k < n; ++k){
			raices[k] = polar(r, theta + 2.0 * M_PI * k / n);
		}
		sort(raices.begin(), raices.end(), comp);
		cout << "Case " << i << ":\n";
		for(int k = 0; k < n; ++k){
			if(abs(raices[k].real()) < 0.0005) raices[k].real(0);
			if(abs(raices[k].imag()) < 0.0005) raices[k].imag(0);
			cout << fixed << setprecision(3) << raices[k].real();
			if(raices[k].imag() >= 0) cout << "+";
			cout << fixed << setprecision(3) << raices[k].imag() << "i\n";
		}
		cout << "\n";
		++i;
	}
	return 0;
}