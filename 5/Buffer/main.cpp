#include<iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
using namespace std;

struct buffer
{
	int info;
	int blockNum;
	int state; 
};

const int MOD_NUM = 5;
const int CACHE_SIZE = 12;

int main()
{
	srand(unsigned int(time(NULL)));

	int mod = 0;
	int cacheSize = CACHE_SIZE;
	cout << ">> Input number of mod (3~10) : ";
	cin >> mod;
	if (mod > 10 || mod < 3)
		mod = MOD_NUM;
	cout << endl;

	
	vector<vector<buffer>> hashQueueHeader;
	for (int i = 0; i < mod; i++)
	{
		vector<buffer> hashQueue;
		hashQueueHeader.push_back(hashQueue);
	}

	vector<int> temp(cacheSize);
	for (int i = 0; i < cacheSize; i++)
	{
		temp[i] = rand() % 50 + 1;
		for (int j = 0; j < i; j++)
		{
			if (temp[i] == temp[j])
			{
				i--;
				break;
			}
		}
	}

	buffer tempData;
	for (int i = 0; i < cacheSize; i++)
	{
		tempData.info = temp[i];
		tempData.blockNum = temp[i] % mod;
		hashQueueHeader[tempData.blockNum].push_back(tempData);
	}


	vector<buffer*> freeList;
	vector<int> randomNumber(cacheSize);
	for (int i = 0; i < int(cacheSize); i++)
	{
		randomNumber[i] = rand() % cacheSize;
		for (int j = 0; j < i; j++)
		{
			if (randomNumber[i] == randomNumber[j])
			{
				i--;
				break;
			}
		}
	}
	
	for (int i = 0; i < int(cacheSize); i++)
	{
		int rest = temp[randomNumber[i]] % mod;
		for (int j = 0; j < hashQueueHeader[rest].size(); j++)
		{
			if (hashQueueHeader[rest][j].info == temp[randomNumber[i]])
			{
				hashQueueHeader[rest][j].state = rand() % 2 + 2;
				freeList.push_back(&hashQueueHeader[rest][j]);
				break;
			}
		}
	}
	randomNumber.clear();

	
	for (int i = 0; i < mod; i++)
		for (int j = 0; j < hashQueueHeader[i].size(); j++)
			if (hashQueueHeader[i][j].state == NULL)
				hashQueueHeader[i][j].state = rand() % 2 + 1; 
						
	int inputNum = 0;
	do{
		for (int i = 0; i < hashQueueHeader.size(); i++)
		{
			cout << endl << ">> Block Num: " << i << "  mod: " << hashQueueHeader.size() << "   ";
			for (int j = 0; j < hashQueueHeader[i].size(); j++)
			{
				cout << hashQueueHeader[i][j].info;
				switch (hashQueueHeader[i][j].state)
				{
				case 0:
					cout << "(Write)  ";
					break;
				case 1:
					cout << "(Busy)  ";
					break;
				case 2:
					cout << "(Free)  ";
					break;
				case 3:
					cout << "(Delay)  ";
					break;
				}
			}
		}

		cout << "\n>> FreeList : ";
		for (int i = 0; i < freeList.size(); i++)
		{
			cout << freeList[i]->info;
			switch (freeList[i]->state)
			{
			case 0:
				cout << "(Write)  ";
				break;
			case 1:
				cout << "(Busy)  ";
				break;
			case 2:
				cout << "(Free)  ";
				break;
			case 3:
				cout << "(Delay)  ";
				break;
			}
		}

		cout << endl << ">> Input wanted block (-1 = exit, -2 = computer poweroff after 10 second.)\n>> ";
		cin >> inputNum;
		system("cls");


		if (inputNum == -1)
			break;
		else if (inputNum == -2)
		{
			cout << "한시간 뒤 컴퓨터 종료" << endl;
			system("shutdown -s -t 3600");
		}

		bool flag1 = false;
		int intTemp = NULL;
		int rest = inputNum % mod;
		for (int j = 0; j < hashQueueHeader[rest].size(); j++)
		{
			if (inputNum == hashQueueHeader[rest][j].info)
			{
				flag1 = true;
				intTemp = j;
				break;
			}
		}

		if (flag1)
		{
			if (hashQueueHeader[rest][intTemp].state == 1 || hashQueueHeader[rest][intTemp].state == 0)
			{
				cout << ">> " << hashQueueHeader[rest][intTemp].info << " is busy.\n";
				Sleep(3000);
				hashQueueHeader[rest][intTemp].state = 2;
				cout << ">> Now" << hashQueueHeader[rest][intTemp].info << " can use.\n";
			}
			else
			{
				if (freeList.empty())
				{
					hashQueueHeader[rest][intTemp].state = 1;
					cout << ">> " << hashQueueHeader[rest][intTemp].info << "is changed to 'busy'" << endl;
				}
				else
				{
					for (int i = 0; i < freeList.size(); i++)
					{
						if (freeList[i]->info == inputNum)
						{
							freeList.erase(freeList.begin() + i);
							cout << ">> " << hashQueueHeader[rest][intTemp].info << "is deleted in freelist.\n";

							hashQueueHeader[rest][intTemp].state = 1;
							cout << ">> " << hashQueueHeader[rest][intTemp].info << "is changed 'busy'\n";
							break;
						}
						else if (i == freeList.size() - 1)
						{
							hashQueueHeader[rest][intTemp].state = 1;
							cout << ">> " << hashQueueHeader[rest][intTemp].info << "is changed busy.\n" << endl;
							break;
						}
					}
				}
			}
		}

		else
		{
			if (freeList.empty())
			{
				cout << ">> There is no entry in free list. Sleep a few second" << endl;
				Sleep(2000);
				intTemp = rand() % cacheSize;
				cout << ">> " << temp[intTemp] << " is finished\n";
				int rest = temp[intTemp] % mod;
				for (int i = 0; i < hashQueueHeader[rest].size(); i++)
				{
					if (hashQueueHeader[rest][i].info == temp[intTemp])
					{
						hashQueueHeader[rest][i].state = 2;
						freeList.push_back(&hashQueueHeader[rest][i]);
						break;
					}
				}
			}
			else if (freeList[0]->state == 3)
			{
				intTemp = 0;
				for (int i = 0; i < freeList.size(); i++)
				{
					if (freeList[i]->state == 3)
						intTemp++;
					else
						break;
				}

				for (int i = 0; i < intTemp; i++)
				{
					int tempD = freeList[0]->info;
					int tempB = freeList[0]->blockNum;
					freeList.erase(freeList.begin());
					for (int j = 0; j < hashQueueHeader[tempB].size(); j++)
					{
						if (tempD == hashQueueHeader[tempB][j].info)
						{
							hashQueueHeader[tempB][j].state = 0;
							break;
						}
					}
				}
				if (!freeList.empty())
				{
					int t1 = freeList[0]->blockNum;
					int t2 = freeList[0]->info;
					freeList.erase(freeList.begin());
					for (int j = 0; j < hashQueueHeader[t1].size(); j++)
					{
						if (t2 == hashQueueHeader[t1][j].info)
						{
							for (int i = 0; i < temp.size(); i++)
							{
								if (temp[i] == hashQueueHeader[t1][j].info)
								{
									temp.erase(temp.begin() + i);
									temp.push_back(inputNum);
									break;
								}
							}
							hashQueueHeader[t1].erase(hashQueueHeader[t1].begin() + j);
							break;
						}
					}
				}
				else if (freeList.empty())
					continue;

				buffer tempBuffer;
				tempBuffer.info = inputNum;
				tempBuffer.blockNum = inputNum % mod;
				tempBuffer.state = 2;
				hashQueueHeader[tempBuffer.blockNum].push_back(tempBuffer);
			}
			else
			{
				int t1 = freeList[0]->blockNum;
				int t2 = freeList[0]->info;
				freeList.erase(freeList.begin());
				for (int j = 0; j < hashQueueHeader[t1].size(); j++)
				{
					if (t2 == hashQueueHeader[t1][j].info)
					{
						for (int i = 0; i < temp.size(); i++)
						{
							if (temp[i] == hashQueueHeader[t1][j].info)
							{
								temp.erase(temp.begin() + i);
								temp.push_back(inputNum);
								break;
							}
						}
						hashQueueHeader[t1].erase(hashQueueHeader[t1].begin() + j);
						break;
					}
				}
				buffer tempBuffer;
				tempBuffer.info = inputNum;
				tempBuffer.blockNum = inputNum % mod;
				tempBuffer.state = 2;
				hashQueueHeader[tempBuffer.blockNum].push_back(tempBuffer);
			}
		}
	} while (cacheSize != 0);
	return 0;
}