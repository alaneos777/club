#include <bits/stdc++.h>

using namespace std;

int main(){
	int a, b, c;
	cin >> a >> b >> c;
	vector<int> posibles(6);
	posibles[0] = a+b+c;
	posibles[1] = a+b*c;
	posibles[2] = a*b+c;
	posibles[3] = a*(b+c);
	posibles[4] = (a+b)*c;
	posibles[5] = a*b*c;
	sort(posibles.begin(), posibles.end());
	cout << posibles[5];
	return 0;
}