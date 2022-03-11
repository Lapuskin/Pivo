#include "Header.h"
#include <iostream>
#include <iostream>
#include <fstream>

using namespace std;

void write(int** x, int size) {
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << x[i][j] << "\t";
        cout << "\n";
    }
}
int main()
{
    int i, chose = 0, temp;
    setlocale(LC_ALL, "rus");
    ifstream file;
    file.open("D:\\Projects\\gph\\oriented.txt");
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
        int n, start, fin;
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
        write(x, n);
        BFS graph;
        while (chose == 0) {
            cout << "Выберите операцию: \n" << "1. Добавить вершину\n" << "2. Добавить ребро\n" << "3. Убрать вершину\n" << "4. Убрать ребро\n" << "5. Построение дерева поиска в ширину\n";
            cin >> temp;
            temp--;
            switch (temp)
            {
            case 0:
            {
                graph.Vertex_Insert(x, n);
                write(x, n);
                break;
            }
            case 1:
            {
                cout << "Введите номер начальной вершины :";
                cin >> start;
                cout << "Введите номер конечной вершины :";
                cin >> fin;
                    graph.Insert_Arc(x, start, fin);
                write(x, n);
                break;
            }   
            case 2:
            {
                graph.Deleting_a_vertex(x, n);
                write(x, n);
                break;
            }
            case 3:
            {
                cout << "Введите номер начальной вершины: ";
                cin >> start;
                cout << "Введите номер конечной вершины: ";
                cin >> fin;
                graph.Removing_an_arc(x, start, fin);
                write(x, n);
                break;
            }
            case 4: {
                write(graph.Tree_bfs(x, n), n);
                break;
            }
            default:
                break;
            }   
            cout << "Желаете продолжить?(1 - да/ 0 - нет)";
            cin >> temp;
            if (temp == 0)
                chose++;
        }
    }
}