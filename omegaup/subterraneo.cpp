#include <iostream>
#include <stack>

typedef long long int ull;
using namespace std;

int main(){
	ull p, r;
	stack<string> ans;
	cin >> p;
	do{
		r = p % 60;
		p /= 60;
		ans.push(string(r / 10, 'L') + string(r % 10, 'I'));
	}while(p != 0);
	while(!ans.empty()){
		cout << ans.top();
		ans.pop();
		if(ans.size() > 0){
			cout << ".";
		}
	}
	return 0;
}