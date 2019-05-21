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
    /*
    int size = 9;
    GGraph G(size * size);
    fill_board(G, size);
    Forest *SF = G.getSpanningForest();
    */

    RBTree RBT;

    RBT.insertValue(0, {});
    RBT.insertValue(1, {});
    RBT.insertValue(2, {});
    RBT.insertValue(3, {});
    RBT.insertValue(4, {});
    RBT.insertValue(5, {});
    RBT.insertValue(6, {});
    RBT.insertValue(7, {});
    RBT.insertValue(8, {});
    RBT.insertValue(9, {});
    RBT.insertValue(10, {});

    RBT.deleteValue(0);
    cout << RBT.dumpDot("exports/dot/test.dot") << endl;
    return 0;
}
