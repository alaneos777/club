#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef complex<ld> comp;

bool igual(ld a, ld b){
	return abs(a - b) < 1e-9;
}

vector<comp> ec_1(comp a, comp b){ //ax+b=0
	return {-b / a};
}

vector<comp> ec_2(comp a, comp b, comp c){ //ax^2+bx+c=0
	comp D = b * b - 4.0L * a * c;
	D = polar(sqrt(abs(D)), arg(D)/2);
	vector<comp> raices = {(-b + D)/(2.0L * a), (-b - D)/(2.0L * a)};
	return raices;
}

vector<comp> ec_3(comp a, comp b, comp c, comp d){ //ax^3+bx^2+cx+d=0
	//ecuación auxiliar: hacemos x=y-b/3a, y^3+Py+Q=0
	comp P = (3.0L * a * c - b * b)/(3.0L * a * a);
	comp Q = (2.0L * b * b * b - 9.0L * a * b * c + 27.0L * a * a * d)/(27.0L * a * a * a);
	//cuadrática auxiliar: z^2+Qz-(P/3)^3=0
	vector<comp> aux = ec_2(1.0L, Q, -pow(P / 3.0L, 3));
	//u=cbrt(z1), v=cbrt(z2)
	for(size_t i = 0; i < 2; i++) aux[i] = polar(cbrt(abs(aux[i])), arg(aux[i]) / 3);
	comp u, v, w = comp(-0.5, sqrt(0.75));
	//y=u+v
	vector<comp> raices;
	if(igual(abs(P), 0)){
		raices = {aux[0] + aux[1] - b / (3.0L * a), aux[0] * w + aux[1] * w * w - b / (3.0L * a), aux[0] * w * w + aux[1] * w - b / (3.0L * a)};
	}else{
		for(size_t i = 0; i < 3; i++){
			for(size_t j = 0; j < 3; j++){
				u = aux[0] * pow(w, i), v = aux[1] * pow(w, j);
				if(igual(abs(3.0L * u * v + P), 0)) raices.push_back(u + v - b / (3.0L * a));
			}
		}
	}
	return raices;
}

vector<comp> ec_4(comp a, comp b, comp c, comp d, comp e){ //ax^4+bx^3+cx^2+dx+e=0
	//ecuacion auxiliar: hacemos x=y-b/4a, y^4+Ax^2+Bx+C=0
	comp A = (8.0L * a * c - 3.0L * b * b)/(8.0L * a * a);
	comp B = (b * b * b - 4.0L * a * b * c + 8.0L * a * a * d)/(8.0L * a * a * a);
	comp C = (16.0L * a * b * b * c - 3.0L * b * b * b * b - 64.0L * a * a * b * d + 256.0L * a * a * a * e)/(256.0L * a * a * a * a);
	//cúbica auxiliar: p^3+2Ap^2+(A^2-4C)p-B^2=0
	vector<comp> aux = ec_3(1.0L, 2.0L * A, A * A - 4.0L * C, -B * B);
	for(int i = 0 ; i < 3; i++) aux[i] = polar(sqrt(abs(aux[i])), arg(aux[i]) / 2);
	comp p1, p2, p3, w = -1;
	//y=(p1+p2+p3)/2
	vector<comp> raices;
	if(igual(abs(B), 0)){
		raices = {(aux[0] + aux[1] - aux[2]) / 2.0L - b / (4.0L * a), (aux[0] - aux[1] + aux[2]) / 2.0L - b / (4.0L * a), (-aux[0] + aux[1] + aux[2]) / 2.0L - b / (4.0L * a), (-aux[0] - aux[1] - aux[2]) / 2.0L - b / (4.0L * a)};
	}else{
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				for(int k = 0; k < 2; k++){
					p1 = aux[0] * pow(w, i), p2 = aux[1] * pow(w, j), p3 = aux[2] * pow(w, k);
					if(igual(abs(p1 * p2 * p3 + B), 0)) raices.push_back((p1 + p2 + p3) / 2.0L - b / (4.0L * a));
				}
			}
		}
	}
	return raices;
}

vector<comp> ec_5(comp a, comp b, comp c, comp d, comp e, comp f){ //ax^5+bx^4+cx^3+dx^2+ex+f=0
	comp x0 = 0.718281828, xi = 0;
	int i = 1;
	while(i <= 100){
		comp num = ((((a * x0 + b) * x0 + c) * x0 + d) * x0 + e) * x0 + f;
		comp den = ((((5.0L * a * x0 + 4.0L * b) * x0) + 3.0L * c) * x0 + 2.0L * d) * x0 + e;
		if(igual(abs(num), 0)) break;
		xi = x0 - num / den;
		if(igual(x0.real(), xi.real())) break;
		x0 = xi;
		i++;
	}
	comp A = a;
	comp B = A * x0 + b;
	comp C = B * x0 + c;
	comp D = C * x0 + d;
	comp E = D * x0 + e;
	vector<comp> tmp = ec_4(A, B, C, D, E);
	tmp.push_back(x0);
	return tmp;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	int eq = 1;
	while(cin >> n){
		if(n == 0) break;
		comp a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
		vector<ld> solutions;
		vector<comp> tmp;
		if(n == 1) cin >> e >> f, tmp = ec_1(e, f);
		if(n == 2) cin >> d >> e >> f, tmp = ec_2(d, e, f);
		if(n == 3) cin >> c >> d >> e >> f, tmp = ec_3(c, d, e, f);
		if(n == 4) cin >> b >> c >> d >> e >> f, tmp = ec_4(b, c, d, e, f);
		if(n == 5) cin >> a >> b >> c >> d >> e >> f, tmp = ec_5(a, b, c, d, e, f);
		for(comp & sol : tmp){
			if(abs(sol.real()) < 1e-4) sol.real(0);
			solutions.push_back(sol.real());
		}
		sort(solutions.begin(), solutions.end());
		cout << "Equation " << eq++ << ":";
		for(ld & sol : solutions){
			cout << fixed << setprecision(4) << " " << sol;
		}
		cout << "\n";
	}
	return 0;
}