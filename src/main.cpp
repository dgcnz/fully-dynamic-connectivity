#include "forest.h"
#include "rb_tree.h"
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

    SF.getSpanningForest(&G);
    SF.buildEulerian();

    cout << G.dumpDot("exports/dot/graph.dot") << endl;
    cout << SF.dumpDot("exports/dot/spanning.dot") << endl;
    cout << SF.dumpETDot("exports/dot/euler.dot") << endl;
    return 0;
}
