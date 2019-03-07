#include <iostream>
#include <map>
using namespace std;

int divs(int n){
	int ans = 0;
	for(int d = 1; d*d <= n; ++d){
	    if(n%d!=0) continue;
	    int e=n/d;
	    ans += d;
	    if(e != d) ans += e;
	}
	return ans;
}

map<int, __int128> nums = {
{1, 2ll},
{2, 24ll},
{3, 4320ll},
{4, 4680ll},
{5, 26208ll},
{6, 8910720ll},
{7, 17428320ll},
{8, 20427264ll},
{9, 91963648ll},
{10, 197064960ll},
{11, 8583644160ll},
{12, 10200236032ll},
{13, 21857648640ll},
{14, 57575890944ll},
{15, 57629644800ll},
{16, 206166804480ll},
{17, 17116004505600ll},
{18, 1416963251404800ll},
{19, 15338300494970880ll},
{20, 75462255348480000ll},
{21, 88898072401645056ll},
{22, 301183421949935616ll}
};

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

int main(){
	__int128 ans = 0;
	for(auto p : nums)
	    ans += p.second;
	cout << ans << "\n";
	return 0;
}