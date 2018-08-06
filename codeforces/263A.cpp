#include <bits/stdc++.h>

using namespace std;

int main(){
	bool encontrado = false;
	int p = 0, v, x, y;
	for(int i=0;i<25;i++){
		cin >> v;
		if(!encontrado) p++;
		if(v == 1) encontrado = true;
	}
	x = (p-1)/5 + 1;
	y = (p-1)%5 + 1;
	cout << (abs(x-3)+abs(y-3));
	return 0;
}