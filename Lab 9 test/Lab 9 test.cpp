#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include <math.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	HINSTANCE mydll;
	string s = "Dll1";

	if (!LoadLibraryExA(s.c_str(), 0, LOAD_LIBRARY_AS_DATAFILE))
	{
		cout << "error" << endl;
		return 0;
	}
	mydll = LoadLibraryA("Dll1");
	if (mydll == NULL) {
		cout << "error" << endl;
		return 0;
	}

	typedef double(*NFun)(double, double, double);
	NFun mytg = (NFun)GetProcAddress(mydll, "myf_3532703_00001");
	typedef double(*NFunc)(double, double);
	NFunc tang = (NFunc)GetProcAddress(mydll, "myf_math");
	typedef const char* (*NFunct)();
	NFunct Name = (NFunct)GetProcAddress(mydll, "FName");

	if (!(mydll && mytg && tang && Name))
	{
		cout << "error" << endl;
		system("pause");
		exit(0);
	}

	setlocale(LC_ALL, "rus");
	double x1, x2, dx, f, x, d, r1 = 0, r2 = 0, A;
	int k = 1;int w = 0;
	string Eps;
	cout << "Введите eps: ";
	cin >> Eps;
	cout << "Введите параметр А: ";
	cin >> A;
	bool check = false;
link3:
	while (check == false)
	{
		for (auto c : Eps)
		{
			if ((c < 48 || c > 57) && c != 46)
			{
				cout << "Некорректный ввод. Попробуйте снова: ";
				cin >> Eps;
				goto link3;
			}
		}
		check = true;
	}
	check = false;
	double E;
	stringstream(Eps) >> E;
	if (E == 0)
	{
		Eps = "-1";
		goto link3;
	}
	w = 0;
	string sx1, sx2, sxd;
	cout << "Введите Х1: ";
	cin >> sx1;
link4:
	while (check == false)
	{
		for (auto c : sx1)
		{
			if ((c < 48 || c > 57) && c != 46 && c != 45)
			{
				cout << "Некорректный ввод. Попробуйте снова: ";
				cin >> sx1;
				goto link4;
			}
		}
		check = true;
	}
	check = false;
	stringstream(sx1) >> x1;
	cout << "Введите Х2: ";
	cin >> sx2;
link5:
	while (check == false)
	{
		for (auto c : sx2)
		{
			if ((c < 48 || c > 57) && c != 46 && c != 45)
			{
				cout << "Некорректный ввод. Попробуйте снова: ";
				cin >> sx2;
				goto link5;
			}
		}
		check = true;
	}
	check = false;
	stringstream(sx2) >> x2;
	cout << "Введите величину шага dX: ";
	cin >> sxd;
link6:
	while (check == false)
	{
		for (auto c : sxd)
		{
			if ((c < 48 || c > 57) && c != 46 && c != 45)
			{
				cout << "Некорректный ввод. Попробуйте снова: ";
				cin >> sxd;
				goto link6;
			}
		}
		check = true;
	}
	stringstream(sxd) >> dx;

link2:
	while (w == 0)
	{
		if (((x1 < x2) && (dx < 0)) || ((x1 > x2) && (dx > 0)))
		{
			cout << "Если вводить dx < 0, то д. б. х1 > x2, и, наоборот, если вводить dx > 0, то д. б. х1 < x2  Попробуйте снова: " << endl;
			cout << "Введите Х1: ";
			cin >> x1;
			cout << "Введите Х2: ";
			cin >> x2;
			cout << "Введите величину шага dX: ";
			cin >> dx;
			goto link2;

		}
		w = 1;
	}


	w = 0;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "|X\t        |";
	string name = Name();
	if (name.length() < 7) {
		cout << Name() << "\t\t|My Function(x)\t|delta\t        |" << endl;
	}
	else
		cout << Name() << "\t|My Function(x)\t|delta\t        |" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	if ((dx == 0) || (abs(dx) >= abs(x1 - x2))) goto link;//вычисление только одной строчки
link1:
	while (abs(x2 - x1) + pow(10, -10) >= abs(dx))
	{
		double temp = mytg(A, E, x1);
		int t = isinf(temp);
		d = pow(abs(mytg(A, E, x1)*mytg(A, E, x1) - tang(A, x1) * tang(A, x1)), 0.5);
		cout.precision(7);
		if ((temp == temp))
		{
			if (((x1 <= -1.57079) || (x1 >= 1.57079)) && (tan(0.3) == tang(A, 0.3)))
				cout << "|" << fixed << x1 << "\t|error\t\t|error\t\t|error\t\t|" << endl;
			else {
				if (isinf(temp) == 1)
				{
					cout << "|" << fixed << x1 << "\t|" << fixed << tang(A, x1) << "\t|бесконечность\t|бесконечность\t|" << endl;
				}
				else {
					cout << "|" << fixed << x1 << "\t|" << fixed << tang(A, x1) << "\t|" << fixed << mytg(A, E, x1) << "\t|" << fixed << d << "\t|" << endl;
				}
			}
			cout << "-----------------------------------------------------------------" << endl;
		}
		else {
			cout << "|" << fixed << x1 << "\t|error\t\t|error\t\t|error\t\t|" << endl;
			cout << "-----------------------------------------------------------------" << endl;
		}
		k++;
		x1 += dx;
	}
link:
	d = pow(abs(mytg(A, E, x1)*mytg(A, E, x1) - tang(A, x1) * tang(A, x1)), 0.5);
	cout.precision(7);
	double temp = mytg(A, E, x1);
	if ((temp == temp))
	{
		if (((x1 <= -1.57079) || (x1 >= 1.57079)) && (tan(0.3) == tang(A, 0.3)))
			cout << "|" << fixed << x1 << "\t|error\t\t|error\t\t|error\t\t|" << endl;
		else {
			if (isinf(temp) == 1)
			{
				cout << "|" << fixed << x1 << "\t|" << fixed << tang(A, x1) << "\t|бесконечность\t|бесконечность\t|" << endl;
			}
			else {
				cout << "|" << fixed << x1 << "\t|" << fixed << tang(A, x1) << "\t|" << fixed << mytg(A, E, x1) << "\t|" << fixed << d << "\t|" << endl;
			}
		}
		cout << "-----------------------------------------------------------------" << endl;
	}
	else {
		cout << "|" << fixed << x1 << "\t|error\t\t|error\t\t|error\t\t|" << endl;
		cout << "-----------------------------------------------------------------" << endl;
	}
	double xi;
	string sxi;
	cout << "Введите Х(ideal): ";
	cin >> sxi;
link7:
	while (check == false)
	{
		for (auto c : sxi)
		{
			if ((c < 48 || c > 57) && c != 46 && c != 45)
			{
				cout << "Некорректный ввод. Попробуйте снова: ";
				cin >> sxi;
				goto link7;
			}
		}
		check = true;
	}
	stringstream(sxi) >> xi;
	cout << "_________________________________________________________________" << endl;
	if (name.length() < 7) {
		cout << "\n|eps\t        |" << Name() << "\t\t|My function(x)\t|delta\t        |" << endl;
	}
	else {
		cout << "\n|eps\t        |" << Name() << "\t|My function(x)\t|delta\t        |" << endl;
	}
	cout << "_________________________________________________________________" << endl;
	long double e;
	for (int i = -1;i >= -7;i--)
	{
		e = pow(10, i);
		temp = mytg(A, e, xi);
		d = pow(abs(mytg(A, e, xi)*mytg(A, e, xi) - tang(A, xi) * tang(A, xi)), 0.5);
		cout.precision(7);
		if (temp == temp)//yлавливание нанинд
		{
			if (((xi <= -1.57079) || (xi >= 1.57079)) && (tan(0.3) == tang(A, 0.3)))
				cout << "|" << fixed << e << "\t|error\t\t|error\t\t|error\t\t|" << endl;
			else {
				if (isinf(temp) == 1)
				{
					cout << "|" << fixed << e << "\t|" << fixed << tang(A, x1) << "\t|бесконечность\t|бесконечность\t|" << endl;
				}
				else
				{
					cout << "|" << fixed << e << "\t|" << fixed << tang(A, xi) << "\t|" << fixed << mytg(A, e, xi) << "\t|" << fixed << d << "\t|" << endl;
				}
			}
			cout << "_________________________________________________________________" << endl;
		}
		else {
			cout << "|" << e << "\t|error\t\t|error\t\t|error\t\t|" << endl;
			cout << "_________________________________________________________________" << endl;
		}
	}
}


