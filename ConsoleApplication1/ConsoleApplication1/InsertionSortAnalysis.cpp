#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#include <windows.h>
#include <fstream>
#include<vector>

#define S_AVG 1
#define S_BEST 2
#define S_WORST 3

LARGE_INTEGER frequency;        // ticks per second
LARGE_INTEGER t1, t2;           // ticks
double elapsedTime;

using namespace std;

ofstream f;

void initNearlySortedvec(vector<unsigned long>& vec, vector<unsigned long>::size_type n)
{

	//Random number generator by shuffling http://ideone.com/qU00S4
	if (n >= 1)
	{
		for (vector<unsigned long>::size_type i = 0; i < n; i++) {
			vec[i] = i + 1;
		}
		srand(time(NULL));
		int k = rand() % n;
		while (k) {
			for (vector<unsigned long>::size_type i = (rand() % n); i < n - i; i++)
			{
				vector<unsigned long>::size_type j = i + rand() / (RAND_MAX / (vec.size() - i) + 1);
				vector<unsigned long>::size_type t = vec[j];
				vec[j] = vec[i];
				vec[i] = t;
			}
			k--;
		}
		
		
	}
}

void initWorstvec(vector<unsigned long>& vec, vector<unsigned long>::size_type n)
{

	//Random number generator by shuffling http://ideone.com/qU00S4
	if (n >= 1)
	{
		for (vector<unsigned long>::size_type i = 0; i < n; i++) {
			vec[i] = n - i;
		}
		srand(time(NULL));
		for (vector<unsigned long>::size_type i = (rand() % n); i < n - i; i++)
		{
			vector<unsigned long>::size_type j = i + rand() / (RAND_MAX / (vec.size() - i) + 1);
			vector<unsigned long>::size_type t = vec[j];
			vec[j] = vec[i];
			vec[i] = t;
		}


	}
}

void initRandvec(vector<unsigned long>& vec, vector<unsigned long>::size_type n)
{
	
	//Random number generator by shuffling http://ideone.com/qU00S4
	if (n >= 1)
	{
		for (vector<unsigned long>::size_type i = 0; i < n; i++) {
			vec[i] = i + 1;
		}
		srand(time(NULL));

		for (vector<unsigned long>::size_type i = 1; i < n; i++)
		{
			vector<unsigned long>::size_type j = i + rand() / (RAND_MAX / (vec.size() - i) + 1);
			vector<unsigned long>::size_type t = vec[j];
			vec[j] = vec[i];
			vec[i] = t;
		}
	}
}

void printvec(vector<unsigned long> vec) {
	cout << "{";
	for (vector<unsigned long>::size_type i = 0; i < vec.size(); i++)
		cout << vec[i] << ", ";
	cout << "}" << endl;
}

void insSort(vector<unsigned long>& vec) {
	vector<unsigned long>::size_type key, j, i;
	for (i = 1; i < vec.size(); i++) {
		j = i;
		while (j > 0 && vec[j - 1] > vec[j]) {
			key = vec[j];
			vec[j] = vec[j - 1];
			vec[j - 1] = key;
			j--;
		}
	}
}
void saveOutput(string str) {
	f << str;
}


void RunExpr(vector<unsigned long>& vec,vector<unsigned long>::size_type n, vector<unsigned long>::size_type sede, vector<unsigned long>::size_type step, unsigned int cases) {
	sede += step;
	if (sede > n) {
		return;
	}
	else {
		switch (cases) {
		case 1: initRandvec(vec, sede);  break;
		case 2: initNearlySortedvec(vec, sede); break;
		case 3: initWorstvec(vec, sede); break;
		default: initRandvec(vec, sede); 
		}
		
	}
	QueryPerformanceCounter(&t1); //Start Time
	//Insertion Sort
	insSort(vec);
	QueryPerformanceCounter(&t2); //End time
	elapsedTime = trunc((t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart); //Time Taken
	saveOutput(to_string(sede) + (string)"\t" + to_string(elapsedTime) + "\n"); //output to file
	RunExpr(vec, n, sede, step, cases); // rerun
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
	vector<unsigned long> vec(n);

	//-------------------------------------------------
	saveOutput("Average Case \n\t T(n)\n");
	RunExpr(vec, n, 0, step, S_AVG);
	saveOutput("Best Case\n\t T(n)\n");
	RunExpr(vec, n, 0, step, S_BEST);
	saveOutput("Worst Case\n\t T(n)\n");
	RunExpr(vec, n, 0, step, S_WORST);
	f.close();
	system("pause");


}
