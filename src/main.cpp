#include "gridgraph.h"
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
    int board_size = 9;
    Graph G;
    fill_board(G, board_size);

    cout << G.dumpDot("exports/dot/test.dot") << endl;
    return 0;
}
