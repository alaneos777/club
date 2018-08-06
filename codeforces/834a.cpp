#include <iostream>
#include <map>

using namespace std;

int mod(int a, int b){
	int r = a % b;
	if(r < 0) r += b;
	return r;
}

int main(){
	map<char, int> info = {{'^', 0}, {'>', 1}, {'v', 2}, {'<', 3}};
	char inicio, fin;
	int start, end, time;
	cin >> inicio >> fin;
	start = info[inicio];
	end = info[fin];
	cin >> time;
	int cw = mod(start + time, 4);
	int ccw = mod(start - time, 4);
	if(cw == end && ccw == end){
		cout << "undefined";
	}else if(cw == end && ccw != end){
		cout << "cw";
	}else if(cw != end && ccw == end){
		cout << "ccw";
	}else{
		cout << "undefined";
	}
	return 0;
}