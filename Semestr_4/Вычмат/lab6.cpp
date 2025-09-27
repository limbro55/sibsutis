#include <iostream>
#include <cmath>
#include <ctime>
#include <complex>

using namespace std;

complex<double> Exp(double angle)
{
	return complex<double>(cos(angle),sin(angle));
}

int main()
{
	const double pi = 3.1415;
	const int n = 4, h = 1;
	int T = n*h; 
	double x = 1.5;
	double x_mas[n] = {0,1,2,3};
	double y_mas[n] = {0,1,4,9};
	double k_mas[n] = {-1,0,1,2};
	double nd = n;
	
	complex<double> y(0,0);
	for(int i = 0; i < n; i++)
	{
		complex<double> Aj(0,0);
		for(int j = 0; j < n; j++)
		{
			double stek = (-2 * pi * j * k_mas[i]) / n ;
			Aj += y_mas[j] * Exp(stek);
			cout << "Aj = " << Aj << " exp =" <<  Exp(stek) << endl;
		}
		
		double stek = 2*pi*k_mas[i]* (x - x_mas[0]) / T;
		double check = 1/nd;
		y += (Aj * Exp(stek)) * check;
	}
	cout << y << endl;
	
}