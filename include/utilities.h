#ifndef __UTILITIES_H__
#define __UTILITIES_H__
#include "graph.h"
#include <functional>
#include <iostream>
#include <utility>

using namespace std;
using Point = pair<int, int>;
// test(bind(static_cast<void (Graph::*)(int)>(&Graph::addNode), &G, 0));

void test(std::function<void()> f)
{
    cout << "Starting execution of " << __func__ << endl;

    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();

    cout << "Ended execution of " << __func__ << endl;

    std::chrono::duration<double> time_span
        = std::chrono::duration_cast<std::chrono::duration<double>>(
            end - start);

    std::cout << "TIME: " << time_span.count() << "s\n";
}

int flatten(int x, int y, int size)
{
    return size * y + x;
}

Point deflatten(int z, int size)
{
    int x = z % size;
    int y = z / size;

    return make_pair(x, y);
}

void fill_board(Graph &G, int size)
{
    using namespace std::placeholders;

    auto fflatten = std::bind(flatten, _1, _2, size);
    auto defflatten = std::bind(deflatten, _1, size);

    for (int i = 0, total = size * size; i < total; ++i)
        G.addNode(i, { { "pos", defflatten(i) } });

    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            Node *u = G[fflatten(x, y)];
            if (y > 0)
                u->addEdge(G[fflatten(x, y - 1)]);
            if (y < size - 1)
                u->addEdge(G[fflatten(x, y + 1)]);
            if (x > 0)
                u->addEdge(G[fflatten(x - 1, y)]);
            if (x < size - 1)
                u->addEdge(G[fflatten(x + 1, y)]);
        }
    }
}

#endif
