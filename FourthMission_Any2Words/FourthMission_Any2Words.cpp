#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

void permutationsWithRepeat(ofstream&, int);
bool nextSequencePermutationsWithRepeat(int*, size_t);
bool findIndexElm_firstOccurrence_whichLessCurrent(int&, int*);
void sortTheRestOfTheSequence(int*, int, size_t);
void fillInTheSet(int*, int[3], int);
int inputSymbol();
int indexWord(char symbolRepeat);
size_t length_7_9(int);

void print(int*, int, ofstream&, int*, int&);
void printWord(int, ofstream&);
bool checkCountWord_userWords(int*, int[3], int);
bool f2_s2_t3(int firstUserWord_2repeat, int secondUserWord_2repeat, int thirdUserWord_3repeat);
bool notRepeatThePreviousSet(int*, int*, int);
void countUserWord(int set, int symbolRepeat, int& k);

int main()
{
	setlocale(LC_ALL, "ru");
	cout << " \t\tКомбинаторные алгоритмы #4\n";

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
			cout << " 1.Построить все слова длины 7, в которых ровно одна буквы повторяется два раза\n и ровно одна буква повторяется 3 раза, остальные не повторятся."
				"\n 2.Построить все слова длины 9, в которых ровно 2 буквы повторяются два раза\n и одна буква повторяется 3 раза, остальные буквы не повторяются."
				"\n 3.Выход.\n";

			cout << " Выбор пал на ----> ";
			int choice = 0; cin >> choice;
			switch (choice)
			{
			case 1:
				file << "Все слова длины 7, в которых ровно одна буква повторяется два раза\n и ровно одна буква повторяется 3 раза, остальные не повторятся.\n";
				permutationsWithRepeat(file, 7);
				cout << "Данные успешно записаны в файл\n";
				break;
			case 2:
				file << "Все слова длины 9, в которых ровно 2 буквы повторяются два раза\n и одна буква повторяется 3 раза, остальные буквы не повторяются.\n";
				permutationsWithRepeat(file, 9);
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
		return 0;
	}
	catch (...) {}
	
}

void permutationsWithRepeat(ofstream& file, int length)
{
	int word = 0;
	vector<int>saveFirstWord;
	do
	{
		word++;
		int symbolsRepeat[3]{ 0,0,0 };
		symbolsRepeat[0] = word;
		if (word == 6)
			break;

		if (length == 9)
		{
			//TODO: для второй буквы добавить проверку
			int word2 = 1;
			vector<int> saveWord;
			do
			{
				symbolsRepeat[1] = 0;
				for (int i = 0; i < 6; i++)
				{
					if (symbolsRepeat[0] != i + 1)
					{
						bool repeatWord = false;
						for (vector<int>::iterator it = saveFirstWord.begin(); it < saveFirstWord.end(); it++)
						{
							if (*it == i + 1)
							{
								repeatWord = true;
								break;
							}
						}
						if (repeatWord == false)
						{
							for (vector<int>::iterator it = saveWord.begin(); it < saveWord.end(); it++)
							{
								if (*it == i + 1)
								{
									repeatWord = true;
									break;
								}
							}
							if (repeatWord == false)
							{
								saveWord.push_back(i + 1);
								symbolsRepeat[1] = i + 1;
								break;
							}
						}						
				
					}
				}
				if (symbolsRepeat[1] == 0)
					break;
				int word3 = 1;
				vector<int> saveWord2;
				do
				{
					symbolsRepeat[2] = 0;
					for (int i = 0; i < 6; i++)
					{
						if (symbolsRepeat[0] != i + 1 && symbolsRepeat[1]!=i+1)
						{
							bool repeatWord = false;
							for (vector<int>::iterator it = saveWord2.begin(); it < saveWord2.end(); it++)
							{
								if (*it == i + 1)
								{
									repeatWord = true;
									break;
								}
							}
							if (repeatWord == false)
							{
								saveWord2.push_back(i + 1);
								symbolsRepeat[2] = i + 1;
								break;
							}

						}
					}
					if (symbolsRepeat[2] != 0)
					{

						int* set = new int[length + 2];
						fillInTheSet(set, symbolsRepeat, length_7_9(length));

						int* setLast = new int[length + 2]{};
						int indexLine = 0;

						if (checkCountWord_userWords(set, symbolsRepeat, length))
							print(set, length, file, setLast, indexLine);

						while (nextSequencePermutationsWithRepeat(set, length_7_9(length)))
						{
							if (checkCountWord_userWords(set, symbolsRepeat, length) == true)
							{
								print(set, length, file, setLast, indexLine);
							}
						}
						delete[] set;
					}

					word3++;
				} while (word3<5);
				
				word2++;
			} while (word2 < 6);
			saveFirstWord.push_back(word);
		}
		else
		{
			int word2 = 1;
			vector<int> saveWord;
			do
			{
				for (int i = 0; i < 6; i++)
				{
					if (symbolsRepeat[0] != i + 1)
					{
						bool repeatWord = false;
						for (vector<int>::iterator it = saveWord.begin();it< saveWord.end();it++)
						{
							if (*it == i + 1)
							{
								repeatWord = true;
								break;
							}
						}
						if (repeatWord == false)
						{
							saveWord.push_back(i + 1);
							symbolsRepeat[2] = i + 1;
							break;
						}
													
					}
				}
				int* set = new int[length + 2];
				fillInTheSet(set, symbolsRepeat, length_7_9(length));

				int* setLast = new int[length + 2]{};
				int indexLine = 0;

				if (checkCountWord_userWords(set, symbolsRepeat, length))
					print(set, length, file, setLast, indexLine);

				while (nextSequencePermutationsWithRepeat(set, length_7_9(length)))
				{
					if (checkCountWord_userWords(set, symbolsRepeat, length) == true)
					{
						print(set, length, file, setLast, indexLine);
					}
				}
				delete[] set;
				word2++;
			} while (word2<6);
			
		}


		//saveFirstWord.push_back(word);

	} while (word<6);
	
}

size_t length_7_9(int length)
{
	return length==7? 9 : 10;
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

void fillInTheSet(int* set, int symbolsRepeat[3], int length)
{
	for (int i = 0, numberWord = 1; i < length; i++, numberWord++)
	{
		if (numberWord != symbolsRepeat[0] && numberWord != symbolsRepeat[1] && numberWord != symbolsRepeat[2])
		{
			set[i] = numberWord;
		}
		else
		{
			if (numberWord != symbolsRepeat[2])
			{
				set[i] = numberWord;
				set[i + 1] = numberWord;
				i++;
			}
			else
			{
				set[i] = numberWord;
				set[i + 1] = numberWord;
				set[i + 2] = numberWord;
				i += 2;
			}
			
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
	int static allIndexLineFile = 0;
	if (notRepeatThePreviousSet(currentSet, pastSet, countElm) == true)
	{
		allIndexLineFile++;
		indexLine++;
		file << allIndexLineFile << " --> " << indexLine << " : ";
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

bool checkCountWord_userWords(int* set, int userWords[3], int length)
{
	for (int i = 0, firstUserWord = 0, secondUserWord = 0,thirdUserWord = 0; i < length; i++)
	{
		if (userWords[1] == 0)
		{
			countUserWord(set[i], userWords[0], firstUserWord);
			countUserWord(set[i], userWords[2], thirdUserWord);
			if (firstUserWord == 2 && thirdUserWord==3)
				return true;
		}
		else
		{
			countUserWord(set[i], userWords[0], firstUserWord);
			countUserWord(set[i], userWords[1], secondUserWord);
			countUserWord(set[i], userWords[2], thirdUserWord);
			if (f2_s2_t3(firstUserWord, secondUserWord, thirdUserWord))
				return true;
		}
	}
	return false;
}

bool f2_s2_t3(int firstUserWord_2repeat, int secondUserWord_2repeat, int thirdUserWord_3repeat)
{
	return firstUserWord_2repeat == 2 && secondUserWord_2repeat == 2 && thirdUserWord_3repeat == 3;
}

void countUserWord(int word, int userWord, int& k)
{
	if (word == userWord)
		k++;
}
