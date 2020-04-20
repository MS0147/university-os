#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

const int MAX_SIZE = 256;

class Memory {
private:
	vector<int> memory, start, limit;
	vector<int> tstart, tlimit;
public:
	Memory();
	void Print();
	int FreeSize();
	void Index();
	int BlockNum();
	int BestFit(int size);
	void Delete(int item, int count);
};


Memory::Memory()
{
	for (int i = 0; i < MAX_SIZE; i++)
		memory.push_back(0);
	cout << "Memory size is 256K" << endl;
}

void Memory::Print()
{
	cout << setfill('-') << setw(40) << ' ' << endl;
	Index();
	cout << ">> Remained Memory Resource : " << FreeSize() << endl;
	cout << ">> Block num : " << BlockNum() << endl;

	int temp = 0;
	for (int i = 0; i < start.size(); i++)
		temp += limit[i] - start[i];

	cout << ">> Average size : " << (MAX_SIZE - temp) / BlockNum() << endl;
	cout << setw(40) << ' ' << endl;
}

int Memory::FreeSize()
{
	int remain = 0;
	for (int i = 0; i < MAX_SIZE; i++)
		if (memory[i] == 0)
			remain++;
	return remain;
}

void Memory::Index()
{
	if (start.size() == 0)
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (memory[i] != 0)
			{
				start.push_back(i);
				tstart.push_back(i);
				for (i; i < MAX_SIZE; i++)
					if (memory[i] == 0)
					{
						limit.push_back(i);
						tlimit.push_back(i);
						break;
					}
			}
		}
	else
	{
		for (int i = limit[limit.size() - 1]; i < MAX_SIZE; i++)
			if (memory[i] != 0)
			{
				start.push_back(i);
				tstart.push_back(i);
				for (i; i < MAX_SIZE; i++)
					if (memory[i] == 0)
					{
						limit.push_back(i);
						tlimit.push_back(i);
						break;
					}
			}
	}
}


int Memory::BlockNum()
{
	int block = 0;
	int num = 0;

	if (start.size() != 0)
	{
		if (start[0] == 0)
			num++;
		if (limit[limit.size() - 1] == MAX_SIZE - 1)
			num++;
		for (int i = 0; i < start.size() - 1; i++)
			if (limit[i] == start[i + 1])
				num++;

		block = start.size() + 1 - num;
	}
	else
		block = 1;

	return block;
}

int Memory::BestFit(int size)
{
	if (FreeSize() < size) {
		cout << ">> This Instruction isn't executable." << endl;
		return -1;
	}

	if (BlockNum() == 1)
	{
		if (start.size() == 0)
			for (int i = 0; i < size; i++)
				memory[i] = 1;
		else
			for (int i = 0; i < size; i++)
			{
				memory[limit[limit.size() - 1] + i] = 1;
			}
		return 0;
	}
	vector<int> temp;
	int check = -1;
	if (memory[0] == 0)
		temp.push_back(start[0]);
	for (int i = 0; i < start.size() - 1; i++)
		temp.push_back(start[i + 1] - limit[i]);
	if (memory[255] == 0)
		temp.push_back(MAX_SIZE - limit[limit.size() - 1]);


	for (int i = 0; i < temp.size(); i++)
		if (size <= temp[i])
		{
			if (check == -1)
				check = i;
			else if (temp[i] < temp[check])
				check = i;
		}

	int count = 0;

	if (check != -1)
		for (int i = 0; i < 256; i++)
			if (memory[i] == 0)
			{
				if (count == check)
				{
					start.insert(start.begin() + check, i);
					tstart.push_back(i);
					for (int j = 0; j < size; j++)
					{
						memory[i] = 1;
						i++;
					}
					limit.insert(limit.begin() + check, i);
					tlimit.push_back(i);
					cout << ">> Coalescing" << endl;
					break;
				}
				else
					for (; i < 256; i++)
						if (memory[i] != 0)
						{
							count++;
							break;
						}
			}
	return 0;
}

void Memory::Delete(int item, int count)
{
	for (int i = tstart[item - 1]; i < tlimit[item - 1]; i++)
		memory[i] = 0;

	tstart[item - 1] = -1;
	tlimit[item - 1] = -1;
	start.erase(start.begin() + item - (count + 1));
	limit.erase(limit.begin() + item - (count + 1));
}