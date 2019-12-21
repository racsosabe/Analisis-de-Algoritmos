#include "InfInt.h"
#include<bits/stdc++.h>
using namespace::std;

typedef InfInt int1024_t;

int1024_t fastexp(int1024_t x, int b){
	int1024_t r = 1;
	while(b > 0){
		if(b&1) r *= x;
		x *= x;
		b >>= 1;
	}
	return r;
}

int1024_t getFactor(int1024_t x){
	int1024_t i = 3;
	while(i * i <= x){
		if(x % i == InfInt(0)){
			return i;
		}
		i += 2;
	}
}

void testPrimality(int p){
	auto start = chrono::steady_clock::now();
	int1024_t x = 2LL;
	int1024_t M = fastexp(x,p) - 1LL;
	int1024_t s = 4;
	cerr << "Analizando M" << p << endl;
	for(int i=1; i<=p-2; i++){
		s = s * s - 2;
		if(s >= M) s %= M;
	}
	string ans = (s == InfInt(0)? "es primo" : "no es primo");
	auto end = chrono::steady_clock::now();
	cerr << "Tiempo de ejecución: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms\n";
	cerr << "Veredicto: M" << p << " " << ans << '\n';
	if(ans[0] == 'n'){
		cerr << "Uno de sus factores es " << getFactor(M) << endl;
	}
}

int main(){
	int p;
	cin >> p;
	testPrimality(p);
	return 0;
}
