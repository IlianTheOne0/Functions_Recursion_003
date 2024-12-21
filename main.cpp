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
TReturn display(TValue* number1, TValue* number2, TReturn result)
{
    result += *number1;
    if (*number1 == *number2)
    {
        return result;
    }

    (*number1)++;
    return display<TReturn, TValue>(number1, number2, result);
}


int main()
{
    int* number1 = get_value<int, const char[]>("Enter the first number: ");
    int* number2 = get_value<int, const char[]>("Enter the second number: ");

    if (*number2 < *number1)
    {
        int temp = *number1;
        *number1 = *number2;
        *number2 = temp;
    }
    int result{};
    cout << endl << "Result: " << display<int, int>(number1, number2, result) << endl;

    delete_value(number1);
    delete_value(number2);

    char ch = _getch();
    return 0;
}