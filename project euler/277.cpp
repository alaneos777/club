#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

string seq(lli n, int cnt){
	string ans = "";
	while(n != 1){
		lli r = n % 3;
		if(r == 0){
			n = n / 3;
			ans += "D";
		}else if(r == 1){
			n = (4*n + 2) / 3;
			ans += "U";
		}else{
			n = (2*n - 1) / 3;
			ans += "d";
		}
		if(ans.size() == cnt){
			return ans;
		}
	}
	return ans;
}

lli rev(lli end, const string & cad){
	for(int i = (int)cad.size()-1; i >= 0; --i){
		const char c = cad[i];
		if(c == 'd'){
			if((3*end + 1) % 2 != 0) return -1;
			end = (3*end + 1) / 2;
		}else if(c == 'U'){
			if((3*end - 2) % 4 != 0) return -1;
			end = (3*end - 2) / 4;
		}else{
			end = 3*end;
		}
	}
	return end;
}

int main(){
	string start = "UDDDUdddDDUDDddDdDddDDUDDdUUDd";
	lli n = 1;
	while(1){
		lli a1 = rev(n, start);
		if(a1 > 1e15){
			cout << a1 << "\n";
			break;
		}
		n++;
	}
	return 0;
}