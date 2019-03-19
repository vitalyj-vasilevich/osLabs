#include <iostream>
#include <windows.h>
#include <process.h>

using namespace std;

class Array {
public:
	int* array;
	int zeroCount;
	int size;
	Array(int size = 10)
	{
		array = new int[size];
		zeroCount = 0;
		this->size = size;
	}
	~Array()
	{
		delete[] array;
	}
};

DWORD WINAPI worker(LPVOID obj)
{
	Array* a = (Array*)obj;
	for (int i = 0; i < a->size; i++)
	{
		if (a->array[i] == 0)
		{
			a->zeroCount++;
		}
	}
	return 00;
}

DWORD WINAPI count(LPVOID obj)
{
	int first = 0;
	int second = 1;
	int third;
	cout << first << endl;
	Sleep(500);
	cout << second << endl;
	Sleep(500);
	while (true)
	{
		third = first + second;
		cout << third << endl;
		Sleep(500);
		first = second;
		second = third;
	}
	return 0;
}

int main()
{
	DWORD sleepTime;
	HANDLE hWorker;
	HANDLE hCount;
	DWORD IDWorker;
	DWORD IDCount;
	int sz = 0;
	cout << "Input a size of the array: " << endl;
	cin >> sz;
	Array* arr = new Array(sz);
	for (int i = 1; i < sz; ++i)
	{
		arr->array[i] = rand() % 10 - 5;
	}
	cout << "Origin array: \n";
	for (int i = 0; i < sz; ++i)
	{
		cout << arr->array[i] << ' ';
	}
	hWorker = CreateThread(NULL, 0, worker, arr, 0, &IDWorker);
	hCount = CreateThread(NULL, 0, count, NULL, CREATE_SUSPENDED, &IDCount);
	if (hWorker == NULL || hCount == NULL)
		return GetLastError();
	SuspendThread(hWorker);
	Sleep(1000);
	ResumeThread(hWorker);
	WaitForSingleObject(hWorker, INFINITE);
	CloseHandle(hWorker);
	cout << "zeros in array: " << arr->zeroCount << endl;
	ResumeThread(hCount);
	WaitForSingleObject(hCount, INFINITE);
	CloseHandle(hCount);
	system("pause");
	return 0;
}