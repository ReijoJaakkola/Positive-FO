#include <vector>
#include <string>

namespace dsf {
    struct Node {
        int m_location = 0;
        int m_size = 1;
        int m_parent = 0;

        bool operator==(const Node& other) const
        {
            return m_location == other.m_location;
        }
    };

    class DisjointSetForest {
        private:
            std::vector<Node> m_nodes = {};
            bool validLocation(int location);

        public:
            DisjointSetForest(int size);
            int findRoot(int location); // Returns -1 if invalid location.
            bool sameComponent(int location1, int location2); // Asserts if invalid location.
            bool nodeUnion(int location1, int location2); // Asserts if invalid location. Returns true if
                                                          // the nodes were not in the same component.
    };
}