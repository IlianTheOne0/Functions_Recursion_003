#include <iostream>
#include <conio.h>
#include <random>
#include <Windows.h>

using std::cout;
using std::endl;
using std::cin;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template<typename TValue>
void delete_value(TValue*& value, char indicator)
{
	delete value;
	value = nullptr;
}
template<typename TValue>
void delete_value(TValue*& arr, bool indicator)
{
	delete[] arr;
	arr = nullptr;
}

int* breaking(int value)
{
	int* arr = new int[4];
	for (int i = 3; i >= 0; --i)
	{
		arr[i] = value % 10;
		value /= 10;
	}
	return arr;
}

template<typename TReturn, typename TValue>
TReturn guessing(TValue* bot, int* bot_arr, unsigned long long attempts)
{
	int input{};

	do {
		cout << "Enter the number: ";
		cin >> input;

		if (input > 9999 || input < 1000)
		{
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Incorrect number. Try again!" << endl;
			SetConsoleTextAttribute(hConsole, 7);
			continue;
		}
		break;
	} while (true);

	if (*bot == input)
	{
		system("cls");
		SetConsoleTextAttribute(hConsole, 2);
		cout << "Correct!" << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << "Number: " << *bot << endl;
		return attempts;
	}

	attempts++;

	int* input_arr = breaking(input);
	short bull = 0;
	short cow = 0;

	for (int* ptr0 = bot_arr; ptr0 < bot_arr + 4; ptr0++)
	{
		for (int* ptr1 = input_arr; ptr1 < input_arr + 4; ptr1++)
		{
			if (*ptr0 == *ptr1)
			{
				bull++;
				break;
			}
		}
	}

	for (int* ptr0 = bot_arr, *ptr1 = input_arr; ptr0 < bot_arr + 4; ptr0++, ptr1++)
	{
		if (*ptr0 == *ptr1)
		{
			cow++;
		}
	}

	delete_value(input_arr, true);

	cout << "Bulls: " << bull << endl << "Cows: " << cow << endl << endl;

	cout << endl;
	return guessing<TReturn, TValue>(bot, bot_arr, attempts);
}

int main()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(1000, 9999);

	int* number = new int{ dist(gen) };
	int* number_arr = breaking(*number);
	
	unsigned long long attempts{ 1 };
	cout << "Attempts: " << guessing<int, int>(number, number_arr, attempts) << endl;

	delete_value(number, ' ');
	delete_value(number_arr, true);

	char ch = _getch();
	return 0;
}
