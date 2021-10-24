// Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <math.h>
#include <conio.h>
#include <stdio.h>


using namespace std;
void Out_Rez(double Sr, double Y, double Mod)
{
	cout << "S = " << Sr << "," << " Y = " << Y << "," << " Modul  = " << Mod << ";" << endl;	
}
int f_for(int i, int k, double in) 
{
	
	for (i = 1; i <= 2 * k; i++) //считает (2k)!
	{
		in = in * i;
	}
}


int main()
{
	double a, b, h, S, Y, in, x, Mod, Sr;
	int n, k, i;
	puts("input a, b, h, n:");
	scanf_s("%lf%lf%lf%d", &a, &b, &h, &n);
	for (x = a; x <= b; x = x + h)
	{
		Sr = 0;
		for (k = 0; k <= n; k++) //считает сумму в функции S
		{
			in = 1;
			f_for(i, k, in);
			S = pow(x, 2 * k) / in;
			Sr = Sr + S;
		}
		Y = (exp(x) + exp(-1 * x)) / 2;
		Mod = abs(Y - Sr);
		Out_Rez(Sr, Y, Mod);
	}

}
