﻿#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<vector<int>> generateAdjacencyMatrix(int size) {
    vector<vector<int>> matrix(size, vector<int>(size, 0));
    srand(time(0));

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            int edge = rand() % 2;
            matrix[i][j] = edge;
            matrix[j][i] = edge;
        }
    }

    return matrix;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

vector<int> bfsDistances(const vector<vector<int>>& graph, int start) {
    int size = graph.size();
    vector<int> distances(size, -1);
    queue<int> q;

    q.push(start);
    distances[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < size; ++i) {
            if (graph[current][i] == 1 && distances[i] == -1) {
                distances[i] = distances[current] + 1;
                q.push(i);
            }
        }
    }

    return distances;
}

int countDominatingVertices(const vector<vector<int>>& graph) {
    int size = graph.size();
    int count = 0;

    for (int i = 0; i < size; ++i) {
        bool isDominating = true;
        for (int j = 0; j < size; ++j) {
            if (i != j && graph[i][j] == 0) {
                isDominating = false;
                break;
            }
        }
        if (isDominating) {
            ++count;
        }
    }

    return count;
}

vector<int> findIsolatedVertices(const vector<int>& distances) {
    vector<int> isolatedVertices;
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] == -1) {
            isolatedVertices.push_back(i);
        }
    }
    return isolatedVertices;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int graphSize;

    cout << "Введите количество вершин графа:\n";
    cin >> graphSize;

    vector<vector<int>> adjacencyMatrix = generateAdjacencyMatrix(graphSize);

    cout << "Матрица смежности:" << endl;
    printMatrix(adjacencyMatrix);

    int startVertex = 0;

    while (true)
    {
        cout << "Введите стартовую вершину:\n";
        cin >> startVertex;
        if (startVertex >= 0 && startVertex < graphSize)
        {
            break;
        }
        else
        {
            cout << "Значение не валидно\n";
        }
    }

    vector<int> distances = bfsDistances(adjacencyMatrix, startVertex);
    cout << "\nРасстояния от вершины " << startVertex << ":" << endl;
    for (int i = 0; i < distances.size(); ++i) {
        cout << "Вершина " << i << ": " << distances[i] << endl;
    }

    int dominatingVerticesCount = countDominatingVertices(adjacencyMatrix);
    cout << "\nКоличество доминирующих вершин: " << dominatingVerticesCount << endl;

    vector<int> isolatedVertices = findIsolatedVertices(distances);
    cout << "\nИзолированные вершины:" << endl;
    for (int vertex : isolatedVertices) {
        cout << "Вершина " << vertex << endl;
    }

    return 0;
}
