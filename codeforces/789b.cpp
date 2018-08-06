#include <bits/stdc++.h>
using namespace std;

bool isInteger(double x){
	return abs(x - floor(x)) < 1e-7;
}

int main(){
	int b1, q, l, m;
	cin >> b1 >> q >> l >> m;
	vector<int> a(m);
	bool cero = false, b1_p = false, b1_n = false;
	for(int i = 0; i < m; i++){
		cin >> a[i];
		if(a[i] == 0) cero = true;
		if(a[i] == b1) b1_p = true;
		if(a[i] == -b1) b1_n = false;
	}
	if(q == 0){
		if(b1 == 0){
			if(cero){
				cout << "0";
			}else{
				cout << "inf";
			}
		}else{
			if(b1_p && cero){
				cout << "0";
			}else if(cero){
				if(abs(b1) <= l)
					cout << "1";
				else
					cout << "0";
			}else{
				cout << "inf";
			}
		}
	}else if(q == 1){
		if(abs(b1) <= l){
			if(b1 == 0 && cero)
				cout << "0";
			else
				if(b1_p)
					cout << "0";
				else
					cout << "inf";
		}else{
			cout << "0";
		}
	}else if(q == -1){
		if(abs(b1) <= l){
			if(b1 == 0 && cero)
				cout << "0";
			else
				if(!b1_p || !b1_n)
					cout << "inf";
				else
					cout << "0";
		}else{
			cout << "0";
		}
	}else{
		if(b1 == 0){
			if(cero)
				cout << "0";
			else
				cout << "inf";
		}else{
			int n = floor(1 + log(abs((double)l/(double)b1)) / log(abs(q)));
			for(int i = 0; i < m; i++){
				if(a[i] != 0 && abs(a[i]) <= l){
					if(a[i] % b1 == 0){
						int div = a[i] / b1;
						if(q > 0){
							if(div > 0){
								double tmp = 1 + log((double)a[i]/(double)b1)/log((double)q);
								if(isInteger(tmp)) n--;
							}
						}else{
							if(div > 0){
								double tmp = 1 + log((double)a[i]/(double)b1)/log((double)q);
                                if(isInteger(tmp) && ((int)round(tmp)) % 2 == 0) n--;
							}else{
								double tmp = 1 + log((double)a[i]/(double)b1)/log((double)q);
                                if(isInteger(tmp) && ((int)round(tmp)) % 2 == 1) n--;
							}
						}
					}
				}
			}
			if(n < 0) n == 0;
			cout << n;
		}
	}
	return 0;
}
