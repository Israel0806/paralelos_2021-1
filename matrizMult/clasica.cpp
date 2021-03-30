#include <iostream>

using namespace std;

int main() {
    int A[20][20], B[20][20], C[20][20];
    int row_A, col_A, col_B;

    cout << "Matriz A\n";
    cout << "Filas de matriz A: "; cin >> row_A;
    cout << "Columnas de matriz A: "; cin >> col_A;

    for(int i = 0; i < row_A; ++i)
        for(int j = 0; j < col_A; ++j)
            A[i][j] = i + j;

    cout<<"\nMatriz B\n";
    cout<<"Filas de B: " << col_A << " (ya esta definido y no es necesario).\n";
    cout<<"Columnas de B: "; cin>>col_B;
    for(int i=0; i < col_A; ++i)
        for(int j=0; j < col_B; ++j)
            B[i][j] = i + j;

    // Matriz C
    for(int i=0; i<row_A; ++i)
        for(int j=0; j<col_B; ++j)
            C[i][j] = 0;

    // Multiplicacion clasica
    for(int i = 0; i < row_A; ++i)
        for(int j = 0; j < col_B; ++j)
            for(int k = 0; k < col_A; ++k)
                C[i][j] += A[i][k] * B[k][j];


    cout<<"Matriz A: \n";
    for(int i = 0; i < row_A; ++i) {
        for(int j = 0; j < col_A; ++j)
            cout << A[i][j] << " ";
        cout << endl;
    }

    cout<<"Matriz B: \n";
    for(int i = 0; i < col_A; ++i) {
        for(int j = 0; j < col_B; ++j)
            cout << B[i][j] << " ";
        cout << endl;
    }

    cout<<"Matriz C: \n";
    for(int i = 0; i < row_A; ++i) {
        for(int j = 0; j < col_B; ++j)
            cout << C[i][j] << " ";
        cout << endl;
    }
}