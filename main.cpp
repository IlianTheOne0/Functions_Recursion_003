#include <iostream>
#include <conio.h>
#include <random>
#include <iomanip>
#include <Windows.h>

using std::cout;
using std::endl;
using std::cin;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::setw;
using std::round;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template<typename TValue>
void delete_value(TValue*& value, char indicator)
{
	delete value;
	value = nullptr;
}
template<typename TValue>
void delete_value(TValue**& arr, int* size, bool indicator)
{
	for (int i = 0; i < *size; ++i)
	{
		delete[] arr[i];
	}
	delete[] arr;
	arr = nullptr;
}

void init(int** arr, int* size, int min, int max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);

    for (int i = 0; i < *size; i++)
    {
        arr[i] = new int[*size];
        for (int j = 0; j < *size; j++)
        {
            arr[i][j] = dist(gen);
        }
    }
}
void init(double** arr, int* size, double min, double max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(min, max);

    for (int i = 0; i < *size; i++)
    {
        arr[i] = new double[*size];
        for (int j = 0; j < *size; j++)
        {
            arr[i][j] = round(dist(gen) * 10) / 10.0;
        }
    }
}
void init(char** arr, int* size, int min, int max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);

    for (int i = 0; i < *size; i++)
    {
        arr[i] = new char[*size];
        for (int j = 0; j < *size; j++)
        {
            arr[i][j] = dist(gen);
        }
    }
}

template<typename TValueL, typename TValueR>
void print(TValueL* value, TValueR* message)
{
    cout << message << *value << endl;
}
template<typename TValueL, typename TValueR, typename TValue>
void print(TValueL** arr, int* size, TValue min, TValue max, int setw_value, TValueR* message)
{
    cout << message << endl;

    for (int i = 0; i < *size; i++)
    {
        for (int j = 0; j < *size; j++)
        {
            if (i == j)
            {
                SetConsoleTextAttribute(hConsole, 6);
                if (arr[i][j] == min)
                {
                    SetConsoleTextAttribute(hConsole, 4);
                }
                if (arr[i][j] == max)
                {
                    SetConsoleTextAttribute(hConsole, 2);
                }
            }

            cout << setw(setw_value) << arr[i][j] << " ";

            SetConsoleTextAttribute(hConsole, 7);
        }
        cout << endl;
    }
}

template<typename TValue>
void sorting(TValue** arr, int* size)
{
    for (int i = 0; i < *size; ++i) {
        for (int k = 1; k < *size; ++k) {
            TValue key = arr[i][k];
            int j = k - 1;

            while (j >= 0 && arr[i][j] > key) {
                arr[i][j + 1] = arr[i][j];
                j = j - 1;
            }
            arr[i][j + 1] = key;
        }
    }
}

template<typename TReturn, typename TValue>
TReturn _max(TValue** arr, int* size)
{
    TReturn max = arr[0][0];

    for (int i = 0; i < *size; i++)
    {
        if (arr[i][i] > max)
        {
            max = arr[i][i];
        }
    }

    return max;
}
template<typename TReturn, typename TValue>
TReturn _min(TValue** arr, int* size)
{
    TReturn min = arr[0][0];

    for (int i = 0; i < *size; i++)
    {
        if (arr[i][i] < min)
        {
            min = arr[i][i];
        }
    }

    return min;
}

int main()
{
    cout << "Marking on the main diagonal of the matrix" << endl
        << "\t1. Min element: ";
    SetConsoleTextAttribute(hConsole, 4);
    cout << "value" << endl;
    SetConsoleTextAttribute(hConsole, 7);

    cout << "\t2. Max element: ";
    SetConsoleTextAttribute(hConsole, 2);
    cout << "value" << endl;
    SetConsoleTextAttribute(hConsole, 7);

    cout << "\t3. Ordinary element: ";
    SetConsoleTextAttribute(hConsole, 6);
    cout << "value" << endl;
    SetConsoleTextAttribute(hConsole, 7);
    cout << endl << endl << endl;


	int* size = new int{ 5 };

    int** matrix0 = new int*[*size];
	init(matrix0, size, -9, 9);
    int matrix0min = _min<int, int>(matrix0, size);
    int matrix0max = _max<int, int>(matrix0, size);
    print<int, const char>(matrix0, size, matrix0min, matrix0max, 3, "First matrix:");
    cout << endl;
    sorting<int>(matrix0, size);
    matrix0min = _min<int, int>(matrix0, size);
    matrix0max = _max<int, int>(matrix0, size);
    print<int, const char>(matrix0, size, matrix0min, matrix0max, 3, "Sorted first matrix:");
    cout << endl << endl << endl;
    delete_value(matrix0, true);

    double** matrix1 = new double* [*size];
    init(matrix1, size, -9.9, 9.9);
    double matrix1min = _min<double, double>(matrix1, size);
    double matrix1max = _max<double, double>(matrix1, size);
    print<double, const char, double>(matrix1, size, matrix1min, matrix1max, 5, "Second matrix:");
    cout << endl;
    sorting<double>(matrix1, size);
    matrix1min = _min<double, double>(matrix1, size);
    matrix1max = _max<double, double>(matrix1, size);
    print<double, const char, double>(matrix1, size, matrix1min, matrix1max, 5, "Sorted second matrix:");
    cout << endl << endl << endl;
    delete_value(matrix1, true);
    
    char** matrix2 = new char* [*size];
    init(matrix2, size, 97, 122);
    int matrix2min = _min<int, char>(matrix2, size);
    int matrix2max = _max<int, char>(matrix2, size);
    print<char, const char, char>(matrix2, size, matrix2min, matrix2max, 2, "Third matrix:");
    cout << endl;
    sorting<char>(matrix2, size);
    matrix2min = _min<int, char>(matrix2, size);
    matrix2max = _max<int, char>(matrix2, size);
    print<char, const char, char>(matrix2, size, matrix2min, matrix2max, 2, "Sorted third matrix:");
    cout << endl << endl << endl;
    delete_value(matrix2, true);
    
    delete_value(size, ' ');


	char ch = _getch();
	return 0;
}