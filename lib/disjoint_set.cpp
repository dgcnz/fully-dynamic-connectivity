#include <cstdlib>
#include <cstring>
#include <iostream>

#include "disjoint_set.h"

using namespace std;

DisjointSet::DisjointSet(int size)
{
    /*
     * Initializes parents to itself and ranks to 0
     */

    this->parent = (int *)malloc(sizeof(int) * size);
    this->rank = (int *)calloc(sizeof(int), size);

    for (int i = 0; i < size; ++i)
        parent[i] = i;
}

void DisjointSet::unionSet(int v1_key, int v2_key)
{
    this->link(findSet(v1_key), findSet(v2_key));
}

void DisjointSet::link(int v1_key, int v2_key)
{
    if (rank[v1_key] > rank[v2_key])
        parent[v2_key] = v1_key;
    else
    {
        parent[v1_key] = v2_key;
        if (rank[v1_key] == rank[v2_key])
            ++(rank[v2_key]);
    }
}

int DisjointSet::findSet(int v_key) const
{
    if (v_key != parent[v_key])
        parent[v_key] = findSet(parent[v_key]);

    return parent[v_key];
}
DisjointSet::~DisjointSet()
{
    free(this->rank);
    free(this->parent);
};
