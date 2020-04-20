#pragma once
#include"Page.h"
#include<iostream>
#include<iomanip>
using namespace std;


FIFO::FIFO()
{
	frame_size = FRAME_SIZE;
	frame = new int[frame_size];
	for (int i = 0; i < frame_size; i++)
		frame[i] = -1;
	index = 0;
}

void FIFO::insert(int item)
{
	bool there = this->find(item);
	if (!there)
	{
		frame[index] = item;
		index = (index + 1) % frame_size;
	}
}

void FIFO::print()
{
	cout << ">> FIFO <<\n\n";
	cout << ">> 현재 사용중인 페이지는 다음과 같습니다." << endl << endl;
	for (int i = 0; i < frame_size; i++)
	{
		if (i != (index+frame_size-1)%frame_size)
			cout << setw(7) << frame[i];
		else
			cout << setw(7) << '(' << frame[i] << ')';
	}
	cout << endl << endl;
}

bool FIFO::find(int item)
{
	for (int i = 0; i < frame_size; i++)
	{
		if (frame[i] == item)
			return true;
	}
	return false;
}



LRU::LRU()
{
	frame_size = FRAME_SIZE;
	frame = new Node[frame_size];
	for (int i = 0; i < frame_size; i++)
	{
		frame[i].info = -1;
		frame[i].age = 100;
	}
}

void LRU::print()
{
	cout << ">> LRU <<\n\n";
	cout << ">> 현재 사용중인 페이지는 다음과 같습니다." << endl << endl;
	for (int i = 0; i < frame_size; i++)
		cout << setw(7) << frame[i].info << '(' << frame[i].age-1 << ')';
	cout << endl << endl;
}

int LRU::find(int item)
{
	for (int i = 0; i < frame_size; i++)
	{
		if (frame[i].info == item)
			return i;
	}
	return -1;
}

void LRU::insert(int item)
{
	int there = this->find(item);

	if (there == -1)
	{
		there = 0;
		for (int i = 1; i < frame_size; i++)
		{
			if (frame[i].age > frame[there].age)
				there = i;
		}
		frame[there].info = item;
		frame[there].age = 0;
	}
	else
	{
		frame[there].age = 0;
	}

	for (int i = 0; i < frame_size; i++)
		frame[i].age++;
}




Optimal::Optimal()
{
	frame_size = FRAME_SIZE;
	frame = new int[frame_size];
	shortest = new int[frame_size];
	for (int i = 0; i < frame_size; i++)
	{
		frame[i] = -1;
		shortest[i] = 0;
	}
	init = 0;
	valid = true;
}

int Optimal::find(int* arr, int arr_size)
{
	for (int i = 0; i < frame_size; i++)
		shortest[i] = 100;
	bool there;
	int ret = 0;

	for (int i = 0; i < frame_size; i++)
	{
		there = false;
		for (int j = 1; j < arr_size; j++)
		{
			if (frame[i] == arr[j])
			{
				shortest[i] = j;
				there = true;
				break;
			}
		}
		if (!there)
			shortest[i] = 100;
		if (shortest[ret] < shortest[i])
			ret = i;
	}

	for (int i = 0; i < frame_size; i++)
	{
		if (arr[0] == frame[i])
		{
			valid = false;
			break;
		}
		else
			valid = true;
	}
	if (valid)
	{
		for (int j = 1; j < arr_size; j++)
		{
			if (arr[0] == arr[j])
			{
				shortest[ret] = j;
				there = true;
				break;
			}
		}
	}
	return ret;
}

void Optimal::print()
{
	cout << ">> Optimal <<\n\n";
	cout << ">> 현재 사용중인 페이지와 다음 페이지 까지의 거리는 다음과 같습니다." << endl << endl;
	for (int i = 0; i < frame_size; i++)
		cout << setw(7) << frame[i] << '(' << shortest[i] << ')';
	cout << endl << endl;
}

void Optimal::insert(int item, int* arr, int arr_size)
{
	if (init < 10)
	{
		for (int i = 0; i < init; i++)
			if (item == frame[i])
				return;
		frame[init] = arr[0];
		init++;
	}
	else
	{
		int there = this->find(arr, arr_size);
		if(valid)
			frame[there] = item;
	}
}