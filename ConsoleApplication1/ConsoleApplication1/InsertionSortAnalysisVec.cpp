#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#include <windows.h>
#include <fstream>
#include<vector>

LARGE_INTEGER frequency;        // ticks per second
LARGE_INTEGER t1, t2;           // ticks
double elapsedTime;

using namespace std;

ofstream f;

void initRandArr(vector<unsigned long> arr, vector<unsigned long>::size_type n)
{
	
	//Random number generator by shuffling http://ideone.com/qU00S4
	cout << n;
	if (n >= 1)
	{
		for (vector<unsigned long>::size_type i = 0; i < n; i++) {
			arr[i] = (i + 1);
			cout << " " << *i + 1 << " ";
		}
		srand(time(NULL));
		for (vector<unsigned long>::iterator i = arr.begin()+1; i != arr.end(); i++)
		{
			vector<unsigned long>::size_type j = i + rand() / (RAND_MAX / (arr.size() - i) + 1);
			vector<unsigned long>::size_type t = arr[j];
			arr[j] = arr[i];
			arr[i] = t;
		}
	}
}

void printArr(vector<unsigned long> arr) {
	cout << "{";
	for (vector<unsigned long>::size_type i = 0; i < arr.size(); i++)
		cout << arr[i] << ", ";
	cout << "}" << endl;
}
void insSort(vector<unsigned long> arr) {
	vector<unsigned long>::size_type key, j, i;
	for (i = 1; i < arr.size(); i++) {
		j = i;
		while (j > 0 && arr[j - 1] > arr[j]) {
			key = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = key;
			j--;
		}
	}
}
void saveOutput(string str) {
	f << str;
}


void RunExpr(vector<unsigned long> arr,vector<unsigned long>::size_type n, vector<unsigned long>::size_type sede, vector<unsigned long>::size_type step) {
	sede += step;
	if (sede > n) {
		return;
	}
	else {
		
		initRandArr(arr, sede);
		QueryPerformanceCounter(&t1); //Start Time
		//Insertion Sort
		printArr(arr);
		insSort(arr);
		QueryPerformanceCounter(&t2); //End time
		elapsedTime = trunc((t2.QuadPart - t1.QuadPart) * 1000000.0 / frequency.QuadPart); //Time Taken
		saveOutput(to_string(sede) + (string)"\t" + to_string(elapsedTime) + "\n");
		RunExpr(arr, n, sede, step);
	}
	
}


int main() {
	srand(time(NULL));
	QueryPerformanceFrequency(&frequency);
	
	vector<unsigned long>::size_type n, step;
	//Input
	cout << "Enter n in T(n): ";
	cin >> n;
	cout << "Enter the step size for n: ";
	cin >> step;
	cout<< endl;
	//Output
	cout << "Writing Values to File";
	f.open("data.txt", ios::out | ios::app);
	saveOutput("N\t T(n)\n");
	vector<unsigned long> arr(n);
	//initNearlySorted(arr, n);

	//RunExpr(arr, n, 0, step);
	f.close();
	system("pause");


}
