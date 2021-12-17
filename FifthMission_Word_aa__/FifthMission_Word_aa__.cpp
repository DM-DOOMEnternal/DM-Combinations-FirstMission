#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

void permutationsWithRepeat(ofstream&, int, int*, int); 
bool nextSequencePermutationsWithRepeat(int*, size_t);
void CombinationsWithRepetitions(ofstream&,int);
void permutationsWord(int* set, int* set2, std::ofstream& file, int countWord_a);
int lengthForCombinations(int countWord_a);
void fillInTheSet_newset(int* set, int* set2, int length, int countWord_a);
void fillInTheSet(int length, int* set, int number, int countWord_a);
bool nextSequenceCombinationsWithRepeat(int*, size_t, size_t);
bool findIndexElm_firstOccurrence_whichLessCurrent(int&, int*);
void sortTheRestOfTheSequence(int*, int, size_t);

size_t lengt_4_7(int);
void print(int*, int, ofstream&);
void indexLine(int , int& , std::ofstream& , int& );
void printWord(int, ofstream&);
bool checkCountWord_a(int* , int , int );
bool countWord_a_3456(int , int );
bool notRepeatThePreviousSet(int*, int*, int);

int main()
{
	setlocale(LC_ALL, "ru");
	cout << " \t\tКомбинаторные алгоритмы #5\n";
	try
	{
		cout << " Все данные записываются в файл. Введите путь файла\n (формата Диск:\{папка}\ файл.формат )\n :";
		string pathFile = "";
		getline(cin, pathFile);
		ofstream file(pathFile);
		while (!file)
		{
			pathFile = "";
			cout << " Путь к файл указан не вверно либо файла не существует. \n Укажите заново путь: ";
			getline(cin, pathFile);
			file.open(pathFile);
		}
		cout << " Дано множество {a,b,c,d,e,f}\n";

		for (;;)
		{
			cout << " 1.Построить все слова длины 4, в которых ,больше двух букв 'a'. "
				"\n 2.Построить все слова длины 7, в которых большие двух буквы 'a'.\n";

			cout << " Выбор пал на ----> ";
			int choice = 0; cin >> choice;
			switch (choice)
			{
			case 1:
				file << "Все слова длины 4, в которых больше двух букв 'a'\n";
				CombinationsWithRepetitions(file,4);
				cout << "Данные успешно записаны в файл\n";
				break;
			case 2:
				file << "Все слова длины 7, в которых больше двух букв 'a'.\n";
				CombinationsWithRepetitions(file, 7);
				cout << "Данные успешно записаны в файл\n";
				break;
			default:
				break;
			}

			bool repeat = false;
			cout << " Продолжить ? (1)";
			cin >> repeat;
			if (repeat == false)
			{
				file.close();
				break;
			}

		}//конец for
	}
	catch (const  char* exception)
	{
		cerr << " Error: " << exception << "\n";
	}
	catch (...) {}
}

void CombinationsWithRepetitions(ofstream& file, int length)
{
	int* set;
	
	if (length == 4)
	{
		set = new int[length] { 1, 1, 1, 2 };
		permutationsWithRepeat(file, 4, set,3);
		fillInTheSet(length, set,3,3);
		permutationsWithRepeat(file, 4, set,3);
		fillInTheSet(length, set, 4,3);
		permutationsWithRepeat(file, 4, set,3);
		fillInTheSet(length, set, 5,3);
		permutationsWithRepeat(file, 4, set,3);
		fillInTheSet(length, set, 6,3);
		permutationsWithRepeat(file, 4, set,3);
		fillInTheSet(length, set, 1, 3);
		print(set, length, file);
		delete[] set;
		return;
	}
	else
	{
		int* set = new int[length] {};
		int* setLast = new int[7]{};
		int* set2 = new int[length + 1]{ 2,2,2,2,2,2 };
		for (int countWord_a = 3; countWord_a < 7; countWord_a++)
		{
			fillInTheSet(length, set, NULL,countWord_a);

			permutationsWithRepeat(file, 7, set, countWord_a);
			permutationsWord(set, set2, file, countWord_a);
			for (int i = 0; i < length + 1; i++)
				set2[i] = 2;
		}
		for (int i = 0; i < length; i++)
			set[i] = 1;
		print(set, length, file);
		cout << "a a a a a a a \n";

		delete[] set;
		delete[] setLast;
		delete[] set2;
		return;
	}
		
	delete[] set;
}

void permutationsWord(int* set, int* set2, std::ofstream& file, int countWord_a)
{
	while (nextSequenceCombinationsWithRepeat(set2, 6, lengthForCombinations(countWord_a)))
	{
		fillInTheSet_newset(set, set2, 7, countWord_a);
		permutationsWithRepeat(file, 7, set, countWord_a);
	}
}

int lengthForCombinations(int countWord_a)
{
	return countWord_a == 3? 4 : countWord_a == 4? 3 : countWord_a == 5? 2 : countWord_a == 6 ? 1 : 0;
}

void fillInTheSet_newset(int* set, int* set2,int length,int countWord_a)
{
	for (int j = 0; j < countWord_a; j++)
		set[j] = 1;
	for (int k = countWord_a; k < length; k++)
		set[k] = set2[k - countWord_a];
}

void fillInTheSet(int length, int* set,int number,int countWord_a)
{
	for (int i = 0; i < length; i++)
	{
		if (length == 4)
		{
			if (i == length - 1)
				set[i] = number;
			else
				set[i] = 1;
		}
		else
		{
			if (countWord_a == 3)
			{
				if (i > 3)
					set[i] = 1;
				else
					set[i] = 2;
			}else
				if (countWord_a == 4)
				{
					if (i < 4)
						set[i] = 1;
					else
						set[i] = 2;
				}else
					if (countWord_a == 5)
					{
						if (i < 5)
							set[i] = 1;
						else
							set[i] = 2;
					}else
						if (countWord_a == 6)
						{
							if (i < 6)
								set[i] = 1;
							else
								set[i] = 2;
						}
			
		}
		
	}
}

bool nextSequenceCombinationsWithRepeat(int* set, size_t countElm, size_t k)
{
	int j = k - 1;
	while (set[j] == countElm && j >= 0)
		j--;
	if (j < 0)
		return false;
	if (set[j] >= countElm)
		j--;
	set[j]++;
	if (j == k - 1)
		return true;
	for (int m = j + 1; m < k; m++)
		set[m] = set[j];
	return true;
}//-----------------Сочетания с повторениями-------------------------

void permutationsWithRepeat(ofstream & file, int length, int* set2,int countWord_a)
{
	int* set = set2;
	int* setLast = new int[length + 2]{};

	print(set, length, file);
	while (nextSequencePermutationsWithRepeat(set, lengt_4_7(length)))
	{
		if (checkCountWord_a(set,lengt_4_7(length),countWord_a) == true)
		{
			print(set, length, file);
		}
	}

}

size_t lengt_4_7(int length)
{
	return length == 4 ? 4 : 7;
}

bool nextSequencePermutationsWithRepeat(int* set, size_t countElm)
{
	int j = countElm - 2;

	if (findIndexElm_firstOccurrence_whichLessCurrent(j, set) == false)
		return false;

	int k = countElm - 1;
	while (set[j] >= set[k])
		k--;

	swap(set[j], set[k]);// текущий и последний поменять местами 

	sortTheRestOfTheSequence(set, j, countElm); //сор ост элементы
	return true;
}//-----------------Перестановки-------------------------

bool findIndexElm_firstOccurrence_whichLessCurrent(int& j, int* set)
{
	while (j != -1 && set[j] >= set[j + 1]) //ищем индекс эл-а(первое вхожд) который меньше текущего(j+1) 
		j--;

	if (j == -1)
		return false;
	return true;
}

void sortTheRestOfTheSequence(int* set, int j, size_t countElm)
{
	int indexFromTheCurrent = j + 1, indexFromTheEnd = countElm - 1;//сортируем оставшуюся часть последовательности 
	while (indexFromTheCurrent < indexFromTheEnd)
	{
		swap(set[indexFromTheCurrent], set[indexFromTheEnd]);
		indexFromTheCurrent++; indexFromTheEnd--;
	}
}

void print(int* set, int countElm, ofstream & file)
{
	static int* setLast = new int[countElm];
	static int indexLineFirstMission = 0, indexLineSecondMission = 0;

	if (notRepeatThePreviousSet(set, setLast, countElm) == true)
	{
		indexLine(countElm, indexLineSecondMission, file, indexLineFirstMission);
		for (int i = 0; i < countElm; i++)
		{
			printWord(set[i], file);
			setLast[i] = set[i];
		}
		file << endl;
		cout << endl;
	}

}

void indexLine(int length, int& indexLineSecondMission, std::ofstream & file, int& indexLineFirstMission)
{
	if (length == 4)
	{
		indexLineSecondMission++;
		file << indexLineSecondMission << " : ";
	}
	else
	{
		indexLineFirstMission++;
		file << indexLineFirstMission << " : ";
	}
}

bool notRepeatThePreviousSet(int* set, int* setLast, int countElm)
{
	if (setLast != NULL)
	{
		for (int i = 0; i < countElm; i++)
		{
			if (set[i] != setLast[i])
				return true;
		}
		return false;
	}
	else
		return true;
}

void printWord(int number, ofstream & file)
{
	switch (number)
	{
	case 1:
		file << 'a' << " ";
		cout << 'a' << " ";
		break;
	case 2:
		file << 'b' << " ";
		cout << 'b' << " ";
		break;
	case 3:
		file << 'c' << " ";
		cout << 'c' << " ";
		break;
	case 4:
		file << 'd' << " ";
		cout << 'd' << " ";
		break;
	case 5:
		file << 'e' << " ";
		cout << 'e' << " ";
		break;
	case 6:
		file << 'f' << " ";
		cout << 'f' << " ";
		break;
	default:
		break;
	}
}

bool checkCountWord_a(int* set, int length, int countWord_a)
{
	bool secondMission;
	if (length == 4) secondMission = false; else secondMission = true;
	for (int i = 0, word_a = 0; i < length; i++)
	{
		if (set[i] == 1)
			word_a++;
		if (word_a == 3 && secondMission == false)
			return true;
		if (secondMission == true && countWord_a_3456(countWord_a, word_a))
			return true;		
	}
	return false;
}

bool countWord_a_3456(int countWord_a, int word_a)
{
	if (countWord_a == 3 && word_a == 3)
		return true;
	if (countWord_a == 4 && word_a == 4)
		return true;
	if (countWord_a == 5 && word_a == 5)
		return true;
	if (countWord_a == 6 && word_a == 6)
		return true;
	return false;
}
