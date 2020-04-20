#pragma once
const int FRAME_SIZE = 10;

struct Node
{
	int info;
	int age;
};

class FIFO
{
private:
	int frame_size;
	int* frame;
	int index;
public:
	FIFO();
	void print();
	void insert(int item);
	bool find(int item);
};

class LRU
{
private:
	int frame_size;
	Node* frame;
public:
	LRU();
	void print();
	void insert(int item);
	int find(int item);
};

class Optimal
{
private:
	int frame_size;
	int* frame;
	int init;
	int* shortest;
	bool valid;
public:
	Optimal();
	void print();
	void insert(int item, int* arr, int arr_size);
	int find(int* arr, int arr_size);
};