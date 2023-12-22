#include <iostream>
#include "TList.h"
#include "TPolinom.h"
#include <vector>
#include <string>
using namespace std;


int main()
{
	setlocale(LC_ALL, "ru");


	cout << "Полиномы: " << endl;
	vector<int> a = { 1,222,2,444,3,555 };
	vector<int> b = { 1,234,5,555,4,891 };
	TPolinom p1(a);
	TPolinom p3(p1);//копия
	TPolinom p2(b);
	bool flag = (p1 == p3);
	cout << "Полином 1:" << endl;
	cout << p1.ToString() << endl;
	cout << "Полином 2" << endl;
	cout << p2.ToString();

	cout << endl << "Полином 3 - копия полинома 1: " << endl;
	cout << "Полином 3:" << endl;
	cout << p3.ToString()<< endl;

	cout << "Проверка на равенство: " << endl;
	cout << "Полином 1 == Полином 3? ";
	cout << flag<< endl;
	flag = (p1 == p2);
	cout << "Полином 1 == Полином 2? ";
	cout << flag;

	p3 = p2;
	cout << endl;

	cout << "Присваивание: " << endl;
	cout << "Полином 3 = Полином 2" << endl;
	cout << p3.ToString();

	TPolinom p4(a);
	p4 = p1.AddPolinom(p2);
	cout << endl;
	cout << "К полиному 1 добавим полином 2" << endl;
	cout << p4.ToString();

	cout << endl;
	cout << "Сложение полиномов: ";
	TPolinom p5(a);
	p5 = p1 + p2;
	cout << endl;
	cout << "Полином 1 + Полином 2" << endl;
	cout << p5.ToString();


	TMonom mon(1, 236);
	p3.AddMonom(mon);
	cout << endl;
	cout << "К полиному 3 добавим Моном" << endl;
	cout << p3.ToString();




}