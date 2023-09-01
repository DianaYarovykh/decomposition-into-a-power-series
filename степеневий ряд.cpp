#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

/*
Функція обчислює приблизне значення функції за рядом Тейлора-Маклорена, 
підраховує кількість кроків до заданої точності та повертає ці значення
*/
double calculation(double x, double e, int& n, double a)
{
    double q;

    if (n == 1) {
        a = 1 + x / 2;
    }
    if (abs(a) > e) {
        n++;
        q = ((3 - 2 * n) * x) / (2 * n);
        return a + calculation(x, e, n, a * q);
    }
    else {
        return 0;
    }
}
/*
Функція приймає значення х початку, кінця та крок, задану точність та 
вибір користувача за збереженням результатів у файл або вивід у консоль
*/
void rezults(double x_begin, double x_finish, double x_step, double e, int save)
{
    int n = 1;
    double a = 1;
    //відкриваємо файл для збереження туди даних
    FILE* f = NULL;
    const char* file_name = "D:\\My projects\\атап-2\\Курсовая\\output.txt";
    if (save == 1)
    {
        errno_t error_code = freopen_s(&f, file_name, "w+", stdout);
        if (error_code != 0) {
            cout << "Cannot open file.\n";
        }
    }
    // друкується початок таблиці
    printf("+-----------------------------------------------------------------------------+\n");
    printf("|   x    |    сумма    |   шаг   |  sqrt(1 + x)  |  эпсилон  |   погрешность  |\n");
    printf("+-----------------------------------------------------------------------------+\n");
    // за допомогою циклу друкуються значення
    while (x_begin <= x_finish)
    {
        double func_val = calculation(x_begin, e, n, a);
        printf("|  %4.1f  |  %.7f  |   %.03d   |   %.7lf   |  %.5f  |  %.10f  |\n", x_begin, func_val, n, sqrt(1 + x_begin), e, abs(abs(func_val) - sqrt(1 + x_begin)));
        x_begin += x_step;
        n = 1;
    }
    printf("+-----------------------------------------------------------------------------+\n");
    if (save == 1 && f != NULL) {
        fclose(f);
    }
}
//Функція приймає значення х початку та кінця, крок, точність та вибір виводу результатів
void print_consol(double x_begin, double x_finish, double x_step, double e, int save)
{
    setlocale(LC_ALL, "Russian");
    //цикли в цій функції перевіряють правильність вводу значень
    cout << "Введите начало диапазона: ";
    cin >> x_begin;
    while (x_begin < -1) {
        cout << "Введите начало диапазона > -1 : ";
        cin >> x_begin;
    }
    cout << "Введите конец диапазона: ";
    cin >> x_finish;
    while (x_begin > x_finish || x_finish > 1) {
        cout << "Введите конец диапазона < 1 : ";
        cin >> x_finish;
    }
    cout << "Введите шаг: ";
    cin >> x_step;
    while (x_step == 0) {
        cout << "Введите шаг != 0 : ";
        cin >> x_step;
    }
    cout << "Введите точность: ";
    cin >> e;
    while (e > 1 || e <= 0) {
        cout << "Введите точность (0;1) : ";
        cin >> e;
    }
    cout << "Сохранить данные в файл? Введите 1, если да: ";
    cin >> save;
    rezults(x_begin, x_finish, x_step, e, save);
}
//Функція зчитує з файлу значення х початку та кінця, крок, точність та вибір виводу результатів
void print_file(double& x_begin, double& x_finish, double& x_step, double& e, int save)
{
    setlocale(LC_ALL, "Russian");
    FILE* f = NULL;
    f = fopen("D:\\My projects\\атап-2\\Курсовая\\input.txt", "r");
    if (f != NULL) // якщо файл існує
    {
        fscanf(f, "%lf %lf %lf %lf", &x_begin, &x_finish, &x_step, &e);
        cout << "Начало диапазона: " << x_begin << endl;
        cout << "Конец диапазона: " << x_finish << endl;
        cout << "Шаг: " << x_step << endl;
        cout << "Точность: " << e << endl;
    }
    else // якщо файл відсутній
    {
        cout << "Введите значения с консоли" << endl;
        print_consol(x_begin, x_finish, x_step, e, save);
    }
    fclose(f);
    cout << "Сохранить данные в файл? Введите 1, если да: ";
    cin >> save;
    rezults(x_begin, x_finish, x_step, e, save);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    double x_begin = 0, x_finish = 0, x_step = 0, e = 0;
    int a;
    int save = 0;
    // початок діалогу з користувачем
    do {
        cout << "Использовать консоль или файл?" << endl;
        cout << "Ведите 1 (использовать консоль) или 2 (использовать файл): ";
        cin >> a;
        switch (a)
        {
        case 1:
            print_consol(x_begin, x_finish, x_step, e, save);
            break;
        case 2:
            print_file(x_begin, x_finish, x_step, e, save);
            break;
        default:
            cout << "Введите 1 или 2!" << endl;
            break;
        }
    } while (a != 1 && a != 2); // перевіряє правильність вводу значень
}
