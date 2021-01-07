#include <bits/stdc++.h>
using namespace std;
using comp = complex<double>;
const double pi = acos(-1);

int main(){
	string ins;
	comp pos;
	comp dir(1, 0);
	while(getline(cin, ins)){
		char c = ins[0];
		int n = stoi(ins.substr(1));
		if(c == 'N'){
			pos += comp(0, n);
		}else if(c == 'S'){
			pos += comp(0, -n);
		}else if(c == 'E'){
			pos += comp(n, 0);
		}else if(c == 'W'){
			pos += comp(-n, 0);
		}else if(c == 'L'){
			dir *= polar(1.0, n * pi / 180);
		}else if(c == 'R'){
			dir *= polar(1.0, -n * pi / 180);
		}else if(c == 'F'){
			pos += dir * comp(n, 0);
		}
	}
	cout << abs(real(pos))+abs(imag(pos)) << endl;
	return 0;
}