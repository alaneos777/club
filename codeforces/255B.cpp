#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	string s;
	size_t pos;
	bool op = true;
	cin >> s;
	while(op){
		op = false;
		pos = s.find("yx");
		if(pos != string::npos){
			s.replace(pos, 2, "xy");
			op = true;
		}else{
			pos = s.find("xy");
			if(pos != string::npos){
				s.erase(pos, 2);
				op = true;
			}
		}
	}
	cout << s;
	return 0;
}