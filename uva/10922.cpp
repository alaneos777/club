#include <bits/stdc++.h>
using namespace std;

int sumDigits(int n){
	int ans = 0;
	while(n > 0){
		ans += n % 10;
		n /= 10;
	}
	return ans;
}

int sumDigits(string s){
	int ans = 0;
	for(int i = 0; i < s.size(); i++){
		ans += (s[i] - '0');
	}
	return ans;
}

int str_int(string s){
	stringstream ss(s);
	int ans;
	ss >> ans;
	return ans;
}

string int_str(int n){
	stringstream ss;
	ss << n;
	string ans;
	ss >> ans;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	string n;
	while(cin >> n && n != "0"){
		string n0 = n;
		int suma = 0, depth = 0;
		do{
			n = int_str(sumDigits(n));
			depth++;
		}while(str_int(n) > 9);
		if(str_int(n) == 9){
			cout << n0 << " is a multiple of 9 and has 9-degree " << depth << ".\n";
		}else{
			cout << n0 << " is not a multiple of 9.\n";
		}
	}
	return 0;
}