#include <iostream>
#include <chrono>

using namespace std;

#define MAX_SIZE 500

/*
En el IDE de zinjai se probo hasta una matriz de 500x500, en el siguiente link se probo con una matriz de 1000x1000
Link para probar el programa: https://www.onlinegdb.com/online_c++_compiler
*/
int main() {
	double A[MAX_SIZE][MAX_SIZE], x[MAX_SIZE], y[MAX_SIZE];
	chrono::duration<float,milli> duration;
	auto start = chrono::system_clock::now();
	
	for(int i = 0; i < MAX_SIZE; ++i) {
		x[i] = i;
		y[i] = 0;
		for(int j = 0; j < MAX_SIZE; ++j)
			A[i][j] = i+j;
	}
	auto end = chrono::system_clock::now();
	duration = end - start;
	cout<<"Tiempo de carga de la matriz con "<< MAX_SIZE << "x" << MAX_SIZE << " datos: " << duration.count() << " ms\n";
	
	/// FIRST TEST: row then column
	start = chrono::system_clock::now();
	for(int i = 0; i < MAX_SIZE; ++i)
		for(int j = 0; j < MAX_SIZE; ++j)
			y[i] += A[i][j] * x[j];
	end = chrono::system_clock::now();
	duration = end - start;
	cout<<"Tiempo de CASO 1: " << duration.count() << " ms\n";
		
	for(int i = 0; i < MAX_SIZE; ++i)
		y[i] = 0;
	
	/// SECOND TEST: column then row
	start = chrono::system_clock::now();
	for(int j = 0; j < MAX_SIZE; ++j)
		for(int i = 0; i < MAX_SIZE; ++i)
			y[i] += A[i][j] * x[j];
	end = chrono::system_clock::now();
	duration = end - start;
	cout<<"Tiempo de CASO 2: " << duration.count() << " ms\n";
		
	return 0;
}
