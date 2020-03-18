#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

//Функция транспонирования матрицы
template <typename T> void TransponMtx(T** matr, T** tMatr, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tMatr[j][i] = matr[i][j];
}

//Функция освобождения памяти
template <typename T> void FreeMem(T** matr, int n)
{
    for (int i = 0; i < n; i++)
        delete[] matr[i];
    delete[] matr;
}

//Функция заполнения матрицы
template <typename T> void SetMtx(T** matr, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int f; cin >> f;
            matr[i][j] = f;
        }
}

//Функция печати матрицы
template <typename T> void PrintMtx(T** matr, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)            
            cout << setw(20) << setprecision(4) << matr[i][j] << " ";
        cout << endl;
    }
}

//Функция вычеркивания строки и столбца
void Get_matr(int** matr, int n, int** temp_matr, int indRow, int indCol)
{
    int ki = 0;
    for (int i = 0; i < n; i++) {
        if (i != indRow) {
            for (int j = 0, kj = 0; j < n; j++) {
                if (j != indCol) {
                    temp_matr[ki][kj] = matr[i][j];
                    kj++;
                }
            }
            ki++;
        }
    }
}

//Функция вычисления определителя матрицы
int Det(int** matr, int n)
{
    int temp = 0;   //Временная переменная для хранения определителя
    int k = 1;      //Степень
    if (n < 1) {
        cout << "Ошибка ввода: некорректный размер матрицы" << endl;
        return 0;
    }
    else if (n == 1)
        temp = matr[0][0];
    else if (n == 2)
        temp = matr[0][0] * matr[1][1] - matr[1][0] * matr[0][1];
    else {
        for (int i = 0; i < n; i++) {
            int m = n - 1;
            int** temp_matr = new int* [m];
            for (int j = 0; j < m; j++)
                temp_matr[j] = new int[m];
            Get_matr(matr, n, temp_matr, 0, i);
            temp = temp + k * matr[0][i] * Det(temp_matr, m);
            k = -k;
            FreeMem(temp_matr, m);
        }
    }
    return temp;
}

//Умножение обратной матрицы на вектор u и нахождение x*
template <typename T> void FindMtx(T** tobr_matr, int n) {

    vector<float> res; for (int i = 0; i < n; i++) {
        res.push_back(0);
    }

    vector<float> u; for (int i = 0; i < n; i++) {
        u.push_back(1);
    }

    for (int i = 0; i < n; i++)
    {
        float temp = 0;
        for (int j = 0; j < n; j++)
        {
            temp += tobr_matr[i][j] * u[i];
        }
        res[i] = temp;
    }

    cout << "uC^-1 = ("; 
    for (int i = 0; i < n; i++) { cout << res[i]; if (i != n - 1) cout << ", "; }
    cout << ") " << endl; 

    float temp = 0; for (int i = 0; i < n; i++) temp += res[i];
    cout << "uC^-1uT = " << temp << endl;

    cout << "x* = ("; 
    for (int i = 0; i < n; i++) { cout << res[i] / temp; if (i != n - 1) cout << ", "; }
    cout << ") " << endl;
}

//Умножение обратной матрицы на вектор u, нахождение y* и цены игры
template <typename T> void FindMty(T** tobr_matr, int n) {

    vector<float> res; for (int i = 0; i < n; i++) {
        res.push_back(0);
    }

    vector<float> u; for (int i = 0; i < n; i++) {
        u.push_back(1); 
    }

    for (int i = 0; i < n; i++)
    {
        float temp = 0;
        for (int j = 0; j < n; j++)
        {
            temp += tobr_matr[j][i] * u[i];
        }
        res[i] = temp;
    }

    cout << "C^-1uT = (";
    for (int i = 0; i < n; i++) { cout << res[i]; if (i != n - 1) cout << ", "; }
    cout << ") " << endl;

    float temp = 0; for (int i = 0; i < n; i++) temp += res[i];

    cout << "y* = (";
    for (int i = 0; i < n; i++) { cout << res[i] / temp; if (i != n - 1) cout << ", "; }
    cout << ") " << endl;

    cout << "v = "; cout << 1 / temp;

}

//Функция нахождения максимального выигрыша игрока А и выбора последующей из этого стратегии
int FindMax(vector<int> x, int A) { 
    int c = 0; int z; z = x[0];
    for (int i = 0; i < x.size(); i++) { //Проверка - если все значения одинаковые, то остаемся на той же стратегии
        if (x[i] == z) c++;
    }
    if (c == x.size()) return A;

    c = INT_MIN; int n;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] > c) {
            c = x[i]; n = i;
        }
    }

    return n;
}

//Функция нахождения минимального проигрыша игрока Б и выбора последующей из этого стратегии
int FindMin(vector<int> x, int A) {
    int c = 0; int z; z = x[0];
    for (int i = 0; i < x.size(); i++) { //Проверка - если все значения одинаковые, то остаемся на той же стратегии
        if (x[i] == z) c++;
    }
    if (c == x.size()) return A;

    c = INT_MAX; int n;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] < c) {
            c = x[i]; n = i;
        }
    }

    return n;
}

//Нахождение максимума из V_
double FindMx(vector<double> x) {
    double c = -100000;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] > c) {
            c = x[i];
        }
    }
    return c;
}

//Нахождение минимума из v-
double FindMn(vector<double> x) {
    double c = 100000;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] < c) {
            c = x[i];
        }
    }
    return c;
}

void main()
{
    setlocale(0, "");
    int n, det; //Размер матрицы и определитель
    cout << "Размер матрицы n x n: ";
    cin >> n;

    int** matr = new int* [n]; //Матрица значений по условию
    double** obr_matr = new double* [n]; //Обратная матрица
    double** tobr_matr = new double* [n]; //Транспонированная обратная
    for (int i = 0; i < n; i++) {
        matr[i] = new int[n];
        obr_matr[i] = new double[n];
        tobr_matr[i] = new double[n];
    }
    SetMtx(matr, n);
    cout << "Условие: " << endl;
    PrintMtx(matr, n);
    det = Det(matr, n);
    cout << "Определитель матрицы = " << det << endl;
    if (det) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int m = n - 1;
                int** temp_matr = new int* [m];
                for (int k = 0; k < m; k++)
                    temp_matr[k] = new int[m];
                Get_matr(matr, n, temp_matr, i, j);
                obr_matr[i][j] = pow(-1.0, i + j + 2) * Det(temp_matr, m) / det;
                FreeMem(temp_matr, m);
            }
        }
    }
    else cout << "Определитель матрицы равен 0 => матрица является вырожденной и обратной нет" << endl;

    //Транспонирование матрицы
    TransponMtx(obr_matr, tobr_matr, n);
    //Печать обратной матрицы после транспонирования
    cout << "Обратная матрица: " << endl;
    PrintMtx(tobr_matr, n);

    //Решение аналитическим способом
    cout << "Решение аналитическим методом: " << endl;
    FindMtx(tobr_matr, n);
    FindMty(tobr_matr, n);

    //Метод Брауна-Робинсон
    cout << endl << "Решение методом БР: " << endl;

    int k, A, B; A = 0; B = 0;
    vector<int> x; for (int i = 0; i < n; i++) x.push_back(matr[i][A]);
    vector<int> y; for (int i = 0; i < n; i++) y.push_back(matr[B][i]);
    int x1, x2, x3, y1, y2, y3;

    //В качестве счетчика итераций / знаменатель для столбцов пороговых значений
    k = 2;

    vector<int> cx; vector<int> cy; //Вектора-счетчики - сколько раз применили ту или иную стратегию
    for (int i = 0; i < n; i++) {
        cx.push_back(0);
        cy.push_back(0);
    }

    cx[0]++; cy[0]++; 

    vector<double> delX; vector<double> delY;

    //Первая строка таблицы - наименование столбцов (для красивого оформления)
    cout << setw(4) << "k" << " | " << "A" << " " << "B" << " | ";

    for (int i = 0; i < n; i++)
        cout << setw(5) << "x" << i + 1;

    cout << " | ";

    for (int i = 0; i < n; i++)
        cout << setw(5) << "y" << i + 1;

    cout << " | ";
    cout << setw(7) << "(1/k)v-" << " " << setw(7) << "(1/k)V_"; cout << " | "; //Пороговые значение
    cout << setw(7) << "(1/k)v-" << " " << setw(7) << "(1/k)V_"; cout << " | "; //Посчитанные пороговые значения
    cout << setw(7) << "e"; cout << " | "; //Точность
    cout << setw(6) << "v"; //Цена игры
    cout << endl << "--------------------------------------------------------------------------------------------------------" << endl;

    //Остальные строки
    for (int i = 0; i < k; i++) { // i - строка
        cout << setw(4) << i + 1 << " | " << A + 1 << " " << B + 1 << " | ";
        for (int j = 0; j < n; j++) cout << setw(5) << x[j] << " ";
        cout << " | ";
        for (int j = 0; j < n; j++) cout << setw(5) << y[j] << " ";

        A = FindMax(x, A);
        B = FindMin(y, B);
        cx[A]++; cy[B]++;

        if (i != 0) {
            cout << " | " << setw(4) << x[A] << "/" << setw(2) << i + 1 << " " << setw(4) << y[B] << "/" << setw(2) << i + 1 << " | ";
            double X; double Y; X = (double)x[A] / (i + 1); Y = (double)y[B] / (i + 1);

            cout << setw(7) << X << " " << setw(7) << Y;

            delX.push_back(X); delY.push_back(Y);
        }
        if (i == 0) {
            cout << " | " << setw(4) << x[A] << "   " << setw(6) << y[B] << "   | ";
            double X; double Y; X = x[A] / 1.; Y = y[B] / 1.;

            cout << setw(7) << X << " " << setw(7) << Y;

            delX.push_back(X); delY.push_back(Y);
        }

        for (int j = 0; j < n; j++) x[j] = x[j] + matr[j][B];
        for (int j = 0; j < n; j++) y[j] = y[j] + matr[A][j];

        double a, b, c;
        a = FindMn(delX);
        b = FindMx(delY);
        c = a - b;

        if (i != 0) cout << " | " << setw(7) << setprecision(4) << c << " | " << setw(6) << setprecision(4) << (a + b) / 2.0 << endl;
        if (i == 0) cout << " | " << setw(7) << setprecision(4) << c << " | " << setw(6) << setprecision(4) << (a + b) / 2.0 << endl;

        //Результаты БР метода
        if (c <= 0.10) {
            cout << "min (1/k)v- = " << a << endl;
            cout << "max (1/k)V_ = " << b << endl;
            cout << "Погрешность = " << c << endl;
            cout << "Среднее арифметическое (цена игры) = " << (a + b) / 2.0 << endl;
            i = k; k--; cx[A]--; cy[B]--;
        }

        if (c > 0.10) k++;

    }

    //Результаты БР метода
    cout << "Приближенные смешанные стратегии: " << endl;
    cout << "x[k]~ = (";
    for (int j = 0; j < n; j++) {
        cout << cx[j] << "/" << k;
        if (j != n - 1) cout << ", ";
    }
    cout << ")" << endl;

    cout << "y[k]~ = (";
    for (int j = 0; j < n; j++) {
        cout << cy[j] << "/" << k;
        if (j != n - 1) cout << ", ";
    }
    cout << ")" << endl;

    //Освобождение памяти
    FreeMem(tobr_matr, n);
    FreeMem(matr, n);
    FreeMem(obr_matr, n);
}
