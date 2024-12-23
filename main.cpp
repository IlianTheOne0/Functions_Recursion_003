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
TReturn GCD(TValue* number0, TValue* number1)
{
    if (*number1 == 0)
    {
        return *number0;
    }

    TReturn result = *number0 % *number1;

    return GCD<TReturn, TValue>(number1, &result);
}


int main()
{
    int* number0 = get_value<int, const char[]>("Enter the first number: ");
    int* number1 = get_value<int, const char[]>("Enter the second number: ");

    cout << endl << endl << "The greatest common divisor: " << GCD<int, int>(number0, number1) << endl;

    delete_value(number0);
    delete_value(number1);

    char ch = _getch();
    return 0;
}