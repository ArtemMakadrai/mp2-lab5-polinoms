#pragma once
#include "TList.h"
using namespace std; 


template<class T>
class THeadList : public TList<T>
{
protected:
	TNode<T>* pHead;  // заголовок, pFirst - звено за pHead
public:
	THeadList();
	~THeadList();
	void InsertFirst(T item); // вставка звеньев после заголовка
	void DeleteFirst(); // удалить первое звено
	THeadList<T>& operator=(THeadList<T>& other);
};
	
template<class T>
THeadList<T>& THeadList<T>::operator=(THeadList<T>& other) {
	if (this == &other) {
		return *this;
	}

	while (pFirst != nullptr) {
		DeleteFirst();
	}

	InsertFirst(other.pFirst->value);
	TNode<T>* tmp = other.pFirst;
	while (tmp->pNext != nullptr) {
		tmp = tmp->pNext;
		InsertPCurrent(tmp->value); 
	}
	
}
template<class T>
THeadList<T>::THeadList()
{
	pHead = new TNode<T>{};
	this->pFirst = pHead->pNext; 
	this->pStop = new TNode<T>{};
	this->pLast = this->pStop;
	this->pCurrent = this->pFirst;
	this->length = 0;

}

template<class T>
THeadList<T>::~THeadList()
{

}

template <class T>
void THeadList<T>::InsertFirst(T item)
{
	TNode<T>* nNode = new TNode<T>{ item, nullptr };
	nNode->pNext = this->pFirst;
	this->pFirst = nNode;
	if (length == 0) {
		this->pCurrent = this->pFirst;
		this->pLast = this->pFirst;
		this->pStop = new TNode<T>;
		pStop->pNext = nullptr;
	}
	this->length++; 
}

template <class T>
void THeadList<T>::DeleteFirst()
{
	if (this->IsEmpty()) {
		throw -1;
	}
	TNode<T>* temp = this->pFirst;
	this->pFirst = this->pFirst->pNext;
	delete temp;
	this->length--;
}