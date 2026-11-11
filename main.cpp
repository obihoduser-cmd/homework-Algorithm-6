#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// ЧАСТЬ 1. РЕКУРСИВНЫЕ АЛГОРИТМЫ

// 1. Рекурсивный факториал
unsigned long long factorial(int n) {
    if (n < 0) {
        throw invalid_argument("Число не может быть отрицательным");
    }

    if (n == 0 || n == 1) {
        return 1;
    }

    return n * factorial(n - 1);
}

// 2. Рекурсивные числа Фибоначчи
long long fibonacci(int n) {
    if (n < 0) {
        throw invalid_argument("Индекс не может быть отрицательным");
    }

    if (n == 0) return 0;
    if (n == 1) return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 3. Рекурсивный обход лабиринта 6x6

const int SIZE = 6;

int maze[SIZE][SIZE] = {
    {0, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 1, 0},
    {0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0},
    {1, 1, 0, 0, 0, 0}
};

bool visited[SIZE][SIZE] = {};
bool path[SIZE][SIZE] = {};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool findPath(int x, int y) {
    // Проверка границ лабиринта
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        return false;
    }

    // Стена или уже посещённая клетка
    if (maze[x][y] == 1 || visited[x][y]) {
        return false;
    }

    visited[x][y] = true;
    path[x][y] = true;

    // Достигли выхода
    if (x == SIZE - 1 && y == SIZE - 1) {
        return true;
    }

    // Пробуем четыре направления
    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (findPath(newX, newY)) {
            return true;
        }
    }

    // Если путь не найден, возвращаемся назад
    path[x][y] = false;

    return false;
}

void printMaze() {
    cout << "Лабиринт:\n";

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (maze[i][j] == 1) {
                cout << "# ";
            }
            else if (path[i][j]) {
                cout << "* ";
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }

    cout << "* - найденный путь\n";
    cout << "# - стена\n";
    cout << ". - свободная клетка\n";
}

// 4. Задача о 5 ферзях

const int N = 5;

int queenPosition[N];
int firstSolution[N];
int solutionsCount = 0;

bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        // Проверка столбца и диагоналей
        if (queenPosition[i] == col ||
            abs(queenPosition[i] - col) == abs(i - row)) {
            return false;
        }
    }

    return true;
}

void solveQueens(int row) {
    // Все ферзи успешно размещены
    if (row == N) {
        solutionsCount++;

        // Сохраняем первое решение
        if (solutionsCount == 1) {
            for (int i = 0; i < N; i++) {
                firstSolution[i] = queenPosition[i];
            }
        }

        return;
    }

    // Пробуем каждый столбец текущей строки
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            queenPosition[row] = col;

            solveQueens(row + 1);
        }
    }
}

void printQueens() {
    cout << "Первое найденное решение:\n";

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (firstSolution[row] == col) {
                cout << "Q ";
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }

    cout << "Всего решений: " << solutionsCount << endl;
}

// ЧАСТЬ 2. ПРОСТЫЕ СОРТИРОВКИ

// Вывод массива
void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

// 1. Пузырьковая сортировка
void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // Если обменов не было, массив уже отсортирован
        if (!swapped) {
            break;
        }
    }
}

// 2. Сортировка вставками
void insertionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// 3. Сортировка выбором
void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// 4. Рекурсивная пузырьковая сортировка
void recursiveBubbleSort(vector<int>& arr, int n) {
    // Базовый случай рекурсии
    if (n <= 1) {
        return;
    }

    // Один проход пузырьковой сортировки
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            swap(arr[i], arr[i + 1]);
        }
    }

    // Сортируем оставшуюся часть
    recursiveBubbleSort(arr, n - 1);
}

// MAIN

int main() {
    setlocale(LC_ALL, "Russian");

    // ЧАСТЬ 1
    cout << "========== ЧАСТЬ 1. РЕКУРСИЯ ==========\n\n";

    // Факториал
    int number = 5;

    cout << "1. Факториал числа " << number << " = "
         << factorial(number) << "\n\n";

    // Фибоначчи
    int fibNumber = 10;

    cout << "2. Число Фибоначчи с индексом "
         << fibNumber << " = "
         << fibonacci(fibNumber) << "\n\n";

    // Лабиринт
    cout << "3. Обход лабиринта 6x6:\n";

    if (findPath(0, 0)) {
        cout << "Путь найден!\n";
    }
    else {
        cout << "Путь не найден!\n";
    }

    printMaze();
    cout << endl;

    // Задача о ферзях
    cout << "4. Задача о 5 ферзях:\n";

    solveQueens(0);
    printQueens();

    // ЧАСТЬ 2
    cout << "\n========== ЧАСТЬ 2. СОРТИРОВКИ ==========\n\n";

    vector<int> original = {8, 3, 7, 1, 9, 2, 5, 4, 6};

    vector<int> a = original;
    vector<int> b = original;
    vector<int> c = original;
    vector<int> d = original;

    cout << "Исходный массив: ";
    printArray(original);

    // Пузырьковая сортировка
    bubbleSort(a);
    cout << "\n1. Пузырьковая сортировка: ";
    printArray(a);

    // Сортировка вставками
    insertionSort(b);
    cout << "2. Сортировка вставками: ";
    printArray(b);

    // Сортировка выбором
    selectionSort(c);
    cout << "3. Сортировка выбором: ";
    printArray(c);

    // Рекурсивная пузырьковая сортировка
    recursiveBubbleSort(d, d.size());
    cout << "4. Рекурсивная пузырьковая сортировка: ";
    printArray(d);

    return 0;
}
