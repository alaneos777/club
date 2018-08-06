#include <iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	int n;
	bool print = true;
	while(cin >> n){
		if(n == 42){
			print = false;
		}
		if(print){
			cout << n << "\n";
		}
	}
	return 0;
}