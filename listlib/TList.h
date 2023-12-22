#pragma once
#include "TNode.h"
#include <iostream>
using namespace std;

template<class T>
class TList
{
protected:
	TNode<T>* pFirst; // первое звено
	TNode<T>* pCurrent; // текущее звено
	TNode<T>* pPrevious; // звено перед текущим
	TNode<T>* pLast; // последнее звено
	TNode<T>* pStop; // значение указателя, означающего конец списка
	int length; // количество звеньев в списке

public:

	TList();
	~TList();
	int GetLength() { return length; }
	bool IsEmpty(); // список пуст ?
	// вставка звеньев
	void InsertFirst(T item); // перед первым
	void InsertNCurrent(T item); // перед текущим 
	void InsertPCurrent(T item); // перед текущим 
	void InsertLast(T item);  // вставить последним 

	// удаление звеньев
	void DeleteFirst(); // удалить первое звено 
	void DeleteCurrent(); // удалить текущее звено

	void GoNext(); // сдвиг вправо текущего звена
	// (=1 после применения GoNext для последнего звена списка)

	void Reset(); // установить на начало списка
	bool IsEnd();  // список завершен ?

	T GetCurrentItem();
	void SetCurrentItem(T item) { pCurrent->value = item; }


};
template <class T>
TList<T>::TList()
{
	this->pFirst = nullptr; 
	this->pCurrent = nullptr;
	this->pPrevious = nullptr;
	this->pLast = nullptr;
	this->pStop = nullptr;
	this->length = 0;

}

template <class T>
TList<T>::~TList()
{ }

template <class T>
bool TList<T>::IsEmpty()
{	
	if (this->length == 0)
		return true;
	else
		return false;
}

template <class T>
void TList<T>::InsertFirst(T item)
{
	TNode<T>* nNode = new TNode<T>;
	nNode->value = item;
	nNode->pNext = this->pFirst;
	this->pFirst = nNode;
	if (length == 0) {
		this->pCurrent = this->pFirst;
		this->pLast = this->pFirst;
		this->pStop = new TNode<T>;
		pStop->pNext = nullptr;
	}
	length++;
}

template <class T>
void TList<T>::InsertLast(T item)
{
	TNode<T>* nNode = new TNode<T>;
	nNode->value = item;
	nNode->pNext = nullptr;
	if (length == 0) {
		this->pCurrent = this->pFirst;
		pFirst = nNode;
		pStop = new TNode<T>;
		pStop->pNext = nullptr;
	}
	else {
		pLast->pNext = nNode;
	}
	pLast = nNode;
	length++;
}

template <class T>
void TList<T>::InsertPCurrent(T item)
{
	TNode<T>* nNode = new TNode<T>; 
	nNode->value = item;  

	if (pCurrent == pLast) { 
		nNode->pNext = nullptr; 
		pLast->pNext = nNode; 
		pLast = nNode; 
	}
	else {
		nNode->pNext = pCurrent->pNext;
		pCurrent->pNext = nNode; 
	}
	length++;
}

template <class T>
void TList<T>::InsertNCurrent(T item)
{
	TNode<T>* nNode = new TNode<T>;
	nNode->value = item;

	if (pCurrent == pFirst) {
		nNode->pNext = pFirst;
		pFirst = nNode;
	}
	else {
		pPrevious->pNext = nNode;
		nNode->pNext = pCurrent;
	}
	length++;
}



template <class T>
void TList<T>::DeleteFirst()
{
	if (pFirst != nullptr) {
		TNode<T>* temp = pFirst;
		pFirst = pFirst->pNext;
		delete temp;
		length--;
		if (length == 0) {
			pLast = nullptr;
			pStop = nullptr;
		}
	}
}

template <class T>
void TList<T>::DeleteCurrent()
{
	if (pCurrent != nullptr && pFirst != nullptr) {
		if (pCurrent == pFirst) {
			DeleteFirst();
		}
		else {
			pPrevious->pNext = pCurrent->pNext;
			pCurrent = pCurrent->pNext;
			length--;
		}
		if (pCurrent == pLast) {
			pLast = pPrevious;
		}
		if (pCurrent == pStop) {
			pStop = pPrevious;
		}
	}
}

template <class T>
T TList<T>::GetCurrentItem()
{
	if (pCurrent == pStop)
		throw " ";
	return pCurrent->value;
}

template <class T>
void TList<T>::Reset()
{
	pCurrent = pFirst;
	pPrevious = nullptr;
}

template <class T>
void TList<T>::GoNext()
{
	if (pCurrent != nullptr) {
		pPrevious = pCurrent;
		pCurrent = pCurrent->pNext;
	}
}

template <class T>
bool TList<T>::IsEnd()
{	
	if (pCurrent->pNext == pStop)
		return true;
	else
		return false;
}