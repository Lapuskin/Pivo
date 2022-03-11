#pragma once
#include "Header.h"
#include "iostream"
#include "vector"
#include "queue"
using namespace std;

class BFS {
	void bfs(int** x, int& size, int index, bool* visited, queue <int> que, int** tree, bool* queue_visited);
public:
	void Vertex_Insert(int**& x, int& size);
	void Deleting_a_vertex(int**& x, int& size);
	void Insert_Arc(int** x, int start, int finish);
	void Removing_an_arc(int** x, int start, int finish);
	int** Tree_bfs(int** x, int& size);
};