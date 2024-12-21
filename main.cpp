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

template<typename TValue>
void delete_value(TValue*& value)
{
    delete value;
    value = nullptr;
}

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


int main()
{
    int* size = new int{ 100 };
    int* arr = new int[*size];
    init_arr<int>(arr, size);
    print_arr<int, const char>(arr, size, "Array: ");

    delete_value<int>(arr, false);
    delete_value<int>(size, ' ');

    char ch = _getch();
    return 0;
}