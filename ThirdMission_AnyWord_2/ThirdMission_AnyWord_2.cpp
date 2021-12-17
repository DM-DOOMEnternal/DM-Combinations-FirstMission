 
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

void permutationsWithRepeat(ofstream&,int);
bool nextSequencePermutationsWithRepeat(int*, size_t);
bool findIndexElm_firstOccurrence_whichLessCurrent(int&, int*);
void sortTheRestOfTheSequence(int*, int, size_t);
void fillInTheSet(int*, int[2],int);
int inputSymbol();
int indexWord(char symbolRepeat);

void print(int*, int, ofstream&, int*, int&);
void printWord(int, ofstream&);
bool checkCountWord_userWords(int*,int[2],int);
bool notRepeatThePreviousSet(int*, int*, int);
void countUserWord(int set, int symbolRepeat, int& k);

int main()
{
	setlocale(LC_ALL, "ru");
	cout << " \t\tКомбинаторные алгоритмы #3\n";

	try
	{
		cout << " Все данные записываются в файл. Введите путь файла\n (формата Диск:\{папка}\ файл.формат ) :\n";
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
			cout << " 1.Построить все слова длины 6, в которых ровно две буквы повторяются два раза, остальные не повторятся."
				"\n 2.Построить все слова длины 5, в которых ровно одна буква повторяется два раза, остальные буквы не повторяются.\n"
				"\n 3.Выход.\n";

			cout << " Выбор пал на ----> ";
			int choice = 0; cin >> choice;
			switch (choice)
			{
			case 1:
				file << "Все слова длины 6, в которых ровно две буквы повторяются два раза, остальные не повторятся.\n";
				permutationsWithRepeat(file, 6);
				cout << "Данные успешно записаны в файл\n";
				break;
			case 2:
				file << "Все слова длины 5, в которых ровно одна буква повторяется два раза, остальные буквы не повторяются\n";
				permutationsWithRepeat(file, 5);
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
	catch (const char* exception)
	{
		cerr << " Error: " << exception << "\n";
	}
	catch (...) {}
	
}

void permutationsWithRepeat(ofstream & file,int length) 
{
	int symbolsRepeat[2]{ 0,0 };
    symbolsRepeat[0] =inputSymbol();
	if (length == 6)
	{
		symbolsRepeat[1] = inputSymbol();
	}
		
	int* set = new int[length+2];
	fillInTheSet(set, symbolsRepeat, length + 2);

	int* setLast = new int[length+2]{};
	int indexLine = 0;

	if(checkCountWord_userWords(set,symbolsRepeat,length))
		print(set, length, file, setLast, indexLine);

	while (nextSequencePermutationsWithRepeat(set, length+2))
	{
		if (checkCountWord_userWords(set,symbolsRepeat,length) == true)
		{
			print(set, length, file, setLast, indexLine);
		}
	}
	delete[] set;
}

int inputSymbol()
{
	char symbolRepeat = ' ';
	cout << " Введите символ из множества, который будет повторяться два раза : ";
	cin >> symbolRepeat;
	do
	{
		if (symbolRepeat >= 'a' && symbolRepeat <= 'f')
			break;
		else
			cout << " Данный символ не входит во множество. Введите заново : ";
		cin >> symbolRepeat;

	} while (true);
	
	return indexWord(symbolRepeat);
}

int indexWord(char symbolRepeat)
{
	switch (symbolRepeat)
	{
	case 'a':
		return 1;
	case 'b':
		return 2;
	case 'c':
		return 3;
	case 'd':
		return 4;
	case 'e':
		return 5;
	case 'f':
		return 6;
	default:
		return 0;
	}
}

void fillInTheSet(int* set, int symbolsRepeat[2],int length)
{
	for (int i = 0,numberWord=1; i < length; i++,numberWord++)
	{
		if (numberWord != symbolsRepeat[0] && numberWord!=symbolsRepeat[1])
		{
			set[i] = numberWord;
		}
		else
		{
			set[i] = numberWord;
			set[i + 1] = numberWord;
			i++;
		}
	}
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


void print(int* currentSet, int countElm, ofstream & file, int* pastSet, int& indexLine)
{
	if (notRepeatThePreviousSet(currentSet, pastSet, countElm) == true)
	{
		indexLine++;
		file << indexLine << " : ";
		for (int i = 0; i < countElm; i++)
		{
			printWord(currentSet[i], file);
			pastSet[i] = currentSet[i];
		}
		file << endl;
		cout << endl;
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
		return false;
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

bool checkCountWord_userWords(int* set,int userWords[2],int length)
{
	for (int i = 0, firstUserWord = 0,secondUserWord=0; i < length; i++)
	{
		if (userWords[1] == 0)
		{
		    countUserWord(set[i], userWords[0], firstUserWord);
			if (firstUserWord == 2)
				return true;
		}
		else
		{
			countUserWord(set[i], userWords[0], firstUserWord);
			countUserWord(set[i], userWords[1], secondUserWord);
			if (firstUserWord == 2 && secondUserWord == 2)
				return true;
		}
		
	}
	return false;
}

void countUserWord(int word, int userWord, int& k)
{
	if (word == userWord)
		k++;
}
