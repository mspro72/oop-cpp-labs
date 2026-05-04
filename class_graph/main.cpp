#include <iostream>
#include <locale.h>
#include "graph.h"
#include "BFS.h"
#include "DFS.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
    // Создаём вершины
    Node* a = new Node("A");
    Node* b = new Node("B");
    Node* c = new Node("C");
    Node* d = new Node("D");
    Node* e = new Node("E"); // изолированная вершина

    // Добавляем в граф
    Graph g;
    g.addNode(a);
    g.addNode(b);
    g.addNode(c);
    g.addNode(d);
    g.addNode(e);

    // Рёбра: A-B-C-D (цепочка), E ни с кем не связана
    g.addEdge(a, b);
    g.addEdge(b, c);
    g.addEdge(c, d);

    BFS bfs(g);
    DFS dfs(g);

    cout << "=== BFS ===" << endl;
    cout << "A-D (есть путь, ожидаем 1): " << bfs.connected(a, d) << endl;
    cout << "A-E (нет пути, ожидаем 0): " << bfs.connected(a, e) << endl;
    cout << "A-A (сам с собой, ожидаем 1): " << bfs.connected(a, a) << endl;

    cout << "=== DFS ===" << endl;
    cout << "A-D (есть путь, ожидаем 1): " << dfs.connected(a, d) << endl;
    cout << "A-E (нет пути, ожидаем 0): " << dfs.connected(a, e) << endl;
    cout << "A-A (сам с собой, ожидаем 1): " << dfs.connected(a, a) << endl;

    // Удаляем вершину B — путь A-D должен пропасть
    g.removeNode(b);
    BFS bfs2(g);
    DFS dfs2(g);
    cout << "=== После удаления B ===" << endl;
    cout << "BFS A-D (ожидаем 0): " << bfs2.connected(a, d) << endl;
    cout << "DFS A-D (ожидаем 0): " << dfs2.connected(a, d) << endl;

    delete a; delete b; delete c; delete d; delete e;
    return 0;
}