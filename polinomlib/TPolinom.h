#pragma once
#include "THeadList.h"
#include "TMonom.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

const int nonDisplayedZeros = 4; // Количество неотображаемых нулей при выводе коэффициента полинома
								 // Кол-во символов после запятой = 6 - nonDisplayedZeros
using namespace std;

class TPolinom : public THeadList<TMonom>
{
public:
	TPolinom();
	TPolinom(TPolinom& other);
	TPolinom(vector<int> a);
	TPolinom& operator=(TPolinom& other); // присваивание
	TPolinom& operator+(TPolinom& q); // сложение полиномов

	// дополнительно можно реализовать:
	void AddMonom(TMonom newMonom); // добавление монома
	//TPolinom MultMonom(TMonom monom); // умножение мономов
	TPolinom AddPolinom(TPolinom& other); // добавление полинома
	TPolinom operator*(double coef); // умножение полинома на число
	//TPolinom operator* (TPolinom& other); // умножение полиномов
	bool operator==(TPolinom& other); // сравнение полиномов на равенство
	string ToString(); // перевод в строку
};

TPolinom::TPolinom() :THeadList<TMonom>::THeadList() 
{ 
	length = 0;
}

TPolinom::TPolinom(TPolinom& other)
{
	int tmp = other.GetLength();
	other.Reset();
	TMonom first;
	first = other.GetCurrentItem();
	other.GoNext();
	InsertFirst(first);
	Reset();
	for (int i = 1; i < tmp; i++) {
		TMonom m;
		m = other.GetCurrentItem();
		InsertPCurrent(m);
		GoNext();
		other.GoNext();
	}
	Reset();
	pStop = nullptr;
}
TPolinom::TPolinom(vector<int> a)
{
	
	pStop = nullptr;
	int c = 1;
	int i1 = 1;
	int sz = a.size(); 
	TMonom start(a[0], a[1]); 
	InsertFirst(start); 
	Reset(); 
	TMonom mon; 
	for (int i = 2; i < sz; i += 2) { 
		int ind1 = a[i + 1]; 
		mon = GetCurrentItem(); 
		Reset(); 
		TMonom first; 
		first = GetCurrentItem(); 
		int ind = first.GetIndex(); 
		if (ind1 > ind) { InsertFirst(TMonom(a[i], a[i + 1])); c++; } 
		else 
		{
			while (ind1 < ind) {
				if (i1 < c) {
					GoNext();
					i1++;
					mon = GetCurrentItem();
					ind = mon.GetIndex();
				}
				else { InsertLast(TMonom(a[i], a[i + 1])); c++; break; }
			}

			if (ind == ind1) {
				if (i1 == 1) {
					first.SetCoef(first.GetCoef() + a[i]);
					InsertFirst(first);
					Reset();
					GoNext();
					DeleteCurrent();
				}
				else
				{
					mon.SetCoef(mon.GetCoef() + a[i]);
					DeleteCurrent();
					InsertPCurrent(mon);
				}
			}
			else { InsertPCurrent(TMonom(a[i], a[i + 1])); c++; }
		}i1 = 1;
	}Reset();

}

TPolinom& TPolinom::operator=(TPolinom& other)
{
	if (this != &other) {
		THeadList<TMonom>::operator=(other);
	}
	return *this;
}

void TPolinom::AddMonom(TMonom m)
{
	int sz = GetLength();
	int i = 0;
	Reset();
	TMonom mon;
	mon = GetCurrentItem();
	int ind = mon.GetIndex();
	int ind1 = m.GetIndex(); 
	if (ind1 > ind)
		InsertFirst(m); 
	else 
	{ 
		while (ind1 < ind) { 
			if (i < sz) { 
				GoNext(); 
				i++; 
				mon = GetCurrentItem(); 
				ind = mon.GetIndex(); 
			}
			else {
				InsertLast(m); return; 
			}
		}
		if (ind == ind1) {
			if (mon.GetCoef() + m.GetCoef() != 0) {
				mon.SetCoef(mon.GetCoef() + m.GetCoef());
				DeleteCurrent();
				InsertNCurrent(mon);
			}
			else { DeleteCurrent(); }
		}
		else
		{
			InsertPCurrent(m);
		}
	}
	Reset();
}

TPolinom& TPolinom::operator+(TPolinom& other)
{
	TPolinom* result = new TPolinom(*this);
	TPolinom tempOther(other); 


	int sz = tempOther.GetLength();
	tempOther.Reset();
	for (int i = 0; i < sz; i++) {
		TMonom a = tempOther.GetCurrentItem();
		result->AddMonom(a);
		tempOther.GoNext();
	}

	return *result;
}

TPolinom TPolinom::AddPolinom(TPolinom& other)
{
	TPolinom res(*this); 
	int sz = other.GetLength(); 
	other.Reset(); 
	for (int i = 0; i < sz; i++) { 
		TMonom a; 
		a = other.GetCurrentItem(); 
		res.AddMonom(a);  
		other.GoNext(); 
	}

	return res;
}

TPolinom TPolinom::operator*(double coef)
{
	Reset(); 
	for (int i = 0; i < GetLength(); i++)  
	{ 
		TMonom currMonom = GetCurrentItem(); 
		currMonom.SetCoef(currMonom.GetCoef() * coef); 
		SetCurrentItem(currMonom); 
		GoNext(); 
	}
	return *this;
}

/*TPolinom TPolinom::operator*(TPolinom& other)
{
	

}*/

bool TPolinom::operator==(TPolinom& other)
{
	int sz = other.GetLength(); 
	if (this->GetLength() != other.GetLength()) { 
		return false;
	}
	Reset(); 
	other.Reset(); 
	for (int i = 0; i < sz; i++) { 
		TMonom a, b; 
		a = other.GetCurrentItem(); 
		b = GetCurrentItem(); 
		GoNext(); 
		other.GoNext(); 
		if (a == b) { 

		}
		else { return false; }
	}
	return true; 
}


string TPolinom::ToString()
{
	string results;
	int sz = GetLength();
	Reset();
	for (int i = 0; i < sz; i++) {
		TMonom a;
		a = GetCurrentItem();
		double A = a.GetCoef(); 
		std::ostringstream o; 
		o << setprecision(3) << A; 
		int ind = a.GetIndex(); 
		results += o.str(); 
		results += "x^"; 
		results += to_string((ind - ind % 100) / 100);  
		results += "y^"; 
		results += to_string(((ind % 100) - (ind % 10)) / 10); 
		results += "z^"; 
		results += to_string(ind % 10); 
		if (i != sz - 1) 
			results += " + "; 
		if (i < sz - 1) 
			GoNext(); 
	}
	Reset(); 
	return results; 
}

/*TPolinom TPolinom::MultMonom(TMonom monom)
{
	return *this * monom; 
}*/