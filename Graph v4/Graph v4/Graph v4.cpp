#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <vector>
#include <deque>

using namespace std;

int main()
{
    int i;
    string name;
    setlocale(LC_ALL, "ru");
    std::cout << "Возможные варинаты графов: " << endl;
    std::cout << "1 - oriented" << endl;
    std::cout << "2 - oriented1" << endl;
    std::cout << "3 - oriented2" << endl;
    std::cout << "4 - oriented3" << endl;
    std::cout << "Введите номер графа для поиска максимального пути: " << endl;
    cin >> i;
    switch (i - 1)
    {
    case 0:
    {
        name = "D:\\Projects\\gph\\oriented.txt"; break;
    }
    case 1:
    {
        name = "D:\\Projects\\gph\\oriented1.txt"; break;
    }
    case 2:
    {
        name = "D:\\Projects\\gph\\oriented2.txt"; break;
    }
    case 3:
    {
        name = "D:\\Projects\\gph\\oriented3.txt"; break;
    }
    default:
    {
        std::cout << "Ошибка! Введен неверный номер графа.";
    }
    }
    ifstream file;
    file.open(name);
    if (file.is_open()) {
        cout << "Файл открыт успешно!" << endl;

        int count = 0;
        int temp;
        while (!file.eof())// пробегаем пока не встретим конец файла 
        {
            file >> temp;//в пустоту считываем из файла числа
            count++;// увеличиваем счетчик числа чисел
        }
        //Вначале переведем каретку в потоке в начало файла
        file.seekg(0, ios::beg);
        file.clear();

        int count_space = 0;
        char symbol;
        while (!file.eof())//на всякий случай цикл ограничиваем концом файла
        {
            //теперь нам нужно считывать не числа, а посимвольно считывать данные
            file.get(symbol);//считали текущий символ
            if (symbol == ' ') count_space++;//Если это пробел, то число пробелов увеличиваем
            if (symbol == '\n') break;//Если дошли до конца строки, то выходим из цикла
        }
        cout << "Матрица смежности для данного графа: " << endl;
        // Опять переходим в потоке в начало файла
        file.seekg(0, ios::beg);
        file.clear();
        int n;
        int m = n = count_space + 1;
        int** x;
        x = new int* [n];
        for (int i = 0; i < n; i++) x[i] = new int[m];

        //Считаем матрицу из файла
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                file >> x[i][j];
        //Выведем матрицу
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                cout << x[i][j] << "\t";
            cout << "\n";
        }
        //АЛГОРИТМ
        int* dist = new int[m];
        bool* vis = new bool[m];
        int* path = new int[m];
        deque<int> stack;
        int st, end;
        cin >> st;
        for (i = 0; i < m; i++)
        {
            vis[i] = false;
            dist[i] = INT_MIN;
        }
        dist[st] = 0;
        int index = st;
        int u;
        vis[st] = true;
        for (int z = 0; z < m; z++) {
            for (i = 0; i < m; i++) {
                if (x[index][i] == 1)
                    stack.push_back(i);

            }
            while (!stack.empty()) {
                for (int j = 0; j < stack.size(); j++)
                {
                    if (x[index][stack[j]] == 1) {
                        if (dist[index] != INT_MIN && (dist[index] + x[index][stack[j]] > dist[stack[j]]))
                        {
                            dist[stack[j]] = dist[index] + x[index][stack[j]];
                        }
                    }
                }
                index = stack.front();
                for (int j = 0; j < stack.size(); j++) {
                    stack.pop_back();
                }
            }
            vis[index] = true;
            for (int z = 0; z < m; z++) {
                cout << vis[z] << " ";
            }
            cout << endl;
        }

        cout << "Стоимость пути из начальной вершины до остальных(Алгоритм Дейкстры):\t\n";
        for (int i = 0; i < n; i++)
        {
            if (dist[i] != INT_MIN && dist[i]!=0)
                cout << st << " -> " << i << " = " << dist[i] << endl;
            else
                cout << st << " -> " << i << " = " << "маршрут недоступен" << endl;
        }
    }
    else
    {
        cout << "Ошибка! Невозможно открыть файл.";
    }
}