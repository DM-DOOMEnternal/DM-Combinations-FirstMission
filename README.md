# DM-Combinations-FirstMission
 commit: combinatorics - 
 В начале задается путь к файлу для записи данных, затем выбирается что необходимо вычислить, после задается количество элементов, если необходимо задается k, и заполнение множества элементами.После программа вычисляет все возможные варианты и записывает в файл.
 
Краткое пояснение кода:

void accommodationWithRepetitions(size_t ,ofstream&); вычесление размещения с повторениями  
bool nextSequence(int*, size_t, size_t, int);
  
void accommodationWithoutRepetitions(size_t, ofstream&); вычесление размещения без повторений  
bool nextSequence(int* , size_t , size_t );

void permutations(size_t, ofstream&); Вычсиление перестановок  
bool nextSequencePermutations(int* , size_t);  

void CombinationsWithoutRepetitions(size_t , ofstream&); Вычисление сочетания без повторений  
bool nextSequenceCombinations(int* , size_t , size_t );  

void CombinationsWithRepetitions(size_t, ofstream&); Вычисление сочетания с повторениями  
bool nextSequenceCombinationsWithRepeat(int*, size_t, size_t);  

void Subsets(size_t, ofstream&); Вычисление всех подмножеств  

int* inputSet(size_t); заполнение множества  
int* inputFirstElm(int); заполнение множества начальным элементом  
bool findIndexElm_firstOccurrence_whichLessCurrent(int&, int*); найти индекс элемента который меньше следующего  
void sortTheRestOfTheSequence(int*, int, size_t); сортировка оставшихся элементов  
int maxSize(size_t , size_t ); макс размер массива (для __ с повторениями)  
void print(int*, int, ofstream&); вывыд/запись в файл  
void sort(int* , int ); сортировка массива  
-----------------------------------------------------------------------------------------конец combinatorics
