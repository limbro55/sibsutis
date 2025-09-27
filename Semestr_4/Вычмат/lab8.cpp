#include <iostream>
#include <cmath>
#include <ctime>


using namespace std;

double h(double x1, double x2)
{
	return x2 - x1;
}

int main()
{
	const int n = 5, Matrix_size = 3, Print_size = 15;
	double x_mas[n] = {1,3,5,7,9};
	double y_mas[n] = {2,5,2,-1,2};
	double print_y[Print_size];
	double print_x[Print_size];
	double C[Matrix_size][Matrix_size] = {0}; // матрица коэффициентов
	double D[Matrix_size]; //вектор правой части 
	double M[Matrix_size + 1]; //вектор вторых произв
	M[0] = 0;
	double h_mas[n-1];
	int k = 0;
	int xf = 4;
	for (int i = 0; i < n - 1; i++){ h_mas[i] = h(x_mas[i],x_mas[i+1]); }
	
	C[0][Matrix_size-1] = 0;
	C[Matrix_size-1][0] = 0;
	C[0][1] = h_mas[1]/6; 
	C[1][0] = h_mas[1]/6;
	C[1][2] = h_mas[2]/6;
	C[2][1] = h_mas[2]/6;
	for(int i = 0; i < n - 2; i++){C[k][k] = (h_mas[i] + h_mas[i+1]) / 3; k++; }
	
	cout << "Matrix C" << endl;
	for(int i = 0; i < Matrix_size; i++)
	{
		for(int j = 0; j < Matrix_size; j++)
		{
			cout << " " << C[i][j];
		}
		cout << endl;
	}
	cout << "Matrix D" << endl;
	for(int i = 0; i < Matrix_size; i++)
	{
		D[i] = ((y_mas[i+2] - y_mas[i+1]) / h_mas[i+1]) - ((y_mas[i+1] - y_mas[i]) / h_mas[i]); 
		cout << " " <<  D[i]  << endl;
	}
	
	
	for(int i = 0; i < Matrix_size; i++)
	{
		double maxEl = abs(C[i][i]);
		int maxRow = i;
		for(int j = 0; j < Matrix_size; j++)
		{
			if(abs(C[j][i]) > maxEl)
			{
				maxEl = abs(C[i][j]);
				maxRow = j;
			}
		}
		swap(C[i], C[maxRow]);
		swap(D[i], D[maxRow]);
	}
	    
	    cout << "Matrix" << endl;
	    for( int i = 0; i < Matrix_size; i++)
	    {
	        for(int j = 0; j < Matrix_size; j++)
	        {
	            cout << " " << C[i][j]; 
	        }
	        cout << " " << D[i];
	        cout << endl;
	    }
	    cout << endl;
	    
	    
	    for(int i = 0; i < Matrix_size; i++)
		{
			for(int k = i + 1 ; k < Matrix_size; k++ )
			{
				double stek = C[k][i] / C[i][i] ;
				for(int j = i; j < Matrix_size; j++)
				{
					C[k][j] -= stek * C[i][j];
					
				}
				D[k] -= stek * D[i];
			}
			for(int j = 0; j < Matrix_size; j++)
			{
				cout.precision(3);
				cout << " " << C[i][j];
			}
			cout << " " << D[i];
			cout << endl;
		
		}	
		
		for(int i = Matrix_size - 1; i >= 0; i--)
		{
			M[i+1] = D[i];
			for(int j = i + 1; j < Matrix_size; j++)
			{
				M[i+1] -= C[i][j] * M[j+1];
			}
			M[i+1] = M[i+1] / C[i][i];
			if (abs(M[i+1]) < 1e-11){ M[i+1] = 0;}
		}
		
		cout << endl;
		for (int i = 0; i < Matrix_size; i++)
		{
			cout << "x" << i+1 << " = "  <<M[i + 1]  << endl;
		} 
		cout << endl;
	double stek = 0;
	int i = 0; 
	for(int j = 0; j < n;j++)
	{
		i = (xf > x_mas[j]) ? j: i;
		cout << "i=" <<  i << endl;
	}
	stek = (M[i]*pow(x_mas[i+1]-xf,3))/(6*h_mas[i]) 
            + (M[i+1]*pow(xf-x_mas[i],3))/(6*h_mas[i])
        	+ (y_mas[i] - M[i]*h_mas[i]*h_mas[i]/6)*(x_mas[i+1]-xf)/h_mas[i]
            + (y_mas[i+1] - M[i+1]*h_mas[i]*h_mas[i]/6)*(xf-x_mas[i])/h_mas[i];
	
	
	cout << stek << endl;
    return 0;
    
}