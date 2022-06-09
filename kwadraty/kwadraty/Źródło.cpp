#include<iostream>
#include<math.h>
using namespace std;


double xsinFun(double x) 
{
	return x * x * sin(x) * sin(x) * sin(x);
}

double expFun(double x)
{
	return exp(x * x) * (x - 1);
}

double horner(double wsp[], int st, double x)
{

	if (x == 0) return wsp[st];
	else {
		double wynik = wsp[0];
		for (int i = 1; i <= st; i++)
		{
			wynik = wynik * x + wsp[i];
		}
		return wynik;
	}

}

double poleTrapezu(double fA, double fB,double h) 
{
	double pole = 0;
	pole = ((fA + fB) / 2) * h;
	return pole;
}

double metodaTrapezow(double wsp[],int stopien, double a, double b, int liczba)//równoodleg³e
{	
	double h = (b-a) / (double)liczba;//wysokoœæ trapezu

	double wynik = 0;
	for (int i = 0; i < liczba; i++) 
	{
		double A = a + (i * h);
		double B = a + ((i + 1) * h);

		wynik += poleTrapezu(horner(wsp, stopien, A), horner(wsp, stopien, B), h);
		//wynik += poleTrapezu(xsinFun(A), xsinFun(B), h); //zad4
		//wynik += poleTrapezu(expFun(A), expFun(B), h); //zad5
	}

	return wynik;
}

double metodaTrapezowRoznoodleglych(double wsp[], int stopien, int liczba, double wartosci[])//ró¿noodleg³e
{
	
	double wynik = 0;
	double A=0, B=0, h=0;
	for (int i = 0; i < liczba-1; i++)
	{
		A = wartosci[i];//punkt mniejszy (wzgledem wartosci x)
		B = wartosci[i+1];//punkt wiekszy (wzgledem wartosci x)
		h = (B - A);//wysokoœæ trapezu
		

		wynik += poleTrapezu(horner(wsp, stopien, A), horner(wsp, stopien, B), h);
		//wynik += poleTrapezu(xsinFun(A), xsinFun(B), h);
		//wynik += poleTrapezu(expFun(A), expFun(B), h);
	}

	return wynik;
}



double metodaSimpsona(double wsp[],int stopien,double a,double b, int liczba)//równoodleg³e
{
	double h = (b - a) / liczba;//odleg³oœæ miêdzy kolejnymi wartoœciami

	double wynik = 0;
	for (int i = 0; i < liczba; i++)
	{
		double A = a + (i * h);
		double B = a + ((i + 1) * h);

		//wynik += (horner(wsp, stopien, A)+(4*horner(wsp,stopien, (A+B)/2))+ horner(wsp, stopien,B));
		wynik += (xsinFun(A) + (4 * xsinFun((A + B) / 2)) + xsinFun(B));
		//wynik += (expFun(A) + (4 * expFun((A + B) / 2)) + expFun(B));

	}
	
	wynik = wynik * (h / 6);

	return wynik;
}


double trapez(double a, double b, int n) {
	double h = a - b / (double)n;
	double aW = xsinFun(a);
	double bW;
	double sum = 0.0;
	for (int i = 1; i <= n; i++) {
		bW = xsinFun(a + i * h);
		sum += aW + bW;
		aW = bW;
	}
	return sum * 0.5 * h;

}

void main() 
{
	int stopien = 4;
	double wsp[]{ 0.4, 5, -6, -2, 55 };//wzór funkcji do ca³kowania


	int liczba = 8;//liczba wartosci w przedziale [a,b]
	double a = 0;//pocz¹tek ca³kowania
	double b = 4.5;//koniec ca³kowania


	cout << metodaTrapezow(wsp, stopien, a, b, liczba) << endl;
	cout << metodaSimpsona(wsp, stopien, a, b, liczba) << endl;
	cout << trapez(a, b, liczba);
}