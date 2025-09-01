#include <iostream>
#include <windows.h>
#include <algorithm>
using namespace std;

class Array {
	unsigned int capacity = 10; // при створенні масиву, він одразу для себе робить запас пам'яті на 10 елементів
	int* data = new int[capacity];
	unsigned int length = 0; // фактична (реальна) кількість елементів, присутніх у масиві

public:
	Array() {}

	void AddToBack(int value) {
		if (length < capacity) // якщо виділенної зарання пам'яті ВИСТАЧАЄ для додавання чергового елемента
			data[length] = value;
		else { // АЛЕ ЯКЩО МІСЦЯ ВЖЕ НЕ ВИСТАЧАЄ, ТО
			// треба перевиділити пам'ять
			capacity *= 2; // збільшуємо запас пам'яті у 2 рази (можна і в 1.5, можна і в 1.2)
			// якщо був запас 10 елементів, то стане 20
			// якщо запас був 20 елементів, то стане 40, і тд
			int* temp = new int[capacity]; // новий масив буде в 2 рази більше по пам'яті
			// але в старому масиві все ще усього 10 елементів, тому цикл треба написати так, щоб зачепити лише старі елементі зі старого масиву
			for (int i = 0; i < length; i++) {
				temp[i] = data[i];
			}
			// в новий масив в кінець (по індексу 10) пишеться ОДИНАДЦЯТИЙ елемент
			temp[length] = value;
			delete[] data; // в цілях запобігання витокам пам'яті, чистимо пам'ять від старого масиву
			data = temp; // переставляємо покажчик на новий масив
		}
		length++;
	}

	void AddToFront(int value) {
		if (length < capacity) { // ще є вільна пам'ять під черговий елмент
			// перевиділяти пам'ять на 1 елемент кожен раз - погана ідея (якщо елементів буде більше ніж 300000+ то все буде відбуватися максимально повільно)
			// при тому що пам'ять вже виділена (є кепесіті), то доведеться зробити зсув для всіх існуючих елементів на 1 вправо
			for (int i = length - 1; i >= 0; i--) { // зсув іде справа наліво (тому що якщо робити його зліва направо, з початку масива в кінець) то можна втратити існуючі елементи
				data[i + 1] = data[i];
			}
			data[0] = value;
		}
		else { // АЛЕ ЯКЩО МІСЦЯ ВЖЕ НЕ ВИСТАЧАЄ, ТО
			// треба перевиділити пам'ять
			capacity *= 2; // збільшуємо запас пам'яті у 2 рази (можна і в 1.5, можна і в 1.2)
			// якщо був запас 10 елементів, то стане 20
			// якщо запас був 20 елементів, то стане 40, і тд
			int* temp = new int[capacity]; // новий масив буде в 2 рази більше по пам'яті
			// але в старому масиві все ще усього 10 елементів, тому цикл треба написати так, щоб зачепити лише старі елементі зі старого масиву
			for (int i = 0; i < length; i++) {
				temp[i + 1] = data[i];
			}
			// в новий масив в початок (по індексу 0) пишеться ОДИНАДЦЯТИЙ елемент
			temp[0] = value;
			delete[] data; // в цілях запобігання витокам пам'яті, чистимо пам'ять від старого масиву
			data = temp; // переставляємо покажчик на новий масив
		}
		length++;
	}

	// переписати метод, тому що він не враховує кепесіті!!!
	void RemoveFromBack() {
		if (length == 0) {
			cout << "array is empty, there is NOTHING to delete!\n";
			return;
		}

		length--;

		if (length > 0 && length < (capacity / 3))
		{
			capacity /= 2;
			int* temp = new int[capacity];
			for (int i = 0; i < length - 1; i++)
			{
				temp[i] = data[i];
			}
			delete[] data;
			data = temp;
		}
	}

	// написати:
	// RemoveFromFront
	// Insert(100, 5)
	// RemoveByIndex(4);
	// RemoveByValue(10);
	// Sort();
	// Reverse();
	//Shuffle();

	void RemoveFromFront()
	{
		if (length == 0) {
			cout << "array is empty, there is NOTHING to delete!\n";
			return;
		}

		for (int i = 0; i < length - 1; i++)
		{
			data[i] = data[i + 1];
		}

		length--;

		if (length > 0 && length < (capacity / 3))
		{
			capacity /= 2;
			int* temp = new int[capacity];
			for (int i = 0; i < length; i++)
			{
				temp[i] = data[i];
			}
			delete[] data;
			data = temp;
		}
	}

	void Insert(int value, int index)
	{
		if (index > length)
		{
			cout << "index is out of diapason\n";
			return;
		}

		if (length < capacity)
		{
			for (int i = length - 1; i >= index; i--)
			{
				data[i + 1] = data[i];
			}
			data[index] = value;
			length++;
		}
		else
		{
			capacity *= 2;
			int* temp = new int[capacity];
			for (int i = 0; i < index; i++)
			{
				temp[i] = data[i];
			}
			temp[index] = value;
			for (int i = index; i < length; i++)
			{
				temp[i + 1] = data[i];
			}
			delete[] data;
			data = temp;
			length++;
		}
		
	}

	void RemoveByIndex(int index)
	{
		if (index >= length)
		{
			cout << "index is out of diapason\n";
			return;
		}

		if (length == 0) {
			cout << "array is empty, there is NOTHING to delete!\n";
			return;
		}

		for (int i = index; i < length - 1; i++)
		{
			data[i] = data[i + 1];
		}

		length--;

		if (length > 0 && length < (capacity / 3))
		{
			capacity /= 2;
			int* temp = new int[capacity];
			for (int i = 0; i < length; i++)
			{
				temp[i] = data[i];
			}
			delete[] data;
			data = temp;
		}
	}

	void RemoveByValue(int value)
	{
		if (length == 0) {
			cout << "array is empty, there is NOTHING to delete!\n";
			return;
		}

		int newlength = 0;
		for (int i = 0; i <= length - 1; i++)
		{
			if (data[i] != value)
			{
				data[newlength] = data[i];
				newlength++;
			}
			else
				continue;
		}

		length = newlength;

		/*
		* вльтернативный, более узконаправленный, вариант
		for (int i = length - 1; i > 0; i--)
		{
			if (data[i] == value)
				RemoveByIndex(i);
		}
		*/
		
		if (length > 0 && length < (capacity / 3))
		{
			capacity /= 2;
			int* temp = new int[capacity];
			for (int i = 0; i < length; i++)
			{
				temp[i] = data[i];
			}
			delete[] data;
			data = temp;
		}

	}

	void Sort()
	{
		sort(data, data + length);
	}

	void Reverse()
	{
		int* temp = new int[length];
		for (int i = 0; i < length; i++)
			temp[i] = data[length - i - 1];
		delete[] data;
		data = temp;
	}

	void Shuffle()
	{
		for (int i = 0; i < 10000; i++)
		{
			int ri1 = rand() % length;
			int ri2 = rand() % length;
			swap(data[ri1], data[ri2]);
		}
	}

	// додати інформацію про ленс та кепесіті
	void Print() const {
		if (length == 0) {
			cout << "array is empty!\n";
		}
		else {
			cout << "elements of the array: ";
			for (int i = 0; i < length; i++)
			{
				cout << data[i] << " ";
			}
			cout << "\n";
		}

		cout << "length: " << length << "\n"; //
		cout << "capacity: " << capacity << "\n"; //
	}

	~Array() {
		cout << "D-TOR\n";
		if (data != nullptr) {
			delete[] data;
		}
	}

	// переписати!!! кепесіті не враховано!!!
	Array(const Array& original) {
		cout << "COPY C-TOR\n";
		this->length = original.length;
		this->capacity = original.capacity; //
		this->data = new int[capacity]; //
		for (int i = 0; i < length; i++)
			this->data[i] = original.data[i];
	}
	void Clear() {
		delete[] data;
		data = nullptr;
		length = 0;
		capacity = 0;
	}

	unsigned int GetLength() const {
		return length;
	}

	unsigned int GetCapacity() const
	{
		return capacity;
	}

	int* GetData() const
	{
		return data;
	}

	//hw
	Array& operator = (const Array& a)
	{
		this->length = a.length;

		if (this->data != nullptr)
		{
			delete[] this->data;
		}

		this->data = new int[a.length];

		for (int i = 0; i < a.length; i++)
		{
			this->data[i] = a.data[i];
		}

		return *this;
	}

	bool operator ==(const Array& a)
	{
		for (int i = 0; i < length; i++)
		{
			if (this->data[i] == a.data[i])
				return true;
			else
				return false;
		}
	}

	bool operator != (const Array & a)
	{
		for (int i = 0; i < length; i++)
		{
			if (this->data[i] != a.data[i])
				return true;
			else
				return false;
		}
	}

	int& operator [](int index)
	{
		return data[index];
	}
};

// загальний синтаксис як зробити перевантаження у вигляді глобальної функції

// тип_результату operator значок_операції (параметри) {
	// список дій
// }

void operator +=(Array& a, int value) {
	cout << "HELLO FROM += function !!!\n";
	a.AddToBack(value);
}

// не можна зробити первантаження для вже існуючих операндів
//void operator << (ostream& os, const int& a) {
//	cout << "cout << !!!\n";
//}

ostream& operator << (ostream& cout, const Array& a) {
	// cout << "cout << !!!\n";
	a.Print();
	return cout;
}

void operator >> (istream& cin, Array& a) {
	cout << "cin >> !!!\n";
	// a.Array::~Array(); // явний виклик деструктора
	// a.Clear();
	while (a.GetLength() > 0) {
		a.RemoveFromBack();
	}
	int count;
	cout << "How many elements do you need? ";
	cin >> count; // 5
	for (int i = 0; i < count; i++)
	{
		int value;
		cout << "Please, enter value for element # " << i << ": ";
		cin >> value;
		a.AddToBack(value);
	}
}

int main() {
	SetConsoleOutputCP(1251);
	srand(time(0));

	Array a;
	//Array b;
	//cin >> a;
	// operator >> (cin, a);

	cout << a;
}