#include "vector"
#include <iostream>
using namespace std;


void nX(int numer, long int masa);
void nm(long int masa);
void nM(long int masa);
void r(int numer, long int masa);
void rm(long int masa);
void rM(long int masa);
void w(int numer);
void wm();
void wM();

struct elewator {
	long int masa;
	unsigned long int numer;
	int posMin;
	int posMax;
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

elewator ** minHeap;
elewator ** maxHeap;
elewator * elewatory;

void GoDown(int index, int size) {
	int leftIndex = 2 * index + 1;
	if (leftIndex >= size) {
		return;
	}
	int rightIndex = 2 * index + 2;
	int minIndex = index;
	
	if ((*minHeap[index]).masa > (*minHeap[leftIndex]).masa) {
		minIndex = leftIndex;
	}
	if ((*minHeap[index]).masa == (*minHeap[leftIndex]).masa) {
		if ((*minHeap[index]).numer > (*minHeap[leftIndex]).numer) {
			minIndex = leftIndex;
		}
	}
	if (rightIndex<size&&(*minHeap[index]).masa > (*minHeap[rightIndex]).masa) {
		minIndex = rightIndex;
	}
	if (rightIndex<size && (*minHeap[index]).masa == (*minHeap[rightIndex]).masa) {
		if ((*minHeap[index]).numer >(*minHeap[rightIndex]).numer) {
			minIndex = rightIndex;
		}
	}
	if ((*minHeap[index]).masa == 0) {
		minIndex = size - 1;
	}
	if (minIndex != index) {
		(*minHeap[index]).posMin = minIndex;
		(*minHeap[minIndex]).posMin = index;
		swap(minHeap[index], minHeap[minIndex]);
		GoDown(minIndex,size);
	}
}
void GoUp(int index) {

}

int main()
{

	int n;///liczba elewatorow
	int m;//liczba operacji
	cin >> n;
	cin >> m;
	char *token;

	elewatory = new elewator[n];
	minHeap = new elewator*[n*n];
	maxHeap = new elewator*[n*n];

	for (size_t i = 0; i < n; i++)
	{
		minHeap[i] = new elewator();
		maxHeap[i] = new elewator();
	}

	for (int i = 0; i < n; i++) {
		elewator x;
		unsigned long int masa;
		cin >> masa;
		x.masa = masa;
		x.numer = i;
		x.posMin = i;
		x.posMax = i;
		elewatory[i] = x;
		minHeap[i] = &elewatory[i];
		maxHeap[i] = &elewatory[i];
	}
	for (size_t i = 0; i < n; i++)
	{
		GoDown(i, n);
	}
	for (int i = 0; i < n; i++)
	{
		cout << i << ":" << (*minHeap[i]).masa << "\t m " << (*minHeap[i]).posMin << "\t M" << (*minHeap[i]).posMax << endl;
	}
	return 0;
}