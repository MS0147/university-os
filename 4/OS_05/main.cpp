#pragma once
#include"Page.h"
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
using namespace std;

void printarr(int* arr, int index);
void fifo(int* arr);
void lru(int* arr);
void opt(int* arr);

int main()
{	
	int select;
	srand((unsigned int)time(NULL));
	int arr[50];
	for (int i = 0; i < 50; i++)
	{
		arr[i] = rand() % 50;
	}

	cout << "1. FIFO\n2. LRU\n3. Optimal\n>> ";
	cin >> select;
	switch (select)
	{
	case 1:
		system("cls");
		fifo(arr);
		break;
	case 2:
		system("cls");
		lru(arr);
		break;
	case 3:
		system("cls");
		opt(arr);
		break;
	default:
		system("cls");
		cout << "유효한 값이 아닙니다." << endl;
		break;
	}

	cout << "Program is finish!" << endl << endl;
	system("pause");
	return 0;
}

void printarr(int* arr, int index)
{
	cout << ">> Reference string" << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (10 * i + j == index)
				cout << setw(5) << '(' << arr[i * 10 + j] << ')';
			else
				cout << setw(5) << arr[i * 10 + j];
		}
		cout << endl << endl;
	}
}

void fifo(int* arr)
{
	FIFO x;
	for (int i = 0; i < 50; i++)
	{
		printarr(arr, i);
		x.insert(arr[i]);
		x.print();
		system("pause");
		system("cls");
	}
}

void lru(int* arr)
{
	LRU x;
	for (int i = 0; i < 50; i++)
	{
		printarr(arr, i);
		x.insert(arr[i]);
		x.print();
		system("pause");
		system("cls");
	}
}

void opt(int* arr)
{
	Optimal x;
	for (int i = 0; i < 50; i++)
	{
		printarr(arr, i);
		x.insert(arr[i], arr+i, 50-i);
		x.print();
		system("pause");
		system("cls");
	}
}