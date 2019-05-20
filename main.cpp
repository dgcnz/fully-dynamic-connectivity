#include "lib/gridgraph.h"
#include "lib/rb_tree.h"
#include "lib/utilities.h"
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

    RBT.rbtInsert(0, {});
    RBT.rbtInsert(1, {});
    RBT.rbtInsert(2, {});
    RBT.rbtInsert(3, {});
    RBT.rbtInsert(4, {});
    RBT.rbtInsert(5, {});
    RBT.rbtInsert(6, {});
    RBT.rbtInsert(7, {});
    RBT.rbtInsert(8, {});
    RBT.rbtInsert(9, {});
    RBT.rbtInsert(10, {});

    RBT.rbtDelete(0);
    cout << RBT.dumpDot("exports/test.dot") << endl;
    return 0;
}
