#include <assert.h>
#include "DisjointSet.h"

namespace dsf {
    DisjointSetForest::DisjointSetForest(int size) 
    {
        for (int i = 0; i < size; ++i)
        {
            Node node;
            node.m_location = i;
            node.m_parent = i;
            m_nodes.push_back(node);
        }
    }

    bool DisjointSetForest::validLocation(int location)
    {
        return 0 <= location && location < static_cast<int>(m_nodes.size());
    }

    int DisjointSetForest::findRoot(int location)
    {
        if (!validLocation(location))
        {
            return -1;
        }

        Node* node = &m_nodes[location];
        while (node->m_parent != node->m_location)
        {
            node->m_parent = m_nodes[node->m_parent].m_parent;
            node = &m_nodes[node->m_parent];
        }
        return node->m_location;
    }

    bool DisjointSetForest::sameComponent(int location1, int location2)
    {
        int root1 = findRoot(location1);
        int root2 = findRoot(location2);

        if (root1 < 0 || root2 < 0) {
            assert(0);
            return false;
        }

        if (root1 == root2) {
            return true;
        }
        else {
            return false;
        }
    }

    bool DisjointSetForest::nodeUnion(int location1, int location2)
    {
        int root1 = findRoot(location1);
        int root2 = findRoot(location2);

        if (root1 < 0 || root2 < 0) {
            assert(0);
            return false;
        }

        if (root1 == root2) {
            return false;
        }

        Node* node1 = &m_nodes[root1];
        Node* node2 = &m_nodes[root2];
        
        if (node1->m_size > node2->m_size) {
            node2->m_parent = node1->m_location;
            node1->m_size = node1->m_size + node2->m_size;
        }
        else {
            node1->m_parent = node2->m_location;
            node2->m_size = node1->m_size + node2->m_size;
        }

        return true;
    }
}