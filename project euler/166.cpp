#include <bits/stdc++.h>
using namespace std;

inline bool is(int n){
	return 0 <= n && n <= 9;
}

int main(){
	int cnt = 0;
	for(int x = 0; x <= 36; ++x){
		for(int i = 0; i <= 9; ++i){
			for(int a = 0; a <= 9; ++a){
				for(int e = 0; e <= 9; ++e){
					int m = x - a - e - i;
					if(!is(m)) continue;
					for(int f = 0; f <= 9; ++f){
						for(int g = 0; g <= 9; ++g){
							int l = f + g - i;
							if(!is(l)) continue;
							int h = x - e - f - g;
							if(!is(h)) continue;
							for(int b = 0; b <= 9; ++b){
								for(int c = 0; c <= 9; ++c){
									int d = x - a - b - c;
									if(!is(d)) continue;
									int j = -x + 2*a + b + c + e - g + i;
									if(!is(j)) continue;
									int k = 2*x - 2*a - b - c - e - f - i;
									if(!is(k)) continue;
									int n = 2*x - 2*a - 2*b - c - e - f + g - i;
									if(!is(n)) continue;
									int o = -x + 2*a + b + e + f - g + i;
									if(!is(o)) continue;
									int p = -x + a + b + c + e + i;
									if(!is(p)) continue;
									cnt++;
								}
							}
						}
					}
				}
			}
		}
	}
	cout << cnt << "\n";
	return 0;
}