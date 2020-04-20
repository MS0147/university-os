/*
############# 데드락 회피 알고리즘 구현 ################

수행이 되지 않을 시 여러번 재시도하면 수행 가능한 경우가 나옴을 명시한다.

2016104106
컴퓨터공학과
김민석
2019/12/02 제출
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
		//리소스 할당, 가용자원 임의 할당
		Resourse[i] = rand() % 30 + 16;
		Available[i] = Resourse[i];
	}

	int Max[8][6];
	int Allocation[8][6];
	int Need[8][6];

	//Max 할당
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			Max[j][i] = rand() % 13;
	}

	//Allocation 할당
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

	// Need 값 할당
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Need[j][i] = Max[j][i] - Allocation[j][i];
		}
	}






	//출력---------------------
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
	//---------------------출력





	int selectProcess; //실행할 프로세스 사용자 입력
	vector<int> ExecProc, Result; // ExecProc : 현재 수행 가능한 프로세스들, Result : 수행한 결과
	bool moreTosearch = true;


	//데드락이 걸리던지, 탈출하던지 둘 중 하나!
	while (true)
	{
		//Result가 다 할당되면 마무리 출력
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






		//수행 불가능한 경우------------------------

		//수행 가능한 것이 없으면 종료
		moreTosearch = !(ExecProc.size() == 0);
		if (!moreTosearch)
		{
			cout << ">> NULL\n\n>> This program has deadlock and we can't unlock this. Please restart program." << endl;
			break;
		}
		//더이상 진전할 수 없을 때 데드락이므로 수행 종료
		moreTosearch = (Result.size() != ExecProc.size());
		if (!moreTosearch)
		{
			cout << "\n\n>> Finished Process == Executable Process" << endl;
			cout << ">> This program has deadlock and we can't unlock this. Please restart program." << endl;
			break;
		}
		//-----------------------수행 불가능한 경우 끝







		/*
		이 아래는 수행 가능할 때 실행하는 구문
		*/

		cout << endl << ">> Input process number what you want : ";
		cin >> selectProcess;
		if (selectProcess == -1)
			break;

		//입력값이 유효한 값인가
		check = false;
		for (int i = 0; i < ExecProc.size(); i++)
		{
			if (selectProcess == ExecProc[i])
			{
				check = true;
				break;
			}
		}

		//1. 유효하지 않으면
		if (!check)
		{
			cout << endl << ">> You chose the unexecutable process!!!!!!!!!!!!!!!" << endl;
			ExecProc.clear();
			continue;
		}

		//2. 유효할 때
		Result.push_back(selectProcess);

		//전에 이미 입력한 값이면 제거
		for (int i = 0; i < Result.size() - 1; i++)
		{
			if (selectProcess == Result[i])
			{
				Result.pop_back();
				break;
			}
		}

		//프로세스가 종료됬으므로 0으로 만들어 버리기
		for (int i = 0; i < 6; i++)
		{
			Available[i] += Allocation[selectProcess][i];
			Allocation[selectProcess][i] = 0;
		}

		//출력-------------------
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
		//--------------------출력 종료


		cout << ">> Finished Process is... ";
		for (int i = 0; i < Result.size(); i++)
			cout << 'P' << Result[i] << ' ';
		cout << endl;
	}

	system("pause");
	return 0;
}