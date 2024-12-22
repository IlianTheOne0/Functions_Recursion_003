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
void print(TValueL* arr, int* size, TValueR* message)
{
    cout << message << endl;

    for (int i = 0; i < *size; i++)
    {
        cout << setw(2) << arr[i] << " ";
    }
    cout << endl;
}
template<typename TValueL, typename TValueR>
void print(TValueL** arr, int* size, TValueR* message)
{
    cout << message << endl;

    for (int i = 0; i < *size; i++)
    {
        for (int j = 0; j < *size; j++)
        {
            cout << setw(2) << arr[i][j] << " ";
        }
        cout << endl;
    }
}
template<typename TValueL, typename TValueR>
void print(TValueL*** arr, int* size, TValueR* message)
{
    cout << message << endl;

    for (int i = 0; i < *size; i++)
    {
        for (int j = 0; j < *size; j++)
        {
            for (int k = 0; k < *size; k++)
            {
                cout << setw(2) << arr[i][j][k] << " ";
            }
            cout << "    ";
        }
        cout << endl;
    }
}

int main()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 99);


    int* size = new int{ 5 };

    int* arr0 = new int[*size];
    init<int>(arr0, size, dist, gen);
    print<int, const char>(arr0, size, "One-dimensional array: ");
    cout << endl << endl;

    int** arr1 = new int* [*size];
    init<int>(arr1, size, dist, gen);
    print<int, const char>(arr1, size, "Two-dimensional array: ");
    cout << endl << endl;

    int*** arr2 = new int** [*size];
    init<int>(arr2, size, dist, gen);
    print<int, const char>(arr2, size, "Three-dimensional array: ");
    cout << endl << endl;


    int* value0 = init<int, int>(dist, gen);
    print<int, const char>(value0, "First value: ");

    int* value1 = init<int, int>(dist, gen);
    print<int, const char>(value1, "Second value: ");

    int* value2 = init<int, int>(dist, gen);
    print<int, const char>(value2, "Third value: ");


    delete_value<int>(arr0, false);
    delete_value<int>(arr1, size, false);
    delete_value<int>(arr2, size, false);
    delete_value<int>(size, ' ');
    delete_value<int>(value0, ' ');
    delete_value<int>(value1, ' ');
    delete_value<int>(value2, ' ');

    char ch = _getch();
    return 0;
}