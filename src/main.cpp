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

    int size = 9;
    GGraph G(size * size);
    fill_board(G, size);
    // Forest *SF = G.getSpanningForest();

    // cout << RBT.dumpDot("images/test.dot") << endl;
    return 0;
}
