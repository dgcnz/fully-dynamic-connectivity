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
    DisjointSet(int size)
    {
        /*
         * Initializes parents to itself and ranks to 0
         */

        this->parent = (int *)malloc(sizeof(int) * size);
        this->rank = (int *)calloc(sizeof(int), size);

        for (int i = 0; i < size; ++i)
            parent[i] = i;
    }

    void unionSet(int v1_key, int v2_key)
    {
        this->link(findSet(v1_key), findSet(v2_key));
    }

    void link(int v1_key, int v2_key)
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

    int findSet(int v_key) const
    {
        if (v_key != parent[v_key])
            parent[v_key] = findSet(parent[v_key]);

        return parent[v_key];
    }
    ~DisjointSet()
    {
        free(this->rank);
        free(this->parent);
    };
};
#endif
