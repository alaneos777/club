#include <iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	if(b <= c || d <= a){
		cout << (b - a + d - c) << "\n";
	}else if(a <= c && d <= b){
		cout << (b - a) << "\n";
	}else if(c <= a && b <= d){
		cout << (d - c) << "\n";
	}else if(a <= c && b <= d){
		cout << (d - a) << "\n";
	}else if(c <= a && d <= b){
		cout << (b - c) << "\n";
	}
	return 0;
}