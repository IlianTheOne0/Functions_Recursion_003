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
TReturn rec_pow(TValue* number, TValue* value)
{
    if (*value == 0)
        return 1;
    TValue new_value = *value - 1;
    return TReturn(*number * rec_pow<int, int>(number, &new_value));
}

int main()
{
    int* number1 = get_value<int, const char[]>("Enter the number: ");
    int* number2 = get_value<int, const char[]>("Enter the number: ");
    
    cout << "Result: " << rec_pow<int, int>(number1, number2) << endl;

    delete_value(number1);
    delete_value(number2);

    char ch = _getch();
    return 0;
}