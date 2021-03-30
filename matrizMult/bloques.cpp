#include <iostream>
#include <chrono>

using namespace std;

int main()
{
    // double A[20][20], B[20][20], C[20][20];
    int row_A, col_A, col_B;

    cout << "Matriz A\n";
    cout << "Filas de matriz A: ";
    cin >> row_A;
    cout << "Columnas de matriz A: ";
    cin >> col_A;
    cout << "\nMatriz B\n";
    cout << "Filas de B: " << col_A << " (ya esta definido y no es necesario).\n";
    cout << "Columnas de B: ";

    double *A = new double[row_A];
    double *B = new double[col_A];
    double *C = new double[row_A];
    for(int i = 0; i < row_A; ++i)
        A[i] = new double[col_A];
    for(int i = 0; i < col_A; ++i)
        B[i] = new double[col_B];
    for(int i = 0; i < row_A; ++i)
        C[i] = new double[col_B];
    
    // Matriz A
    for (int i = 0; i < row_A; ++i)
        for (int j = 0; j < col_A; ++j)
            A[i][j] = i + j;

    // Matriz B
    cin >> col_B;
    for (int i = 0; i < col_A; ++i)
        for (int j = 0; j < col_B; ++j)
            B[i][j] = i + j;

    // Matriz C
    for (int i = 0; i < row_A; ++i)
        for (int j = 0; j < col_B; ++j)
            C[i][j] = 0;

    
    int block_size = 5;
    
    chrono::duration<float,milli> duration;
    auto start = chrono::system_clock::now();
    for(int i=0; i<row_A; i+=block_size){
        for(int j=0; j<col_A; j+=block_size){
            for(int k=0; k<col_B; k+=block_size){
                for(int ii=i; ii<i+block_size; ii++){
                    for(int jj=j; jj<j+block_size; jj++){
                        for(int kk=k; kk<k+block_size; kk++){
                            C[ii][jj] += A[ii][kk]*B[kk][jj];
                        }
                    }
                } 
            }
        }
    }
    auto end = chrono::system_clock::now();

    duration = end - start;
    cout<<"Tiempo: " << duration.count() << " ms\n";
}