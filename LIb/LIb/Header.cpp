#include "Header.h"
#include "iostream"
#include "vector"
#include "queue"

using namespace std;

void BFS::bfs(int** x, int& size, int index, bool* visited, queue <int> que, int** tree, bool* queue_visited) {
    for (int i = 0; i < size; i++) {
        visited[index] = true;
        if (x[index][i] == 1 & queue_visited[i] == false & visited[i] == false) {
                que.push(i);
                queue_visited[i] = true;
                tree[index][i] = 1;
        }
    }
    if (que.empty())
        return;
    int root = que.front();
    que.pop();
    bfs(x, size, root, visited, que, tree, queue_visited);
    return;
}

void BFS::Vertex_Insert(int** &x, int &size) {
    int** xNew = new int* [size + 1];
    
    for (int i = 0; i < size; i++)
    {
        xNew[i] = new int[size + 1];
        for (int j = 0; j < size; j++)
            xNew[i][j] = x[i][j];
    }
    xNew[size] = new int[size + 1];
 
    for (int j = 0; j < size + 1; j++) {
        xNew[size][j] = 0;
        xNew[j][size] = 0;
    }

    size = size++;
    delete[] x;
    x = xNew;
}
void BFS::Deleting_a_vertex(int**& x, int& size) {
    int** xNew = new int* [size-1];

    for (int i = 0; i < size-1; i++)
    {
        xNew[i] = new int[size-1];
        for (int j = 0; j < size-1; j++)
            xNew[i][j] = x[i][j];
    }
    size--;
    delete[] x;
    x = xNew;
}
void BFS::Insert_Arc(int** x, int start, int finish) {
    if (x[start-1][finish-1] != 1)
        x[start-1][finish-1] = 1;
    else{
        cout << "Связь уже есть. Проверьте вершины!\n";
    }
}
void BFS::Removing_an_arc(int** x, int start, int finish) {
    if (x[start-1][finish-1] != 0)
        x[start-1][finish-1] = 0;
    else {
        cout << "Связь не было изначально. Проверьте вершины!\n";
    }
}

int** BFS::Tree_bfs(int** x, int& size){
    bool* visited = new bool[size];
    bool* queue_visited = new bool[size];
    queue <int> que;
    int** tree = new int* [size];
    int index = 0;
    for (int i = 0; i < size; i++)
        tree[i] = new int[size];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            tree[i][j] = 0;
        visited[i] = false;
        queue_visited[i] = false;
    }
    bfs(x, size, index, visited, que, tree, queue_visited);
    return tree;
}