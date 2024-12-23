#include <iostream>
#include <conio.h>
#include <random>
#include <Windows.h>
#include <iomanip>

using std::cout;
using std::endl;
using std::cin;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::setw;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template<typename TValueL>
void delete_value(TValueL*& value, char indicator)
{
    delete value;
    value = nullptr;
}
template<typename TValueL>
void delete_value(TValueL*& arr, bool indicator)
{
    delete[] arr;
    arr = nullptr;
}
template<typename TValueL>
void delete_value(TValueL**& arr, int* size, bool indicator)
{
    for (int i = 0; i < *size; ++i)
    {
        delete[] arr[i];
    }
    delete[] arr;
    arr = nullptr;
}
template<typename TValueL>
void delete_value(TValueL***& arr, int* size, bool indicator)
{
    for (int i = 0; i < *size; ++i)
    {
        for (int j = 0; j < *size; ++j)
        {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;
    arr = nullptr;
}


template<typename TReturn, typename TValue>
TReturn* init(uniform_int_distribution<int> dist, mt19937& gen)
{
    return new TReturn(dist(gen));
}
template<typename TValue>
void init(TValue* arr, int* size, uniform_int_distribution<int> dist, mt19937& gen)
{
    for (int i = 0; i < *size; i++)
    {
        arr[i] = dist(gen);
    }
}
template<typename TValue>
void init(TValue** arr, int* size, uniform_int_distribution<int> dist, mt19937& gen)
{
    for (int i = 0; i < *size; i++)
    {
        arr[i] = new TValue[*size];
        for (int j = 0; j < *size; j++)
        {
            arr[i][j] = dist(gen);
        }
    }
}
template<typename TValue>
void init(TValue*** arr, int* size, uniform_int_distribution<int> dist, mt19937& gen)
{
    for (int i = 0; i < *size; i++)
    {
        arr[i] = new TValue * [*size];
        for (int j = 0; j < *size; j++)
        {
            arr[i][j] = new TValue[*size];
            for (int k = 0; k < *size; k++)
            {
                arr[i][j][k] = dist(gen);
            }
        }
    }
}

template<typename TValueL, typename TValueR>
void print(TValueL* value, TValueR* message)
{
    cout << message << *value << endl;
}
template<typename TValueL, typename TValueR>
void print(TValueL* arr, int* size, int max, TValueR* message)
{
    cout << message << endl;

    for (int i = 0; i < *size; i++)
    {
        if (arr[i] == max)
        {
            SetConsoleTextAttribute(hConsole, 4);
        }

        cout << setw(3) << arr[i] << " ";

        SetConsoleTextAttribute(hConsole, 7);
    }
    cout << endl;
}
template<typename TValueL, typename TValueR>
void print(TValueL** arr, int* size, int max, TValueR* message)
{
    cout << message << endl;

    for (int i = 0; i < *size; i++)
    {
        for (int j = 0; j < *size; j++)
        {
            if (arr[i][j] == max)
            {
                SetConsoleTextAttribute(hConsole, 4);
            }

            cout << setw(3) << arr[i][j] << " ";

            SetConsoleTextAttribute(hConsole, 7);
        }
        cout << endl;
    }
}
template<typename TValueL, typename TValueR>
void print(TValueL*** arr, int* size, int max, TValueR* message)
{
    cout << message << endl;

    for (int i = 0; i < *size; i++)
    {
        for (int j = 0; j < *size; j++)
        {
            for (int k = 0; k < *size; k++)
            {
                if (arr[i][j][k] == max)
                {
                    SetConsoleTextAttribute(hConsole, 4);
                }

                cout << setw(3) << arr[i][j][k] << " ";

                SetConsoleTextAttribute(hConsole, 7);
            }
            cout << "    ";
        }
        cout << endl;
    }
}

template<typename TReturn, typename TValue>
TReturn searcher(TValue* arr, int* size, bool definder)
{
    TReturn max = arr[0];

    for (int i = 1; i < *size; i++)
    {
        if (arr[i] > max) { max = arr[i]; }
    }

    return max;
}
template<typename TReturn, typename TValue>
TReturn searcher(TValue** arr, int* size)
{
    TReturn max = arr[0][0];

    for (int i = 0; i < *size; i++)
    {
        for (int j = 0; j < *size; j++)
        {
            if (arr[i][j] > max)
            {
                max = arr[i][j];
            }
        }
    }

    return max;
}
template<typename TReturn, typename TValue>
TReturn searcher(TValue*** arr, int* size)
{
    TReturn max = arr[0][0][0];

    for (int i = 0; i < *size; i++)
    {
        for (int j = 0; j < *size; j++)
        {
            for (int k = 0; k < *size; k++)
            {
                if (arr[i][j][k] > max)
                {
                    max = arr[i][j][k];
                }
            }
        }
    }

    return max;
}
template<typename TReturn, typename TValue>
TReturn searcher(TValue* number0, TValue* number1)
{
    TReturn max = *number0;

    if (*number1 > max)
    {
        max = *number1;
    }

    return max;
}
template<typename TReturn, typename TValue>
TReturn searcher(TValue* number0, TValue* number1, TValue* number2)
{
    TReturn max = *number0;

    if (*number1 > max)
    {
        max = *number1;
    }
    if (*number2 > max)
    {
        max = *number2;
    }

    return max;
}

int main()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 999);


    int* size = new int{ 5 };

    int* arr0 = new int[*size];
    init<int>(arr0, size, dist, gen);
    int arr0max = searcher<int, int>(arr0, size, true);
    print<int, const char>(arr0, size, arr0max, "One-dimensional array: ");
    print<int, const char>(&arr0max, "Max: ");
    cout << endl << endl;
    delete_value<int>(arr0, false);

    int** arr1 = new int* [*size];
    init<int>(arr1, size, dist, gen);
    int arr1max = searcher<int, int>(arr1, size);
    print<int, const char>(arr1, size, arr1max, "Two-dimensional array: ");
    print<int, const char>(&arr1max, "Max: ");
    cout << endl << endl;
    delete_value<int>(arr1, size, false);

    int*** arr2 = new int** [*size];
    init<int>(arr2, size, dist, gen);
    int arr2max = searcher<int, int>(arr2, size);
    print<int, const char>(arr2, size, arr2max, "Three-dimensional array: ");
    print<int, const char>(&arr2max, "Max: ");
    cout << endl << endl;
    delete_value<int>(arr2, size, false);

    delete_value<int>(size, ' ');


    int* value0 = init<int, int>(dist, gen);
    print<int, const char>(value0, "First value: ");

    int* value1 = init<int, int>(dist, gen);
    print<int, const char>(value1, "Second value: ");

    int* value2 = init<int, int>(dist, gen);
    print<int, const char>(value2, "Third value: ");
    
    cout << endl;

    int max = searcher<int, int>(value0, value1);
    print<int, const char>(&max, "Maximum value (first value, second value): ");
    max = searcher<int, int>(value0, value1, value2);
    print<int, const char>(&max, "Maximum value (first value, second value, third value): ");
        
    delete_value<int>(value0, ' ');
    delete_value<int>(value1, ' ');
    delete_value<int>(value2, ' ');


    char ch = _getch();
    return 0;
}