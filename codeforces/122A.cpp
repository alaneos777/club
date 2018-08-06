#include <bits/stdc++.h>

using namespace std;

bool lucky(int n){
	int d;
	do{
		d = n%10;
		if(!(d == 4 || d == 7)) return false;
		n /= 10;
	}while(n != 0);
	return true;
}

int main(){
	int n;
	cin >> n;
	string test = "NO";
	for(int d=1;d<=sqrt(n);d++){
		if(n%d == 0){
			if(lucky(d) || lucky(n/d)){
				test = "YES";
				break;
			}
		}
	}
	cout << test;
	return 0;
}