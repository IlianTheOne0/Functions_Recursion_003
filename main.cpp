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

template<typename TReturn, typename TValue>
TReturn display(TValue value)
{
    if (value == 0)
        return 1;

    cout << "*";

    TValue new_value = value - 1;
    return display<TReturn, TValue>(new_value);
}

int main()
{
    int* number = get_value<int, const char[]>("Enter the number of stars you want to display: ");

    cout << "Result: ";
    display<int, int>(*number);
    cout << endl;

    delete_value(number);

    char ch = _getch();
    return 0;
}