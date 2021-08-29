// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <iostream>
using namespace std;

double Kunko_tg(double a, double x, double E, long double bern[]) {
	double a1 = 0, a2;
	a2 = x;
	double sum = a1;
	if (abs(a2) < E) return sum;
	int index = 1;
	while (abs(a2 - a1) >= E) {
		a1 = a2;
		sum += a1;
		a2 = (a1 * 4 * fabs(bern[index + 1])  * (pow(2, 2 * index + 2) - 1)* pow(x, 2));
		a2 = a2 / ((pow(2, 2 * index) - 1) * fabs(bern[index])*(2 * index + 1)*(2 * index + 2));
		index += 1;
		if (fabs(a2 - a1) < E)
		{
			break;
		}
	}
	return sum;
}
extern "C" __declspec(dllexport) double myf_3532703_00001(double a, double eps, double x) {

	//числа бернулли
	long double bern[225];
	bern[0] = 0.5;
	for (int n = 1; n < 225; n++) {
		long double sum = 0;
		for (int k = 1; k <= n - 1; k++)// счет ряда
		{
			long double per = bern[k];
			for (int w = 0; w <= 2 * k - 2; w++)
				per = per * (2 * n - w);
			per = per * pow(-1, k - 1);
			for (int v = 1; v <= 2 * k; v++) per = per / v;
			sum = sum + per;
		}
		sum = sum + pow(2 * n + 1, -1) - 0.5;
		sum = sum * pow(-1, n);
		bern[n] = sum;
	}

	return Kunko_tg(a, x, eps, bern);;
}

extern "C" __declspec(dllexport)
const char* FName()
{
	const char* s = "tg(x)";
	return s;
}
extern "C" __declspec(dllexport) double myf_math(double a, double x)
{
	return tan(x);
}



