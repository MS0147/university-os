/*
############# ����� ȸ�� �˰��� ���� ################

������ ���� ���� �� ������ ��õ��ϸ� ���� ������ ��찡 ������ ����Ѵ�.

2016104106
��ǻ�Ͱ��а�
��μ�
2019/12/02 ����
*/
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;

int main()
{
	srand((unsigned int)time(NULL));

	int Resourse[6];
	int Available[6];
	for (int i = 0; i < 6; i++)
	{
		//���ҽ� �Ҵ�, �����ڿ� ���� �Ҵ�
		Resourse[i] = rand() % 30 + 16;
		Available[i] = Resourse[i];
	}

	int Max[8][6];
	int Allocation[8][6];
	int Need[8][6];

	//Max �Ҵ�
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			Max[j][i] = rand() % 13;
	}

	//Allocation �Ҵ�
	for (int i = 0; i < 6; i++)
	{
		int limit = 0;
		for (int j = 0; j < 8; j++)
		{
			Allocation[j][i] = rand() % 6;
			limit += Allocation[j][i];
			if (limit > Available[i] || Allocation[j][i] > Max[j][i])
			{
				limit -= Allocation[j][i];
				Allocation[j][i] = 0;
			}
		}
		Available[i] -= limit;
	}

	// Need �� �Ҵ�
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Need[j][i] = Max[j][i] - Allocation[j][i];
		}
	}






	//���---------------------
	cout << "[ A: " << Resourse[0] << " B: " << Resourse[1] << " C: " << Resourse[2] << " D: " << Resourse[3] << " E: " << Resourse[4] << " F: " << Resourse[5] << " ]" << endl;
	cout << setfill('=') << endl;
	cout << setw(23) << "Allocation" << setw(23) << "Need" << setw(23) << "Max" << setw(23) << "Available : ";

	for (int j = 0; j < 6; j++)
		cout << Available[j] << ' ';
	cout << endl;

	for (int i = 0; i < 8; i++)
	{
		cout << "| P" << i << "		";
		for (int j = 0; j < 6; j++)
		{
			cout << Allocation[i][j] << ' ';
		}
		cout << "		";
		for (int j = 0; j < 6; j++)
		{
			cout << Need[i][j] << ' ';
		}
		cout << "		";
		for (int j = 0; j < 6; j++)
		{
			cout << Max[i][j] << ' ';
		}
		cout << endl;
	}
	cout << setfill('=') << setw(80) << '=' << endl;
	//---------------------���





	int selectProcess; //������ ���μ��� ����� �Է�
	vector<int> ExecProc, Result; // ExecProc : ���� ���� ������ ���μ�����, Result : ������ ���
	bool moreTosearch = true;


	//������� �ɸ�����, Ż���ϴ��� �� �� �ϳ�!
	while (true)
	{
		//Result�� �� �Ҵ�Ǹ� ������ ���
		if (Result.size() == 8)
		{
			cout << ">> Ok, the result is... ";
			for (int i = 0; i < Result.size(); i++)
				cout << 'P' << Result[i] << " ";
			break;
		}



		cout << ">> If you want to exit this program, input -1" << endl << ">> Now you can execute about...";
		bool check = true;

		for (int i = 0; i < 8; i++)
		{
			check = true;
			for (int j = 0; j < 6; j++)
			{
				if (Need[i][j] > Available[j])
				{
					check = false;
					break;
				}
			}
			if (check)
				ExecProc.push_back(i);
		}
		for (int i = 0; i < ExecProc.size(); i++)
			cout << "P" << ExecProc[i] << " ";






		//���� �Ұ����� ���------------------------

		//���� ������ ���� ������ ����
		moreTosearch = !(ExecProc.size() == 0);
		if (!moreTosearch)
		{
			cout << ">> NULL\n\n>> This program has deadlock and we can't unlock this. Please restart program." << endl;
			break;
		}
		//���̻� ������ �� ���� �� ������̹Ƿ� ���� ����
		moreTosearch = (Result.size() != ExecProc.size());
		if (!moreTosearch)
		{
			cout << "\n\n>> Finished Process == Executable Process" << endl;
			cout << ">> This program has deadlock and we can't unlock this. Please restart program." << endl;
			break;
		}
		//-----------------------���� �Ұ����� ��� ��







		/*
		�� �Ʒ��� ���� ������ �� �����ϴ� ����
		*/

		cout << endl << ">> Input process number what you want : ";
		cin >> selectProcess;
		if (selectProcess == -1)
			break;

		//�Է°��� ��ȿ�� ���ΰ�
		check = false;
		for (int i = 0; i < ExecProc.size(); i++)
		{
			if (selectProcess == ExecProc[i])
			{
				check = true;
				break;
			}
		}

		//1. ��ȿ���� ������
		if (!check)
		{
			cout << endl << ">> You chose the unexecutable process!!!!!!!!!!!!!!!" << endl;
			ExecProc.clear();
			continue;
		}

		//2. ��ȿ�� ��
		Result.push_back(selectProcess);

		//���� �̹� �Է��� ���̸� ����
		for (int i = 0; i < Result.size() - 1; i++)
		{
			if (selectProcess == Result[i])
			{
				Result.pop_back();
				break;
			}
		}

		//���μ����� ��������Ƿ� 0���� ����� ������
		for (int i = 0; i < 6; i++)
		{
			Available[i] += Allocation[selectProcess][i];
			Allocation[selectProcess][i] = 0;
		}

		//���-------------------
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << endl << "[ A: " << Resourse[0] << " B: " << Resourse[1] << " C: " << Resourse[2] << " D: " << Resourse[3] << " E: " << Resourse[4] << " F: " << Resourse[5] << " ]";
		cout << endl << ">> The result is..." << endl << setw(25) << "Allocation" << setw(25) << "Need" << setw(25) << "Max" << setw(25) << "Available : ";
		for (int j = 0; j < 6; j++)
			cout << Available[j] << ' ';
		cout << endl;
		for (int i = 0; i < 8; i++)
		{
			cout << "| P" << i << "		";
			for (int j = 0; j < 6; j++)
				cout << Allocation[i][j] << ' ';
			cout << "		";
			for (int j = 0; j < 6; j++)
				cout << Need[i][j] << ' ';
			cout << "		";
			for (int j = 0; j < 6; j++)
				cout << Max[i][j] << ' ';
			cout << endl;
		}

		ExecProc.clear();
		cout << setfill('=') << setw(80) << '=' << endl;
		//--------------------��� ����


		cout << ">> Finished Process is... ";
		for (int i = 0; i < Result.size(); i++)
			cout << 'P' << Result[i] << ' ';
		cout << endl;
	}

	system("pause");
	return 0;
}