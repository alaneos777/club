#include <bits/stdc++.h>
using namespace std;

int main(){
	srand(time(0));
	ofstream out("in.txt");
	out << 1000 << "\n";
	for(int i = 0; i < 1000; ++i){
		int x = ((rand()<<15) | rand()) % int(2e9) - int(1e9);
		int y = ((rand()<<15) | rand()) % int(2e9) - int(1e9);
		int w = rand() % 200 + 1;
		int h = rand() % 200 + 1;
		out << x << " " << y << " " << w << " " << h << "\n";
	}
	return 0;
}