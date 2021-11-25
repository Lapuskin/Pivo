#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <deque>

using namespace std;


void src(int m, int** x, int* dist, bool* vis, int index, deque <int> stack)
{
    for (int i = 0; i < m; i++) {
        if (x[index][i] == 1)
            stack.push_back(i);

    }
    for (int j = 0; j < stack.size(); j++)
    {
        if (x[index][stack[j]] == 1) {
            if (dist[index] != INT_MIN && (dist[index] + x[index][stack[j]] > dist[stack[j]]))
            {
                dist[stack[j]] = dist[index] + x[index][stack[j]];
            }
        }
    }
    if (stack.empty())
        return;
    try
    {
        int nei = stack.front();
        stack.pop_front();
        src(m, x, dist, vis, nei, stack);
    }
    catch (out_of_range e)
    {
        return;
    }
    return;
}

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
        while (!file.eof())//до конца 
        {
            file >> temp;//в пустоту считываем из файла числа
            count++;
        }
        //перевод каретки в потоке в начало файла
        file.seekg(0, ios::beg);
        file.clear();

        int count_space = 0;
        char symbol;
        while (!file.eof())
        {
            file.get(symbol);
            if (symbol == ' ') count_space++;
            if (symbol == '\n') break;//Если дошли до конца, выходим
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

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                file >> x[i][j];

        for (i = 0; i < 8 * m; i++)
            cout << "-";
        cout << endl;
        //Вывод матрицы
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                cout << x[i][j] << "\t";
            cout << "\n";
        }
        //Декоративные палочки ------- 
        for (i = 0; i < 8 * m; i++)
            cout << "-";
        cout << endl;
        //АЛГОРИТМ
        int* dist = new int[m];
        bool* vis = new bool[m];
        deque<int> stack;
        int st, end;
        cout << "Введите номер начальной вершины: ";
        cin >> st;
        cout << "Введите номер конечной вершины: ";
        cin >> end;
        for (i = 0; i < m; i++)
        {
            vis[i] = false;
            dist[i] = INT_MIN;
        }
        dist[st] = 0;
        int index = st;
        int u;
        vis[st] = true;
        src(m, x, dist, vis, index, stack);
        for (i = 0; i < 8 * m; i++)
            cout << "-";
        cout << endl;
        cout << "Стоимость пути из " << st << " вершины в " << end << ":\t\n";
            if (dist[end] != INT_MIN && dist[end] != 0)
                cout << st << " -> " << end << " = " << dist[end] << endl;
            else
                cout << st << " -> " << end << " = " << "маршрут недоступен" << endl;
        int back_index = 1;
        int fin = end;
        int weight = dist[fin]; // вес конечной вершины
        int* ver = new int[m];
        ver[0] = fin;
        while (fin != st) // пока не дошли до начальной вершины
        {
            for (int i = 0; i < m; i++) // просматриваем все вершины
                if (x[i][fin] != 0)   // если связь есть
                {
                    int tmp = weight - x[i][fin]; // определяем вес пути из предыдущей вершины
                    if (tmp == dist[i]) // если вес совпал с рассчитанным
                    {                 // значит из этой вершины и был переход
                        weight = tmp; // сохраняем новый вес
                        fin = i;       // сохраняем предыдущую вершину
                        ver[back_index] = i; // и записываем ее в массив
                        back_index++;
                    }
                }
        }
        // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
        cout << "Максимальный путь"<<endl;
        for (int i = back_index - 1; i >= 0; i--)
            cout << ver[i]<< " ";
    }
    else
    {
        cout << "Ошибка! Невозможно открыть файл.";
    }
}