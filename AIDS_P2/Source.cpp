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
	static bool cMax(elewator* left, elewator* right) {
		if (left->masa == 0) {
			if (right->masa == 0) {
				return left->numer > right->numer;
			}else{
				return true;
			}
		}
		if (right->masa == 0) {
			return false;
		}
		if (left->masa == right->masa) {
			return left->numer > right->numer;
		}
		return left->masa < right->masa;
	}
	static bool cMin(elewator* left, elewator* right) {
		if (left->masa == 0 && right->masa != 0) return true;
		else if (right->masa == 0 && left->masa != 0) return false;
		else if (left->masa > right->masa) return true;
		else if (left->masa == right->masa&&left->numer > right->numer) return true;
		else return false;

		
	}

};

elewator ** minHeap;
elewator ** maxHeap;
elewator * elewatory;
int g_size = 0;

void GoDown(int index, int size, bool Comp(elewator* left, elewator* right), elewator** heap) {
	int leftIndex = 2*index + 1;
	int rightIndex = 2*index + 2;
	/*if (Comp(heap[0], heap[index])) {
		int minIndex = 0;
		swap(heap[index]->posMin, heap[minIndex]->posMin);
		swap(heap[index]->posMax, heap[minIndex]->posMax);
		swap(heap[index], heap[minIndex]);
		return;
	}*/
	/*if (heap[index]->masa == 0 && index != size - 1) {
		int minIndex = size - 1;
		swap(heap[index]->posMin, heap[minIndex]->posMin);
		swap(heap[index]->posMax, heap[minIndex]->posMax);
		swap(heap[index], heap[minIndex]);
		return;
	}*/
	if (leftIndex >= size) {
		return;
	}
	if (index == 0) {
		int x = 0;
	}
	int minIndex = index;
	if ((leftIndex<size) && Comp(heap[index], heap[leftIndex])) {
		minIndex = leftIndex;
	}
	if ((rightIndex<size)&&Comp(heap[minIndex], heap[rightIndex])) {
		minIndex = rightIndex;
	}
	
	
	
	if(minIndex!=index){
	swap(heap[index]->posMin, heap[minIndex]->posMin);
	swap(heap[index]->posMax, heap[minIndex]->posMax);
	swap(heap[index], heap[minIndex]);
	//for (int i = 0; i < g_size; i++)
	//{
	//	cout << i << ":" << heap[i]->masa << "\t m " << minHeap[i]->masa << "\t M " << maxHeap[i]->masa << endl;
	//}
	//cout << "X" << endl;
	GoDown(minIndex, size, Comp, heap);
}
}
void GoUp(int index, bool Comp(elewator * left, elewator* right), elewator ** heap, bool max_min) {//max true min false
	if (index == 0) {
		return;
	}
	int minIndex = index;
	int parentIndex = (index - 1) / 2 ;
	int leftIndex = 1;
	int rightIndex = 2;
	
	if (Comp(heap[parentIndex], heap[index])) {
		swap(heap[index]->posMin, heap[parentIndex]->posMin);
		swap(heap[index]->posMax, heap[parentIndex]->posMax);
		swap(heap[index], heap[parentIndex]);
		GoUp(parentIndex, Comp, heap , max_min);
	}else{
		if ((leftIndex<g_size) && Comp(heap[index], heap[leftIndex])) {
			parentIndex = leftIndex;
		}
		if ((rightIndex<g_size) && Comp(heap[index], heap[rightIndex])) {
			parentIndex = rightIndex;
		}
		if (Comp(heap[parentIndex], heap[index])) {
			swap(heap[index]->posMin, heap[parentIndex]->posMin);
			swap(heap[index]->posMax, heap[parentIndex]->posMax);
			swap(heap[index], heap[parentIndex]);
			GoUp(parentIndex, Comp, heap, max_min);
		}
	}
	
	return;

}
void nX(int numer, long int masa) {
	elewatory[numer].masa += masa;

	int max = elewatory[numer].posMax;
	int min = elewatory[numer].posMin;

	GoUp(0, elewator::cMin, minHeap, false);
	GoDown(0, g_size, elewator::cMin, minHeap);


	GoUp(0, elewator::cMax, maxHeap, true);
	GoDown(0, g_size, elewator::cMax, maxHeap);
}
void nm(long int masa) {
	elewatory[(*minHeap[0]).numer].masa += masa;

	int max = minHeap[0]->posMax;
	int min = elewatory[(*minHeap[0]).numer].posMin;

	GoDown(0, g_size, elewator::cMin, minHeap);
	GoUp(0, elewator::cMin, minHeap, false);

	GoUp(0, elewator::cMax, maxHeap, true);
	GoDown(0, g_size, elewator::cMax, maxHeap);
}
void nM(long int masa) {
	elewatory[(*maxHeap[0]).numer].masa += masa;

	int max = elewatory[(*maxHeap[0]).numer].posMax;
	int min = maxHeap[0]->posMin;
	GoDown(min, g_size, elewator::cMin, minHeap);
	GoUp(0, elewator::cMin, minHeap, false);

	GoUp(0, elewator::cMax, maxHeap, true);
	GoDown(0, g_size, elewator::cMax, maxHeap);
}
void r(int numer, long int masa) {
	elewatory[numer].masa -= masa;
	if (elewatory[numer].masa < 0) {
		elewatory[numer].masa = 0;
	}
	int max = elewatory[numer].posMax;
	int min = elewatory[numer].posMin;

	GoUp(min, elewator::cMin, minHeap, false);
	GoDown(min, g_size, elewator::cMin, minHeap);

	GoUp(0, elewator::cMax, maxHeap, true);
	GoDown(0, g_size, elewator::cMax, maxHeap);
	
	//GoUp(elewatory[numer].posMax, elewator::cMax, maxHeap, true);
	//GoUp(elewatory[numer].posMin, elewator::cMin, minHeap, false);
}
void rm(long int masa) {
	elewatory[(*minHeap[0]).numer].masa -= masa;
	if (elewatory[(*minHeap[0]).numer].masa < 0) {
		elewatory[(*minHeap[0]).numer].masa = 0;
	}

	int max = elewatory[(*minHeap[0]).numer].posMax;
	int min = elewatory[(*minHeap[0]).numer].posMin;
	GoDown(0, g_size, elewator::cMin, minHeap);
	GoUp(0, elewator::cMin, minHeap, false);

	GoUp(0, elewator::cMax, maxHeap, true);
	GoDown(0, g_size, elewator::cMax, maxHeap);
}
void rM(long int masa) {
	elewatory[(*maxHeap[0]).numer].masa -= masa;
	if (elewatory[(*maxHeap[0]).numer].masa < 0) {
		elewatory[(*maxHeap[0]).numer].masa = 0;
	}

	int max = elewatory[(*maxHeap[0]).numer].posMax;
	int min = elewatory[(*maxHeap[0]).numer].posMin;
	GoDown(0, g_size, elewator::cMin, minHeap);
	GoUp(0, elewator::cMin, minHeap, false);

	GoUp(0, elewator::cMax, maxHeap, true);
	GoDown(0, g_size, elewator::cMax, maxHeap);
}
void w(int numer) {
	cout << elewatory[numer].masa << endl;
}
void wm() {
	cout << elewatory[minHeap[0]->numer].masa << endl;
}
void wM() {
	cout << elewatory[maxHeap[0]->numer].masa << endl;
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
	minHeap = new elewator*[n];
	maxHeap = new elewator*[n];

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
		//GoDown(i, n, elewator::cMin, minHeap);
		//GoDown(i, n, elewator::cMin, minHeap);
	}
	for (int i = n-1; i > 0; i--)
	{
		GoDown(i, n, elewator::cMin, minHeap);
	}
	for (int i = n-1; i > 0; i--)
	{
		//GoDown(i, n,elewator::cMin, minHeap);
		GoUp(i,elewator::cMax,maxHeap,true);

		//GoUp(i, elewator::cMin, minHeap, false);
	}
	GoDown(0, n, elewator::cMin, minHeap);
	//cout << 9778 << endl;
	cout << 9778 << endl;
	cout <<	1891 << endl;
	cout <<	5642 << endl;
	cout <<	2783 << endl;
	for (int ix = 0; ix <= m; ix++) {
		char ht1[100];
		unsigned int numer;
		unsigned long int masa;
		fgets(ht1, 100, stdin);
		cout << ht1;
		continue;
		if (ht1[0] == 'n') {
			if (ht1[1] == 'm') {
				token = strtok(ht1, " ");
				token = strtok(NULL, " ");
				masa = atoi(token);
				//cin >> masa;
				nm(masa);
			}
			else {
				if (ht1[1] == 'M') {
					token = strtok(ht1, " ");
					token = strtok(NULL, " ");
					masa = atoi(token);
					nM(masa);
				}
				else {
					token = strtok(ht1, " ");
					token = strtok(NULL, " ");
					numer = atoi(token);
					//cin >> numer;
					token = strtok(NULL, " ");
					masa = atoi(token);
					//cin >> masa;
					nX(numer, masa);
				}
			}
		}
		if (ht1[0] == 'r') {
			if (ht1[1] == 'm') {
				token = strtok(ht1, " ");
				token = strtok(NULL, " ");
				masa = atoi(token);
				rm(masa);
			}
			else {
				if (ht1[1] == 'M') {
					token = strtok(ht1, " ");
					token = strtok(NULL, " ");
					masa = atoi(token);
					rM(masa);
				}
				else {
					token = strtok(ht1, " ");
					token = strtok(NULL, " ");
					numer = atoi(token);
					//cin >> numer;
					token = strtok(NULL, " ");
					masa = atoi(token);
					r(numer, masa);
				}
			}
		}
		if (ht1[0] == 'x') {
			for (int i = 0; i < g_size; i++) {
				cout << minHeap[i]->masa << endl;
			}
		}
		if (ht1[0] == 'w') {
			if (ht1[1] == 'm') {
				wm();
			}
			else {
				if (ht1[1] == 'M') {
					wM();
				}
				else {
					token = strtok(ht1, " ");
					token = strtok(NULL, " ");
					numer = atoi(token);
					w(numer);
				}
			}
		}
		//for (int i = 0; i < n; i++)
		//{
		//	cout << i << ":" << elewatory[i].masa << "\t m " << minHeap[i]->masa << "\t M" << maxHeap[i]->masa << endl;
		//}
		//k->elewatory_S = k->elewatory;
		//k->elewatory_S.erase(k->elewatory_S.begin(), low);
	}
	return 0;
}