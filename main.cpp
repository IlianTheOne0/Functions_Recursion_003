#include <iostream>
#include <conio.h>

using std::cout;
using std::endl;
using std::cin;

template<typename TValue>
void delete_value(TValue*& value)
{
    delete value;
    value = nullptr;
}

template<typename TReturn, typename TValue>
TReturn* get_value(TValue message)
{
    TReturn result;

    cout << message;
    cin >> result;

    return new TReturn(result);
}

int main()
{
    int* number1 = get_value<int, const char[]>("Enter the first number: ");
    int* number2 = get_value<int, const char[]>("Enter the second number: ");


    delete_value(number1);
    delete_value(number2);

    char ch = _getch();
    return 0;
}