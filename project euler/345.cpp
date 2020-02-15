#include <bits/stdc++.h>
using namespace std;

//Given a m*n cost matrix (m<=n), it finds a maximum cost assignment.
//The actual assignment is in the vector returned.
//To find the minimum, negate the values.
template<typename T>
pair<T, vector<int>> hungarian(const vector<vector<T>> & a){
	int m = a.size(), n = a[0].size();
	assert(m <= n);
	vector<int> x(m, -1), y(n, -1);
	vector<T> px(m, numeric_limits<T>::min()), py(n, 0);
	for(int u = 0; u < m; ++u)
		for(int v = 0; v < n; ++v)
			px[u] = max(px[u], a[u][v]);
	for(int u = 0, p, q; u < m; ){
		vector<int> s(m + 1, u), t(n, -1);
		for(p = q = 0; p <= q && x[u] < 0; ++p){
			for(int k = s[p], v = 0; v < n && x[u] < 0; ++v){
				if(px[k] + py[v] == a[k][v] && t[v] < 0){
					s[++q] = y[v], t[v] = k;
					if(s[q] < 0)
						for(p = v; p >= 0; v = p)
							y[v] = k = t[v], p = x[k], x[k] = v;
				}
			}
		}
		if(x[u] < 0){
			T delta = numeric_limits<T>::max();
			for(int i = 0; i <= q; ++i)
				for(int v = 0; v < n; ++v)
					if(t[v] < 0)
						delta = min(delta, px[s[i]] + py[v] - a[s[i]][v]);
			for(int i = 0; i <= q; ++i)
				px[s[i]] -= delta;
			for(int v = 0; v < n; ++v)
				py[v] += (t[v] < 0 ? 0 : delta);
		}else{
			++u;
		}
	}
	T cost = 0;
	for(int u = 0; u < m; ++u)
		cost += a[u][x[u]];
	return {cost, x};
}

int main(){
	vector<vector<int>> A = {{7, 53, 183, 439, 863, 497, 383, 563, 79, 973, 287, 63, 343, 169, 583},
	{627, 343, 773, 959, 943, 767, 473, 103, 699, 303, 957, 703, 583, 639, 913},
	{447, 283, 463, 29, 23, 487, 463, 993, 119, 883, 327, 493, 423, 159, 743},
	{217, 623, 3, 399, 853, 407, 103, 983, 89, 463, 290, 516, 212, 462, 350},
	{960, 376, 682, 962, 300, 780, 486, 502, 912, 800, 250, 346, 172, 812, 350},
	{870, 456, 192, 162, 593, 473, 915, 45, 989, 873, 823, 965, 425, 329, 803},
	{973, 965, 905, 919, 133, 673, 665, 235, 509, 613, 673, 815, 165, 992, 326},
	{322, 148, 972, 962, 286, 255, 941, 541, 265, 323, 925, 281, 601, 95, 973},
	{445, 721, 11, 525, 473, 65, 511, 164, 138, 672, 18, 428, 154, 448, 848},
	{414, 456, 310, 312, 798, 104, 566, 520, 302, 248, 694, 976, 430, 392, 198},
	{184, 829, 373, 181, 631, 101, 969, 613, 840, 740, 778, 458, 284, 760, 390},
	{821, 461, 843, 513, 17, 901, 711, 993, 293, 157, 274, 94, 192, 156, 574},
	{34, 124, 4, 878, 450, 476, 712, 914, 838, 669, 875, 299, 823, 329, 699},
	{815, 559, 813, 459, 522, 788, 168, 586, 966, 232, 308, 833, 251, 631, 107},
	{813, 883, 451, 509, 615, 77, 281, 613, 459, 205, 380, 274, 302, 35, 805}};
	cout << hungarian<int>(A).first << "\n";
	return 0;
}