#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, m, a, b;
	cin >> n >> m >> a >> b;
	if((b-a*m)>=0){
		cout << (a*n);
	}else{
		int lower = floor((double)n/(double)m);
		int upper = ceil((double)n/(double)m);
		cout << min((b-a*m)*lower+a*n,b*upper);
	}
	return 0;
}