// SecondMission_Word_aa.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<cmath>
#include<fstream>
#include<string>

using namespace std;

void permutationsWithRepeat(ofstream&,int,bool,int*);
bool nextSequencePermutationsWithRepeat(int*, size_t);
void CombinationsWithRepetitions(ofstream& );
bool nextSequenceCombinationsWithRepeat(int* , size_t , size_t);
bool findIndexElm_firstOccurrence_whichLessCurrent(int&, int*);
void sortTheRestOfTheSequence(int*, int, size_t);
void indexLine(bool repeatWords, int& indexLineSecondMission, std::ofstream& file, int& indexLineFirstMission);
size_t lengt_5_7(bool );
void print(int*, int, ofstream&,bool);
void printWord(int , ofstream& );
bool checkCountWord_a(int* );
bool notRepeatThePreviousSet(int* , int* , int );

int main()
{
	setlocale(LC_ALL, "ru");
	cout << " \t\tКомбинаторные алгоритмы #2\n";
	try
	{
		cout << " Все данные записываются в файл. Введите путь файла (формата Диск:\{папка}\ файл.формат )\n :";
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
			cout << " 1.Построить все слова длины 5, в которых ровно две буквы 'a'. "
				"\n 2.Построить все слова длины 5, в которых ровно две буквы 'a' остальные не повторятся.\n";

			cout << " Выбор пал на ----> ";
			int choice = 0; cin >> choice;
			switch (choice)
			{
			case 1:
				file << "Все слова длины 5, в которых ровно две буквы 'a'\n";
				CombinationsWithRepetitions(file);
				cout << "Данные успешно записаны в файл\n";
				break;
			case 2:
				file << "Все слова длины 5, в которых ровно две буквы 'a' остальные не повторятся.\n";
				permutationsWithRepeat(file,5,false,NULL);
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

//-----------------Сочетания с повторениями-------------------------
void CombinationsWithRepetitions(ofstream& file)
{
	int* set = new int[5]{ 1,1,2,2,2 };
	int* set2 = new int[6]{ 2, 2,2,2,2,2 };//3, 4, 5, 6};
	int* setLast = new int[7]{};


	permutationsWithRepeat(file, 5, true, set);
	set[0] = 1;
	set[1] = 1;

	while (nextSequenceCombinationsWithRepeat(set2, 6, 3))
	{
		for (int k = 2; k < 5; k++)
			set[k] = set2[k - 2];
		permutationsWithRepeat(file, 5, true, set);
		set[0] = 1;
		set[1] = 1;
	}
	delete[] set;
	delete[] set2;
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

//-----------------Перестановка с повторениями-------------------------
void permutationsWithRepeat(ofstream& file,int length,bool repeatWords,int* set2) //добавить параметров
{
	int* set;
	if (repeatWords == false)
	{
		set = new int[length + 2]{ 1,1,2,3,4,5,6 }; // a a b c d e f
	}
	else
		set = set2;

	int* setLast = new int[length+2]{};
	

	print(set, length, file, repeatWords);
	while (nextSequencePermutationsWithRepeat(set, lengt_5_7(repeatWords)))
	{
		if (checkCountWord_a(set) == true)
		{
			print(set, length, file, repeatWords);
		}		
	}
	if(repeatWords==false)
		delete[] set;
}

size_t lengt_5_7(bool repeatWords)
{
	return repeatWords == false ? 7 : 5;
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

void print(int* set, int countElm, ofstream & file,bool repeatWords)
{
	static int* setLast = new int[countElm];
	static int indexLineFirstMission = 0, indexLineSecondMission = 0;

	if (notRepeatThePreviousSet(set, setLast, countElm) == true)
	{		
		indexLine(repeatWords, indexLineSecondMission, file, indexLineFirstMission);
		for (int i = 0; i < countElm; i++)
		{
			printWord(set[i], file);
			setLast[i] = set[i];
		}
		file << endl;
		cout << endl;
	}

}

void indexLine(bool repeatWords, int& indexLineSecondMission, std::ofstream& file, int& indexLineFirstMission)
{
	if (repeatWords == false)
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

bool notRepeatThePreviousSet(int* set,int* setLast, int countElm)
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

void printWord(int number, ofstream& file)
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

bool checkCountWord_a(int* set)
{
	for (int i = 0, userWord = 0; i < 5; i++)
	{
		if (set[i] == 1)
			userWord++;
		if (userWord == 2)
			return true;
	}
	return false;
}
