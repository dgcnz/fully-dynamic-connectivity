#ifndef __DISJOINT_SET_H__
#define __DISJOINT_SET_H__

#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

class DisjointSet
{
    int *parent;
    int *rank;

public:
    DisjointSet(int size);

    void unionSet(int v1_key, int v2_key);
    void link(int v1_key, int v2_key);
    int findSet(int v_key) const;

    ~DisjointSet();
};

#endif
