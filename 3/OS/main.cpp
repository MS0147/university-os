#include"Memory.h"

int main()
{
	int choose;
	int size;
	int alloced = 0;
	int num = 0;
	int count = 0;
	vector<int> UserMemory;
	
	int already;
	Memory value;

	while (true)
	{
		value.Print();
		cout << endl << ">> 1: Allocation" << endl << ">> 2: Delete" << endl << ">> else: Exit" << endl << endl;
		cin >> choose;

		if (choose == 1) {
			cout << ">> Process " << alloced + 1 << ": Input process size" << endl << ">> ";
			alloced++;
			cin >> size;
			already = value.BestFit(size);
			if (already == -1)
			{
				cout << "The process is already allocated." << endl;
				alloced--;
				continue;
			}
		}
		else if (choose == 2)
		{
			cout << ">> Input process number" << endl << ">> ";
			cin >> num;
			count = 0;
			for (int i = 0; i < UserMemory.size(); i++)
				if (num > UserMemory[i]) 
					count++;
			UserMemory.push_back(num);
			value.Delete(num, count);
		}
		else
		{
			cout << ">> Finished!" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}