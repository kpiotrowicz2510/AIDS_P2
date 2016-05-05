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
int g_size = 0;

void GoDown(int index, int size) {
	if (index <= 0) {
		return;
	}
	int leftIndex = index - 1;

	int rightIndex = index - 1;
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

	if ((*minHeap[0]).masa == 0) {
		minIndex = size - 1;
		swap((*minHeap[0]).posMin, (*minHeap[minIndex]).posMin);
		swap(minHeap[0], minHeap[minIndex]);
		GoDown(0, size);
		return;
	}
	if (minIndex != index) {
		swap((*minHeap[index]).posMin, (*minHeap[minIndex]).posMin);
		swap(minHeap[index], minHeap[minIndex]);
		GoDown(minIndex,size);
	}
}
void GoUp(int index) {
	if (index == 0)
		return;

	int parentIndex = index - 1;

	//if ((*minHeap[parentIndex]) > (*minHeap[index]))
	//{
	//	swap((*minHeap[index]).posMin, (*minHeap[parentIndex]).posMin);
	//	swap(minHeap[index], minHeap[parentIndex]);
	//	GoUp(parentIndex);
	//}
	if ((*maxHeap[index]).masa == 0) {
		int minIndex = g_size - 1;
		swap((*maxHeap[index]).posMax, (*maxHeap[minIndex]).posMax);
		swap(maxHeap[index], maxHeap[minIndex]);
		return;
	}
	if ((*maxHeap[parentIndex]) > (*maxHeap[index]))
	{
		swap((*maxHeap[index]).posMax, (*maxHeap[parentIndex]).posMax);
		swap(maxHeap[index], maxHeap[parentIndex]);
		GoUp(parentIndex);
	}

}

int main()
{

	int n;///liczba elewatorow
	int m;//liczba operacji
	cin >> n;
	cin >> m;
	char *token;
	g_size = n;
	elewatory = new elewator[n];
	minHeap = new elewator*[n*n];
	maxHeap = new elewator*[n*n];

	for (size_t i = 0; i < n*n; i++)
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
	for (size_t i = n-1; i > 0; i--)
	{
		GoDown(i, n);
		GoUp(i);
	}
	for (int i = 0; i < n; i++)
	{
		cout << i << ":" << elewatory[i].masa << "\t m " << elewatory[i].posMin << "\t M" << elewatory[i].posMax << endl;
	}
	return 0;
}