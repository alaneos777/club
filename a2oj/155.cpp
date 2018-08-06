#include <iostream>

typedef unsigned long long int ull;

ull fast_pow_mod(ull b, ull e, ull m){
    ull ans = 1;
    while(e > 0){
        if(e%2 == 1){
            ans = (ans * b) % m;
        }
        e = e >> 1;
        b = (b * b) % m;
    }
    return ans;
}

using namespace std;
int main(){
	int t;
	ull n;
	cin >> t;
	for(int i=0;i<t;i++){
		cin >> n;
		cout << (fast_pow_mod(2, (n+1) % 1800, 33554431) - 1) << "\n";
	}
	return 0;
}