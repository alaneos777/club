#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	int a, b;
	while(true){
		cin >> a >> b;
		if(a == 0 && b == 0) break;
		int carry = 0, count = 0;
		while(!(a == 0 && b == 0)){
			carry = (carry + (a % 10) + (b % 10)) / 10;
			a /= 10;
			b /= 10;
			if(carry > 0) count++;
		}
		if(count == 0){
			cout << "No carry operation.\n";
		}else if(count == 1){
			cout << "1 carry operation.\n";
		}else{
			cout << count << " carry operations.\n";
		}
	}
	return 0;
}