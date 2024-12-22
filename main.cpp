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

template<typename TValue>
void init_arr(TValue* arr, int* size)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 99);

    for (int i = 0; i < *size; i++)
    {
        arr[i] = dist(gen);
    }
}

template<typename TValueL, typename TValueR>
void print_arr(TValueL* arr, int* size, TValueR* message)
{
    cout << message;
    for (int i = 0; i < *size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template<typename TValue>
void calc(TValue* arr, int i, int j = 1)
{
    if (j == 1)
    {
        cout << setw(2) << arr[i] << " == ";
    }

    if (j < 10)
    {
        cout << setw(2) << arr[j + i] << " | ";
        arr[i] += arr[j + i];
        calc<TValue>(arr, i, j + 1);
    }
    else
    {
        cout << "== " << arr[i] << endl;
    }
}

template<typename TValue>
TValue rangefinder(TValue* arr, int* size, int i)
{
    if (i == (*size - 10))
    {
        return *arr;
    }

    /*
    cout << setw(2) << arr[i] << " == ";
    for (int j = 1; j < 10; j++)
    {
        cout << setw(2) << arr[j + i] << " | ";

        arr[i] += arr[j + i];
    }
    cout << "== " << arr[i] << endl;
    */

    calc<int>(arr, i);

    return rangefinder<TValue>(arr, size, i + 1);
}

template<typename TValue>
void overwriting(TValue* arr, TValue* arr0, int* size)
{
    for (int i = 0; i < *size; ++i) {
        arr0[i] = arr[i];
    }
}

template<typename TValue>
void sorting(TValue* arr, int* size)
{
    for (int i = 1; i < *size; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

template<typename TValue>
int index_searcher(TValue* arr, TValue* arr0, int* size)
{
    int number = arr[10];
    int index;

    for (int i = 0; i < *size; i++)
    {
        if (arr0[i] == number)
        {
            index = i;
        }
    }

    return index;
}

int main()
{
    int* size = new int{ 100 };
    int* arr = new int[*size];
    init_arr<int>(arr, size);
    print_arr<int, const char>(arr, size, "Array: ");


    cout << endl << endl << endl << "Step 1. Calculations:" << endl;
    int i = 0;
    *arr = rangefinder<int>(arr, size, i);
    cout << endl;
    print_arr(arr, size, "Intermediate result: ");



    cout << endl << endl << endl << "Step 2. Sorting:" << endl;
    int* original_arr = new int[*size];
    overwriting<int>(arr, original_arr, size);
    sorting<int>(arr, size);
    print_arr(arr, size, "Sorted array: ");
    cout << endl;


    cout << endl << endl << endl << "Step 3. Find the position where the sequence of 10 numbers starts:" << endl;
    i = index_searcher(arr, original_arr, size);
    cout << "Thus, the sequence of digits whose sum is minimal began with " << i << " of the index" << endl;

    delete_value<int>(arr, false);
    delete_value<int>(original_arr, false);
    delete_value<int>(size, ' ');

    char ch = _getch();
    return 0;
}