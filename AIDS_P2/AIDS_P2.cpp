// AIDS_P2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vector"
#include <iostream>
using namespace std;

struct elewator {
	unsigned long int masa;
	unsigned long int numer;
	int priority;
	bool operator < (const elewator& org) {
		if (masa == 0) { return false; }
		if (org.masa == 0) { return true; }
		return (masa < org.masa);
	}
	bool operator > (const elewator& org) {
		if (masa == 0) { return true; }
		if (org.masa == 0) { return false; }
		return (masa > org.masa);
	}
	bool operator == (const elewator &org) {
		//if (masa == 0) { return true; }
		return (numer == org.numer);
	}
};

vector<elewator> heap;
int* tablica;
int* tablica_n_v;
void GoDown(int index) {
	int length = heap.size();
	if (index >= length) { return; }
	int leftChildIndex = 2 * index;
	int rightChildIndex = 2 * index + 1;

	if ((leftChildIndex < length)&&heap[leftChildIndex] < heap[index]) {
		swap(heap[leftChildIndex], heap[index]);
		GoDown(index);
	}
	if ((rightChildIndex < length)&&heap[rightChildIndex] < heap[index]) {
		swap(heap[rightChildIndex], heap[index]);
		GoDown(index);

	}
}
void GoUp(int index) {

}
void make_h(elewator* arr, int length) {
	tablica = new int[length];
	tablica_n_v = new int[length];
	
	for (int i = 0; i < length; ++i)
	{
		heap.push_back(arr[i]);
	}
	for (int i = length; i > 0; i--)
	{
		GoDown(i);
	}
}



class MinHeap
{
private:
	void BubbleDown(int index);
	void BubbleUp(int index);
	void Heapify();
	int zero_count;

public:
	MinHeap(elewator* array, int length);
	MinHeap(const vector<elewator>& vector);
	MinHeap();
	int* tablica;
	int* tablica_n_v;
	void Insert(int index, int masa);
	elewator GetMin();
	int GetMinI();
	elewator GetMax();
	int GetMaxI();
	void DeleteMin();
	void nX(int numer, long int masa);
	void nm(long int masa);
	void nM(long int masa);
	void r(int numer, long int masa);
	void rm(long int masa);
	void rM(long int masa);
	void w(int numer);
	void wm();
	void wM();
	vector<elewator> _vector;
};

MinHeap::MinHeap(elewator* array, int length) : _vector(length)
{
	zero_count = 0;
	tablica = new int[length];
	tablica_n_v = new int[length];
	for (int i = 0; i < length; ++i)
	{
		_vector[i] = array[i];
		//_vector[i] = array[i];
		tablica[i] = _vector[i].numer;
		tablica_n_v[_vector[i].numer] = i;
		//tablica[i] = array[i].numer;
	}

	Heapify();

	for (int i = 0; i < length; ++i)
	{
		//_vector[i] = array[i];
		
		//tablica_n_v[_vector[i].numer] = i;
	}
}

MinHeap::MinHeap(const vector<elewator>& vector) : _vector(vector)
{
	Heapify();
}

MinHeap::MinHeap()
{
}

void MinHeap::Heapify()
{
	int length = _vector.size();
	zero_count = 0;
	for (int i = length - 1; i >= 0; --i)
	{
		if (_vector[i].masa == 0) {
			zero_count++;
			//swap(_vector[i], _vector[_vector.size()-1]);
		}
		
		BubbleDown(i);
		//cout << "t:" << tablica[i] << endl;
		//cout << "t2:" << tablica_n_v[i] << endl;
	}
	
}

void MinHeap::BubbleDown(int index)
{
	int length = _vector.size();
	int leftChildIndex = 2 * index;
	int rightChildIndex = 2 * index + 1;

	if (leftChildIndex >= length) {
		return; //index is a leaf
	}

	if (_vector[index].masa == 0) {
		swap(_vector[index], _vector[_vector.size() - 1]);
	}

	int minIndex = index;

	if (_vector[index] > _vector[leftChildIndex])
	{
		minIndex = leftChildIndex;
	}

	if ((rightChildIndex < length) && (_vector[minIndex] > _vector[rightChildIndex]))
	{
		minIndex = rightChildIndex;
	}

	if (minIndex != index)
	{
		//need to swap
		elewator temp = _vector[index];

		if (temp.masa == 0) {
			swap(_vector[index], _vector[_vector.size() - 1]);
		}

		int temp3 = tablica[index];
		int temp2 = index;

		_vector[index] = _vector[minIndex];
		tablica[index] = _vector[minIndex].numer;
		tablica_n_v[_vector[index].numer] = minIndex;



		_vector[minIndex] = temp;
		tablica[minIndex] = temp3;
		//tablica_n_v[minIndex] = index;
		tablica_n_v[_vector[minIndex].numer] = index;
		BubbleDown(minIndex);
	}
}

void MinHeap::BubbleUp(int index)
{
	if (index == 0)
		return;

	int parentIndex = (index -1) / 2;
	int leftChildIndex = 2*index ;
	int rightChildIndex = 2* index + 1;
	if (leftChildIndex > _vector.size()) {
		return; //index is a leaf
	}
	if (_vector[parentIndex] > _vector[index]|| _vector[leftChildIndex] > _vector[index] || (rightChildIndex < _vector.size()) && _vector[rightChildIndex] > _vector[index])
	{
		elewator temp = _vector[parentIndex];
		int temp3 = tablica[index];
		int temp2 = index;

		tablica[index] = _vector[parentIndex].numer;
		_vector[parentIndex] = _vector[index];
		tablica_n_v[index] = parentIndex;


		_vector[index] = temp;
		tablica[parentIndex] = temp3;
		tablica_n_v[parentIndex] = index;

		for (int i = 0; i < _vector.size(); i++)
		{
			cout << i << ":" << _vector[i].masa << "\t" << tablica[i] << "\t" << tablica_n_v[i] << endl;
		}

		BubbleUp(parentIndex);
	}
}

void MinHeap::Insert(int index, int masa)
{
	int length = _vector.size()-1;

	cout << endl << "AA" << endl << tablica[index] << endl;

	_vector[index].masa += masa;

	BubbleDown(index);
	//BubbleDown(tablica[index]);
	//Heapify();
}

elewator MinHeap::GetMin()
{
	//for(int i = 0;i<_vector.size();i++){
	return _vector[0];
}

int MinHeap::GetMinI()
{
	//for(int i = 0;i<_vector.size();i++){
	return tablica[0];
}

int MinHeap::GetMaxI()
{
	int id = 0;
	elewator max = _vector[0];
	for (size_t i = 0; i < _vector.size(); i++)
	{
		if (_vector[i] > max) {
			max = _vector[i];
			id = i;
		}
	}
	return id;
}

elewator MinHeap::GetMax()
{
	elewator max = _vector[0];

	for (size_t i = 0; i < _vector.size(); i++)
	{
		if (_vector[i] > max) {
			max = _vector[i];
		}
	}
	return max;
}

void MinHeap::DeleteMin()
{
	int length = _vector.size();

	if (length == 0)
	{
		return;
	}

	_vector[0] = _vector[length - 1];
	_vector.pop_back();

	BubbleDown(0);
}

void MinHeap::nX(int numer, long int masa) {
	
}
void MinHeap::nm(long int masa) {

}
void MinHeap::nM(long int masa) {

}
void MinHeap::r(int numer, long int masa) {
	
}
void MinHeap::rm(long int masa) {

}
void MinHeap::rM(long int masa) {

}
void MinHeap::w(int numer) {

}
void MinHeap::wm() {

}
void MinHeap::wM() {
	
}




int main()
{

	int n;///liczba elewatorow
	int m;//liczba operacji
	cin >> n;
	cin >> m;
	char *token;

	elewator * elewatory = new elewator[n];

	for (int i = 0; i < n; i++) {
		elewator x;
		unsigned long int masa;
		cin >> masa;
		x.masa = masa;
		x.numer = i;
		elewatory[i] = x;
	}

	//make_h(elewatory, n);


	MinHeap minHeap(elewatory, n);
	cout << minHeap.GetMin().masa << "  ";
	cout << minHeap.GetMax().masa << "  ";
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << i << ":" << minHeap._vector[i].masa << "\t" << minHeap.tablica[i] << "\t" << minHeap.tablica_n_v[i] << endl;
	}
	cout << endl << endl;
	minHeap.Insert(minHeap.GetMaxI(), 5);
	cout << minHeap.GetMin().masa << "  ";
	cout << minHeap.GetMax().masa << "  ";
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << i << ":" << minHeap._vector[i].masa << "\t" << minHeap.tablica[i] << "\t" << minHeap.tablica_n_v[i] << endl;
	}
	char x;
	std::cin >> x;

    return 0;
}

