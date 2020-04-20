#include<iostream>
#include<ctime>
#include<cmath>
#include<fstream>
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;

struct polling
{
	const int C = 1;
	const int T = 5;
	bool find = false;
};

struct deferrable
{
	const int C = 2;
	const int T = 5;
	float bandwidth = 1;
	bool find = false;
};

struct process
{
	int C;
	int T;
	int processnum;
	int aftertime;
	bool finish = false;
};

int main()
{
	int temp = 0;
	string line;
	int tempT, tempC;
	int count = 0;
	process arr[10];
	polling Pol;
	deferrable Def;
	double valid = 0;
	double dvalid = 0;
	int aparr[10];
	double compare;
	
	fstream file;
	file.open("dataset.txt");
	
	cout << "주기적 task는 다음과 같다." << endl;
	cout << setw(10) << "process" << setw(10) << 'T' << setw(10) << 'C' << endl;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			temp = line.find(' ');
			tempT = stoi(line.substr(0,2));
			tempC = stoi(line.substr(3,1));
			arr[count].C = tempC;
			arr[count].T = tempT;
			arr[count].processnum = count;
			valid += tempC / float(tempT);
			dvalid += tempC / float(tempT);
			count++;
			cout << setw(10) << "process" << count << setw(10) << tempT << setw(10) << tempC << endl;
		}
	}
	
	valid += Pol.C / float(Pol.T);
	dvalid += Def.C / float(Def.T);
	cout << endl << "--------------------------------------------------------" << endl << endl;

	srand((unsigned int)time(NULL));

	process* AP = new process[10];

	cout << "AP의 정보들은 다음과 같다" << endl << endl;

	cout << setw(10) << "AP" << setw(10) << "발생시간" << setw(10) << "수행시간" << endl;

	for (int i = 0; i < 10; i++)
	{
		AP[i].C = 1;
		AP[i].T = rand()*rand() % 80 + 1;
		AP[i].processnum = i;
		aparr[i] = AP[i].T;
		cout << setw(10) << "AP" << i << setw(10) << AP[i].T << setw(10) << AP[i].C << endl;
	}
	cout << endl << "--------------------------------------------------------" << endl << endl;

	bool tlfgod = true;

	sort(aparr, aparr + 10);

	int climing = 5;
	int indexcliming = 0;

	compare = count * (pow(2, (1 / double(count))) - 1);

	cout << "주기 : 5이고 수행시간 : 1 \n\nPolling방식일 때\n\n";
	if (valid > count*(pow(2, (1 / double(count))) - 1))
	{
		cout << valid << '>' << count * (pow(2, (1 / double(count))) - 1) << "\n\n이므로 실행 불가" << endl;
		system("pause");
		return 0;
	}
	else
		cout << valid << "<=" << compare << "\n\n이므로 실행 가능하다." << endl << endl;
	


	while (tlfgod)
	{
		if (AP[indexcliming].T <= climing)
		{
			AP[indexcliming].aftertime = climing;
			indexcliming++;
		}
		climing += 5;
		if (indexcliming == 10)
			break;
	}

	cout << '(';
	for (int i = 0; i < 9; i++)
	{
		cout << '(' << AP[i].aftertime << '-' << AP[i].T << ')' << '+' << ' ';
	}
	cout << '(' << AP[9].aftertime << '-' << AP[9].T << ')' << ')' << '/' << "10" << '=';
	temp = 0;
	for (int i = 0; i < 10; i++)
	{
		temp += (AP[i].aftertime - AP[i].T);
	}
	double ftemp = double(temp) / 10;

	cout << ftemp << endl << endl;
	cout << endl << "평균 대기 시간 : " << ftemp << endl << endl << "--------------------------------------------------------" << endl << endl;

	valid += tempC / float(tempT);

	compare = count * (pow(2, (1 / double(count))) - 1);
	cout << "주기 : 5이고 수행시간 : 2 \n\ndeferrable방식일 때 ";
	if (dvalid > count*(pow(2, (1 / double(count))) - 1))
	{
		cout << dvalid << '>' << count * (pow(2, (1 / double(count))) - 1) << "\n\n이므로 실행 불가" << endl;
		system("pause");
		return 0;
	}
	else
		cout << dvalid << "<=" << compare << "\n\n이므로 실행 가능하다." << endl << endl;
	
	climing = 5;
	indexcliming = 0;
	while (tlfgod)
	{
		if (AP[indexcliming].T <= climing)
		{
			AP[indexcliming].aftertime = climing;
			indexcliming++;
		}
		climing += 1;
		if (AP[indexcliming].T <= climing)
		{
			AP[indexcliming].aftertime = climing;
			indexcliming++;
		}
		climing += 4;

		if (indexcliming >= 10)
			break;
	}

	cout << '(';
	for (int i = 0; i < 9; i++)
	{
		cout << '(' << AP[i].aftertime << '-' << AP[i].T << ')' << '+' << ' ';
	}
	cout << '(' << AP[9].aftertime << '-' << AP[9].T << ')' << ')' << '/' << "10" << '=';
	temp = 0;
	for (int i = 0; i < 10; i++)
	{
		temp += (AP[i].aftertime - AP[i].T);
	}
	ftemp = double(temp) / 10;

	cout << ftemp << endl << endl;
	cout << endl << "평균 대기 시간 : " << ftemp << endl << endl << "--------------------------------------------------------" << endl << endl;

	system("pause");
	return 0;
}