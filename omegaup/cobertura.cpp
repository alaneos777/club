#include <iostream>
using namespace std;

void solve(int r0, int r1, int c0, int c1, int x, int y){
	if(r1 - r0 == 1 && c1 - c0 == 1){
		//base case
		if(!(r0 == x && c0 == y)){
			cout << r0 << " " << c0 << " ";
		}
		if(!(r0 == x && c1 == y)){
			cout << r0 << " " << c1 << " ";
		}
		if(!(r1 == x && c0 == y)){
			cout << r1 << " " << c0 << " ";
		}
		if(!(r1 == x && c1 == y)){
			cout << r1 << " " << c1 << " ";
		}
		cout << "\n";
	}else{
		//inductive case
		int mid_r = (r0 + r1) / 2;
		int mid_c = (c0 + c1) / 2;
		if(r0 <= x && x <= mid_r && c0 <= y && y <= mid_c){
			//first quadrant
			cout << mid_r << " " << mid_c + 1 << " ";
			cout << mid_r + 1 << " " << mid_c << " ";
			cout << mid_r + 1 << " " << mid_c + 1 << "\n";
			solve(r0, mid_r, c0, mid_c, x, y);
			solve(r0, mid_r, mid_c + 1, c1, mid_r, mid_c + 1);
			solve(mid_r + 1, r1, c0, mid_c, mid_r + 1, mid_c);
			solve(mid_r + 1, r1, mid_c + 1, c1, mid_r + 1, mid_c + 1);
		}else if(r0 <= x && x <= mid_r && mid_c + 1 <= y && y <= c1){
			//second quadrant
			cout << mid_r << " " << mid_c << " ";
			cout << mid_r + 1 << " " << mid_c << " ";
			cout << mid_r + 1 << " " << mid_c + 1 << "\n";
			solve(r0, mid_r, c0, mid_c, mid_r, mid_c);
			solve(r0, mid_r, mid_c + 1, c1, x, y);
			solve(mid_r + 1, r1, c0, mid_c, mid_r + 1, mid_c);
			solve(mid_r + 1, r1, mid_c + 1, c1, mid_r + 1, mid_c + 1);
		}else if(mid_r + 1 <= x && x <= r1 && c0 <= y && y <= mid_c){
			//third quadrant
			cout << mid_r << " " << mid_c << " ";
			cout << mid_r << " " << mid_c + 1 << " ";
			cout << mid_r + 1 << " " << mid_c + 1 << "\n";
			solve(r0, mid_r, c0, mid_c, mid_r, mid_c);
			solve(r0, mid_r, mid_c + 1, c1, mid_r, mid_c + 1);
			solve(mid_r + 1, r1, c0, mid_c, x, y);
			solve(mid_r + 1, r1, mid_c + 1, c1, mid_r + 1, mid_c + 1);
		}else if(mid_r + 1 <= x && x <= r1 && mid_c + 1 <= y && y <= c1){
			//fourth quadrant
			cout << mid_r << " " << mid_c << " ";
			cout << mid_r << " " << mid_c + 1 << " ";
			cout << mid_r + 1 << " " << mid_c << "\n";
			solve(r0, mid_r, c0, mid_c, mid_r, mid_c);
			solve(r0, mid_r, mid_c + 1, c1, mid_r, mid_c + 1);
			solve(mid_r + 1, r1, c0, mid_c, mid_r + 1, mid_c);
			solve(mid_r + 1, r1, mid_c + 1, c1, x, y);
		}
	}
}

int main(){
	int n, x, y;
	cin >> n >> x >> y;
	solve(1, 1 << n, 1, 1 << n, x, y);
	return 0;
}