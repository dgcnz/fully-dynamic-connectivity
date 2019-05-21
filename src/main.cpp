#include "dynamic_graph.h"
#include "utilities.h"
#include <cmath>
#include <cstdarg>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
    using namespace std::placeholders; // for _1, _2, _3...
    int board_size = 3;
    Graph G;
    Forest SF;

    fill_board(G, board_size);
    G.removeEdge(0, 1);
    G.removeEdge(1, 0);

    G.removeEdge(0, 3);
    G.removeEdge(3, 0);
    DynamicGraph DF(&G);
    if (DF.isConnected(0, 1))
        cout << "CONECTADO\n";
    else
        cout << "NO CONECTADO\n";
    DF.dumpDot();

    return 0;
}
