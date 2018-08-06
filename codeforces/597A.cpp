#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

ull piso(ull a, ull b){
    if((a>=0 && b>0) || (a<0 && b<0)){
        return a/b;
    }else{
        if(a%b==0) return a/b;
        else return a/b-1;
    }
}

int main(){
	ull k, a, b;
	cin >> k >> a >> b;
	cout << piso(b, k) - piso(a-1, k);
	return 0;
}