#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

void accommodationWithRepetitions(ofstream&);
void inputUserAlphabet(std::string& s);
bool nextSequence(int*, size_t, size_t, int);
void accommodationWithoutRepetitions(ofstream&);
bool nextSequence(int*, size_t, size_t);
void permutations(ofstream&);
bool nextSequencePermutations(int*, size_t);
void CombinationsWithoutRepetitions(ofstream&);
bool nextSequenceCombinations(int*, size_t, size_t);
void CombinationsWithRepetitions(ofstream&);
bool nextSequenceCombinationsWithRepeat(int*, size_t, size_t);
void Subsets(ofstream&);
int* fillSet(size_t);
int* fillSetFirstElm(int);
bool findIndexElm_firstOccurrence_whichLessCurrent(int&, int*);
void sortTheRestOfTheSequence(int*, int, size_t);
int maxSize(size_t, size_t);

void print(int*, int, ofstream&, string);
void translate(int, string, ofstream&);



int main()
{
	setlocale(LC_ALL, "ru");
	cout << " \t\tКомбинаторные алгоритмы \n";

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

	for (;;)
	{
		cout << "\n 1.Построить все размещения с повторениями по k элементов."
			"\n 2.Построить все размещения без повторений по k элементов."
			"\n 3. Построить все перестановки."
			"\n 4. Построить все сочетания без повторениями по k элементов."
			"\n 5. Построить все сочетания с повторений по k элементов."
			"\n 6. Построить все подмножества.\n";

		cout << " Выбор пал на ----> ";
		int choice = 0; cin >> choice;

		switch (choice)
		{
		case 1:
			accommodationWithRepetitions(file);
			cout << "Данные успешно записаны в файл\n";
			break;
		case 2:
			accommodationWithoutRepetitions(file);
			cout << "Данные успешно записаны в файл\n";
			break;
		case 3:
			permutations(file);
			cout << "Данные успешно записаны в файл\n";
			break;
		case 4:
			CombinationsWithoutRepetitions(file);
			cout << "Данные успешно записаны в файл\n";
			break;
		case 5:
			CombinationsWithRepetitions(file);
			cout << "Данные успешно записаны в файл\n";
			break;
		case 6:
			Subsets(file);
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
	}
}

void accommodationWithRepetitions(ofstream& file)
{
	cout << " Заполните множество элементами : ";
	string userAlphabet_set;
	inputUserAlphabet(userAlphabet_set);

	cout << " Введите k : ";
	size_t k = 0;
	cin >> k;

	int maxSizeArray = maxSize(userAlphabet_set.length(), k);

	int* set = fillSetFirstElm(maxSizeArray);

	file << " Размещения с повторениями из " << userAlphabet_set.length() << " элементов по " << k << " с начальным элементом" << userAlphabet_set[0] << "\n";
	int indexLineFile = 1;
	file << indexLineFile << " : ";
	print(set, k, file, userAlphabet_set);

	while (nextSequence(set, userAlphabet_set.length(), k, set[0]))
	{
		indexLineFile++;
		file << indexLineFile << " : ";
		print(set, k, file, userAlphabet_set);
	}

	delete[] set;
}

void inputUserAlphabet(std::string& s)
{
	cin.ignore();
	getline(cin, s);
	s.erase(remove(s.begin(), s.end(), ' '), s.end());
	int s2 = s.length();
	unique_copy(s.begin(), s.end(), back_inserter(s));//unique_copy(s.begin(), s.end(), ostreambuf_iterator<char>(cout)); удалить повторяющиеся элементы и вывести
	s.erase(0, s2);
}

bool nextSequence(int* set, size_t countElm, size_t k, int temp)
{
	int j = k - 1;
	while (j >= 0 && set[j] == countElm)
		j--;
	if (j == -1)
		return false;
	if (set[j] >= countElm)
		j--;
	set[j]++;
	if (j == k - 1)
		return true;
	for (int m = j + 1; m < k; m++)
		set[m] = temp;
	return true;
}

void accommodationWithoutRepetitions(ofstream & file)
{

	cout << " Заполните множество элементами : ";
	string userAlphabet_set;
	inputUserAlphabet(userAlphabet_set);

	cout << " Введите k : ";
	size_t k = 0;
	cin >> k;

	int* set = fillSet(userAlphabet_set.length());

	file << " Размещения без повторенияй из " << userAlphabet_set.length() << " элементов  по " << k << "\n";
	int indexLineFile = 1;
	file << indexLineFile << " : ";
	print(set, k, file, userAlphabet_set);

	while (nextSequence(set, userAlphabet_set.length(), k))
	{
		indexLineFile++;
		file << indexLineFile << " : ";
		print(set, k, file, userAlphabet_set);
	}

	delete[] set;
}

bool nextSequence(int* set, size_t countElm, size_t k)
{
	int j = 0;
	do
	{
		j = countElm - 1;
		if (findIndexElm_firstOccurrence_whichLessCurrent(j, set) == false)
			return false;

		int m = countElm - 1;
		while (set[j] >= set[m])
			m--;
		swap(set[j], set[m]);// текущий и последний поменять местами

		sortTheRestOfTheSequence(set, j, countElm);
	} while (j > k - 1);
	return true;
}


void permutations(ofstream & file)
{
	cout << " Заполните множество элементами : ";
	string userAlphabet_set;
	inputUserAlphabet(userAlphabet_set);

	int* set = fillSet(userAlphabet_set.length());

	file << " Перестановки из " << userAlphabet_set.length() << " элементов \n";
	int indexLineFile = 1;
	file << indexLineFile << " : ";
	print(set, userAlphabet_set.length(), file, userAlphabet_set);

	while (nextSequencePermutations(set, userAlphabet_set.length()))
	{
		indexLineFile++;
		file << indexLineFile << " : ";
		print(set, userAlphabet_set.length(), file, userAlphabet_set);
	}

	delete[] set;
}

bool nextSequencePermutations(int* set, size_t countElm)
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
}

void CombinationsWithoutRepetitions(ofstream & file)
{
	cout << " Заполните множество элементами : ";
	string userAlphabet_set;
	inputUserAlphabet(userAlphabet_set);

	cout << " Введите k : ";
	size_t k = 0;
	cin >> k;

	int* set = fillSet(userAlphabet_set.length());

	file << " Сочетания без повторений из " << userAlphabet_set.length() << " элементов по " << k << "\n";

	int indexLineFile = 1;
	file << indexLineFile << " : ";
	print(set, k, file, userAlphabet_set);
	if (userAlphabet_set.length() >= k)
	{
		while (nextSequenceCombinations(set, userAlphabet_set.length(), k))
		{
			indexLineFile++;
			file << indexLineFile << " : ";
			print(set, k, file, userAlphabet_set);
		}
	}
	else
		file << " k > n ---> = 0\n";

	delete[] set;
}


bool nextSequenceCombinations(int* set, size_t countElm, size_t k)
{
	int m = k;
	for (int i = m - 1; i >= 0; i--)
	{
		if (set[i] < countElm - m + i + 1)
		{
			set[i]++;
			for (int j = i + 1; j < m; j++)
				set[j] = set[j - 1] + 1;
			return true;
		}
	}
	return false;
}

void CombinationsWithRepetitions(ofstream & file)
{
	cout << " Заполните множество элементами : ";
	string userAlphabet_set;
	inputUserAlphabet(userAlphabet_set);

	cout << " Введите k : ";
	size_t k = 0;
	cin >> k;

	int maxSizeArray = maxSize(userAlphabet_set.length(), k);

	int* set = fillSetFirstElm(maxSizeArray);

	file << " Сочетания с повторенями из " << userAlphabet_set.length() << " элементов по " << k << " c начальным элементом " << set[0] << "\n";

	int indexLineFile = 1;
	file << indexLineFile << " : ";
	print(set, k, file, userAlphabet_set);
	if (userAlphabet_set.length() >= k)
	{
		while (nextSequenceCombinationsWithRepeat(set, userAlphabet_set.length(), k))
		{
			indexLineFile++;
			file << indexLineFile << " : ";
			print(set, k, file, userAlphabet_set);
		}
	}
	else
		file << " k > n ---> = 0\n";

	delete[] set;
}


bool nextSequenceCombinationsWithRepeat(int* set, size_t countElm, size_t k)
{
	int j = k - 1;
	while (set[j] == countElm && j >= 0)
		j--;
	if (j < 0)
		return false;
	set[j]++;
	if (j == k - 1)
		return true;
	for (int m = j + 1; m < k; m++)
		set[m] = set[j];
	return true;
}

void Subsets(ofstream & file)
{
	cout << " Заполните множество элементами : ";
	string userAlphabet_set;
	inputUserAlphabet(userAlphabet_set);

	int* set = fillSet(userAlphabet_set.length());

	file << " Множество из " << userAlphabet_set.length() << " элементов \n";
	int max = 1;
	for (int i = 0; i < userAlphabet_set.length(); i++)
		max *= 2;

	for (int i = 0; i < max; i++)
	{
		file << i << " : ";
		for (int j = 0; j < userAlphabet_set.length(); j++)
		{
			// if ((i >> j) & 1) //(сдвигает биты i на j  вправо , аналог, делить i на 2 в степ j) & если сдвиг даст бит 1 то будет true, аналог деление на 2 без остатка) 
			int temp = i / pow(2, j);
			if (temp % 2 != 0)//(если поставить четные то порядок от большего к меньшему) порядок от меньшего к большему
			{
				translate(set[j], userAlphabet_set, file);
			}

		}
		file << endl;
		cout << endl;
	}

	delete[] set;
}

int* fillSet(size_t countElm)
{
	int* set = new int[countElm];
	for (int i = 0; i < countElm; i++)
		set[i] = i + 1;
	return set;
}

int* fillSetFirstElm(int countElm)
{
	int* set = new int[countElm];
	for (int i = 0; i < countElm; i++)
		set[i] = 1;
	return set;
}

bool findIndexElm_firstOccurrence_whichLessCurrent(int& j, int* set)
{
	while (j != -1 && set[j] >= set[j + 1]) //ищем индекс эл-а(первое вхожд) который меньше текущего(j+1) 
		j--;

	if (j == -1)
		return false;
	return true;
}

int maxSize(size_t countElm, size_t k)
{
	return countElm > k ? countElm : k;
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


void print(int* set, int countElm, ofstream & file, string text)
{
	for (int i = 0; i < countElm; i++)
	{
		translate(set[i], text, file);
	}
	file << endl;
	cout << endl;
}

void translate(int elm, string text, ofstream & file)
{
	for (int i = 0; i < text.size(); i++)
	{
		if (elm == i + 1)
		{
			file << text[i] << " ";
			cout << text[i] << " ";
			break;
		}
	}
}
