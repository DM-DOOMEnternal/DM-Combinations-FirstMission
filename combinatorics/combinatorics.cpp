#include <iostream>
#include<cmath>
#include <fstream>
#include<string>
using namespace std;

void accommodationWithRepetitions(size_t ,ofstream&);
bool nextSequence(int*, size_t, size_t, int);
void accommodationWithoutRepetitions(size_t, ofstream&);
bool nextSequence(int* , size_t , size_t );
void permutations(size_t, ofstream&);
bool nextSequencePermutations(int* , size_t);
void CombinationsWithoutRepetitions(size_t , ofstream&);
bool nextSequenceCombinations(int* , size_t , size_t );
void CombinationsWithRepetitions(size_t, ofstream&);
bool nextSequenceCombinationsWithRepeat(int*, size_t, size_t);
void Subsets(size_t, ofstream&);
int* inputSet(size_t);
int* inputFirstElm(int);
bool findIndexElm_firstOccurrence_whichLessCurrent(int&, int*);
void sortTheRestOfTheSequence(int*, int, size_t);
int maxSize(size_t , size_t );
void print(int*, int, ofstream&);
void sort(int* , int );


int main()
{
	setlocale(LC_ALL, "ru");
	cout << " \t\tКомбинаторные алгоритмы \n";

	cout << " Все данные записываются в файл. Введите путь файла (формата Диск:\{папка}\ файл.формат )\n :";
	string pathFile="";
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
		cout << " \nВведите количество элементов : ";
		size_t countElm = 0;
		cin >> countElm;
		switch (choice)
		{
		case 1:
			accommodationWithRepetitions(countElm,file);
			cout << "Данные успешно записаны в файл\n";
			break;
		case 2:
			accommodationWithoutRepetitions(countElm,file);
			cout << "Данные успешно записаны в файл\n";
			break;
		case 3:
			permutations(countElm,file);
			cout << "Данные успешно записаны в файл\n";
			break;
		case 4:
			CombinationsWithoutRepetitions(countElm,file);
			cout << "Данные успешно записаны в файл\n";
			break;
		case 5:
			CombinationsWithRepetitions(countElm,file);
			cout << "Данные успешно записаны в файл\n";
			break;
		case 6:
			Subsets(countElm,file);
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
	
}//конец main

//-----------------Размещения с повторениями-------------------------
void accommodationWithRepetitions(size_t countElm,ofstream& file)
{
	cout << " Введите k : ";
	size_t k = 0;
	cin >> k;

	int maxSizeArray = maxSize(countElm, k);

	int* set = inputFirstElm(maxSizeArray);

	file << " Размещения с повторениями из " << countElm << " элементов по " << k << " с начальным элементом" << set[0] <<"\n";
	int i = 1;
	file << i << " : ";
	print(set, k,file);
	
	while (nextSequence(set, countElm, k, set[0]))
	{
		i++;
		file << i << " : ";
		print(set, k, file);		
	}
		
	delete[] set;
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
}//-----------------Размещения с повторениями-------------------------

//-----------------Размещения без повторений-------------------------
void accommodationWithoutRepetitions(size_t countElm, ofstream& file)
{
	cout << " Введите k : ";
	size_t k = 0;
	cin >> k;

	int* set = inputSet(countElm);

	file << " Размещения без повторенияй из " << countElm << " элементов  по " << k << "\n";
	sort(set, countElm);
	int i = 1;
	file << i << " : ";
	print(set, k,file);

	while (nextSequence(set, countElm, k))
	{
		i++;
		file << i << " : ";
		print(set, k, file);
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
}//-----------------Размещения без повторений-------------------------

//-----------------Перестановки-------------------------
void permutations(size_t countElm, ofstream& file)
{
	int* set = inputSet(countElm);

	file << " Перестановки из " << countElm << " элементов \n";
	sort(set, countElm);
	int i = 1;
	file << i << " : ";
	print(set, countElm,file);

	while (nextSequencePermutations(set, countElm))
	{
		i++;
		file << i << " : ";
		print(set, countElm, file);
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
}//-----------------Перестановки-------------------------

//-----------------Сочетания без повторений-------------------------
void CombinationsWithoutRepetitions(size_t countElm, ofstream& file)
{
	cout << " Введите k : ";
	size_t k = 0;
	cin >> k;

	int* set = inputSet(countElm);

	file << " Сочетания без повторений из " << countElm << " элементов по " << k << "\n";
	sort(set, countElm);

	int i = 1;
	file << i << " : ";
	print(set, k,file);
	if (countElm >= k)
	{
		while (nextSequenceCombinations(set, countElm, k))
		{
			i++;
			file << i << " : ";
			print(set, k, file);
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
}//-----------------Сочетания без повторений-------------------------

//-----------------Сочетания с повторениями-------------------------
void CombinationsWithRepetitions(size_t countElm, ofstream& file)
{
	cout << " Введите k : ";
	size_t k = 0;
	cin >> k;

	int maxSizeArray = maxSize(countElm, k);

	int* set = inputFirstElm(maxSizeArray);

	file << " Сочетания с повторениями из " << countElm << " элементов по " << k << " c начальным элементом " << set[0] << "\n";

	int i = 1;
	file << i << " : ";
	print(set, k,file);
	if (countElm >= k)
	{
		while (nextSequenceCombinationsWithRepeat(set, countElm, k))
		{
			i++;
			file << i << " : ";
			print(set, k, file);
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
}//-----------------Сочетания с повторениями-------------------------


void Subsets(size_t countElm, ofstream& file)
{
	int* set = inputSet(countElm);

	sort(set, countElm);
	file << " Множество из " << countElm << " элементов \n";
	int max = 1;
	for (int i = 0; i < countElm; i++)
		max *= 2;

	for (int i = 0; i < max; i++)
	{
		file << i << " : ";
		for (int j = 0; j < countElm; j++)
		{
			// if ((i >> j) & 1) //(сдвигает биты i на j  вправо , аналог, делить i на 2 в степ j) & если сдвиг даст бит 1 то будет true, аналог деление на 2 без остатка) 
			int temp = i / pow(2, j);
			if (temp % 2 != 0)//(если поставить четные то порядок от большего к меньшему) порядок от меньшего к большему
			{
				file << set[j] << " ";
				cout << set[j] << " ";
			}
				
		}
		file << endl;
		cout << endl;
	}
	
	delete[] set;
}

int* inputSet(size_t countElm)
{
	int* set = new int[countElm];
	cout << " Заполните множества элементами ( " << countElm << ") : ";
	for (int i = 0; i < countElm; i++)
		cin >> set[i];
	return set;
}

int* inputFirstElm(int countElm)
{
	int* set = new int[countElm];
	cout << " Введите начальный элемент : ";
	int temp = 0; cin >> temp;
	for (int i = 0; i < countElm; i++)
		set[i] = temp;
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

void sort(int* set, int countElm)
{
	for (int i = 0; i < countElm; i++)
	{
		for (int j = 0; j < countElm; j++)
			if (set[i] < set[j])
				swap(set[i], set[j]);
	}
}

void print(int* set, int countElm,ofstream& file)
{
	for (int i = 0; i < countElm; i++)
	{
		file << set[i] << " ";
		cout << set[i] << " ";
	}
	file << endl;
	cout << endl;
}