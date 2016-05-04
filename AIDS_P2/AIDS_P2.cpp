// AIDS_P2.cpp : Defines the entry point for the console application.
//
#include "vector"
#include <iostream>
using namespace std;

struct elewator {
	long int masa;
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
	int max_id;
	int max_masa;
};

MinHeap::MinHeap(elewator* array, int length) : _vector(length)
{
	zero_count = 0;
	tablica = new int[length];
	tablica_n_v = new int[length];
	max_id = 0;
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
		if (_vector[i].masa > max_masa) {
			max_id = i;
			max_masa = _vector[i].masa;
		}
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
		
		
		BubbleDown(i);
		//cout << "t:" << tablica[i] << endl;
		//cout << "t2:" << tablica_n_v[i] << endl;
	}
	
}

void MinHeap::BubbleDown(int index)
{
	for (int i = 0; i < _vector.size(); i++)
	{
		cout << i << ":" << _vector[i].masa << "\t" << tablica[i] << "\t" << tablica_n_v[i] << endl;
	}
	int length = _vector.size();
	int parentIndex = (index - 1) / 2;
	int leftChildIndex = 2 * index;
	int rightChildIndex = 2 * index + 1;
	if (_vector[0].masa == 0&& _vector[_vector.size() - 1].masa!=0) {
		swap(_vector[0], _vector[_vector.size() - 1]);
		swap(tablica[0], tablica[_vector.size() - 1]);
		swap(tablica_n_v[tablica[0]], tablica_n_v[tablica[_vector.size() - 1]]);
		BubbleDown(0);
	}
	if (leftChildIndex >= length) {
		return; //index is a leaf
	}
	if (_vector[index].masa > _vector[max_id].masa) {
		max_id = index;
		max_masa = _vector[index].masa;
	}
	if (_vector[leftChildIndex].masa > _vector[max_id].masa) {
		max_id = leftChildIndex;
		max_masa = _vector[leftChildIndex].masa;
	}
	if ((rightChildIndex < length) && _vector[rightChildIndex].masa > _vector[max_id].masa) {
		max_id = rightChildIndex;
		max_masa = _vector[rightChildIndex].masa;
	}
	if (_vector[parentIndex].masa == 0) {
		if (_vector[parentIndex].masa == 0 && _vector[index].masa > _vector[parentIndex].masa) {
			swap(_vector[index], _vector[parentIndex]);
			swap(tablica[index], tablica[parentIndex]);
			swap(tablica_n_v[tablica[index]], tablica_n_v[tablica[parentIndex]]);
			return;
		}
		if ((leftChildIndex < length) && _vector[index].masa < _vector[leftChildIndex].masa) {
			swap(_vector[index], _vector[leftChildIndex]);
			swap(tablica[index], tablica[leftChildIndex]);
			swap(tablica_n_v[tablica[index]], tablica_n_v[tablica[leftChildIndex]]);
			return;
		}
		if ((rightChildIndex < length) && _vector[index].masa < _vector[rightChildIndex].masa) {
			swap(_vector[index], _vector[rightChildIndex]);
			swap(tablica[index], tablica[rightChildIndex]);
			swap(tablica_n_v[tablica[index]], tablica_n_v[tablica[rightChildIndex]]);
			return;
		}
		if (_vector[index].masa == 0) {
			swap(_vector[index], _vector[_vector.size() - 1]);
			swap(tablica[index], tablica[_vector.size() - 1]);
			swap(tablica_n_v[tablica[index]], tablica_n_v[tablica[_vector.size() - 1]]);
			return;
		}
	}
	else {
		if (_vector[index].masa == 0) {
			swap(_vector[index], _vector[_vector.size() - 1]);
			swap(tablica[index], tablica[_vector.size() - 1]);
			swap(tablica_n_v[index], tablica_n_v[_vector.size() - 1]);
			return;
		}
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

		//if (temp.masa == 0) {
		//	swap(_vector[index], _vector[_vector.size() - 1]);
		//	swap(tablica[index], tablica[_vector.size() - 1]);
		//	swap(tablica_n_v[tablica[rightChildIndex]], tablica_n_v[_vector[_vector.size() - 1].numer]);
		//	return;
		//}

		//int temp3 = tablica[index];
		//int temp2 = index;

		//_vector[index] = _vector[minIndex];
		//tablica[index] = _vector[minIndex].numer;
		//tablica_n_v[_vector[index].numer] = minIndex;
		swap(_vector[index],_vector[minIndex]);
		swap(tablica[index], tablica[minIndex]);
		swap(tablica_n_v[tablica[index]], tablica_n_v[tablica[minIndex]]);
		//cout << "X" << endl;

		//_vector[minIndex] = temp;
		//tablica[minIndex] = temp3;
		//tablica_n_v[minIndex] = index;
		//tablica_n_v[_vector[minIndex].numer] = index;
		BubbleDown(minIndex);
	}
}

void MinHeap::BubbleUp(int index)
{
	if (index == 0)
		return;
	if (_vector[index].masa > _vector[max_id].masa) {
	//	max_id = index;
	}
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


		BubbleUp(parentIndex);
	}
}

void MinHeap::Insert(int index, int masa)
{
	int length = _vector.size()-1;

	//cout << endl << "AA" << endl << tablica[index] << endl;

	_vector[index].masa += masa;
	if (_vector[index].masa < 0) {
		_vector[index].masa = 0;
		BubbleDown(index);
		return;
	}
	BubbleDown(index);
	
	//BubbleDown(tablica[index]);
	//Heapify();
}

elewator MinHeap::GetMin()
{
	//for(int i = 0;i<_vector.size();i++){
	return _vector[tablica[0]];
}

int MinHeap::GetMinI()
{
	//for(int i = 0;i<_vector.size();i++){
	return tablica[0];
}

int MinHeap::GetMaxI()
{
	int id = 0;
	return max_id;
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
	return _vector[max_id];
	for (size_t i = 0; i < _vector.size(); i++)
	{
		if (_vector[i].masa > max.masa) {
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
	Insert(tablica_n_v[numer], masa);
}
void MinHeap::nm(long int masa) {
	Insert(GetMinI(), masa);
}
void MinHeap::nM(long int masa) {
	Insert(GetMaxI(), masa);
}
void MinHeap::r(int numer, long int masa) {
	Insert(tablica_n_v[numer], -masa);
}
void MinHeap::rm(long int masa) {
	Insert(GetMinI(), -masa);
}
void MinHeap::rM(long int masa) {
	Insert(GetMaxI(), -masa);
}
void MinHeap::w(int numer) {
	cout << _vector[tablica_n_v[numer]].masa << endl;
}
void MinHeap::wm() {
	cout << _vector[0].masa << endl;
}
void MinHeap::wM() {
	cout << GetMax().masa << endl;
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
	//cout << minHeap.GetMin().masa << "  ";
	//cout << minHeap.GetMax().masa << "  ";
	//cout << endl;
	//for (int i = 0; i < n; i++)
	//{
	//	cout << i << ":" << minHeap._vector[i].masa << "\t" << minHeap.tablica[i] << "\t" << minHeap.tablica_n_v[i] << endl;
	//}
	//cout << endl << endl;
	//minHeap.Insert(minHeap.GetMaxI(), 5);
	//cout << minHeap.GetMin().masa << "  ";
	//cout << minHeap.GetMax().masa << "  ";
	//cout << endl;
	//for (int i = 0; i < n; i++)
	//{
	//	//cout << i << ":" << minHeap._vector[i].masa << "\t" << minHeap.tablica[i] << "\t" << minHeap.tablica_n_v[i] << endl;
	//}

	for (int ix = 0; ix <= m; ix++) {
		char ht1[100];
		unsigned int numer;
		unsigned long int masa;
		fgets(ht1, 100, stdin);
		//cout << ht1;
		//continue;
		if (ht1[0] == 'n') {
			if (ht1[1] == 'm') {
				token = strtok(ht1, " ");
				token = strtok(NULL, " ");
				masa = atoi(token);
				//cin >> masa;
				minHeap.nm(masa);
			}
			else {
				if (ht1[1] == 'M') {
					token = strtok(ht1, " ");
					token = strtok(NULL, " ");
					masa = atoi(token);
					minHeap.nM(masa);
				}
				else {
					token = strtok(ht1, " ");
					token = strtok(NULL, " ");
					numer = atoi(token);
					//cin >> numer;
					token = strtok(NULL, " ");
					masa = atoi(token);
					//cin >> masa;
					minHeap.nX(numer, masa);
				}
			}
		}
		if (ht1[0] == 'r') {
			if (ht1[1] == 'm') {
				token = strtok(ht1, " ");
				token = strtok(NULL, " ");
				masa = atoi(token);
				minHeap.rm(masa);
			}
			else {
				if (ht1[1] == 'M') {
					token = strtok(ht1, " ");
					token = strtok(NULL, " ");
					masa = atoi(token);
					minHeap.rM(masa);
				}
				else {
					token = strtok(ht1, " ");
					token = strtok(NULL, " ");
					numer = atoi(token);
					//cin >> numer;
					token = strtok(NULL, " ");
					masa = atoi(token);
					minHeap.r(numer, masa);
				}
			}
		}
		if (ht1[0] == 'w') {
			if (ht1[1] == 'm') {
				minHeap.wm();
			}
			else {
				if (ht1[1] == 'M') {
					minHeap.wM();
				}
				else {
					token = strtok(ht1, " ");
					token = strtok(NULL, " ");
					numer = atoi(token);
					minHeap.w(numer);
				}
			}
		}

		//k->elewatory_S = k->elewatory;
		//k->elewatory_S.erase(k->elewatory_S.begin(), low);
	}
	

    return 0;
}

