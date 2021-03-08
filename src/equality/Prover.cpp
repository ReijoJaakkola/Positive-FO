#include <assert.h>
#include "DisjointSet.h"
#include "Prover.h"

namespace prover {
    EqualityProver::EqualityProver()
    {}

    void EqualityProver::addFunction(char symbol, int arity)
    {
        m_network.addFunction(symbol, arity);
    }

    bool EqualityProver::addEquality(const std::string& input1, const std::string& input2, bool equality)
    {
        int key1 = m_network.addTerm(input1);
        if (key1 < 0) {
            return false;
        }

        int key2 = m_network.addTerm(input2);
        if (key2 < 0) {
            return false;
        }

        if (equality) {
            m_equalities.push_back({ key1, key2 });
        }
        else {
            m_inequalities.push_back({ key1, key2 });
        }

        return true;
    }

    bool EqualityProver::prove()
    {
        dsf::DisjointSetForest forest(static_cast<int>(m_network.size()));
        
        for (const auto& equality : m_equalities)
        {
            forest.nodeUnion(equality.first, equality.second);
        }

        while (true)
        {
            bool changed = false;
            std::vector <std::pair<int, int >> candidates = {};
            for (int i = 0; i < m_network.size(); ++i) {
                for (int j = 0; j < m_network.size(); ++j) {
                    // Consider only those terms that we have not
                    // yet determined to be equal.
                    if (forest.sameComponent(i, j)) {
                        continue;
                    }

                    if (!m_network.sameFunction(i, j)) {
                        continue;
                    }

                    std::vector<int> children1 = m_network.children(i);
                    std::vector<int> children2 = m_network.children(j);
                    if (children1.size() != children2.size()) {
                        assert(0);
                        return false;
                    }

                    bool same = true;
                    for (size_t k = 0; k < children1.size(); ++k) {
                        if (!forest.sameComponent(children1[k], children2[k])) {
                            same = false;
                            break;
                        }
                    }

                    if (same) {
                        forest.nodeUnion(i, j);
                        changed = true;
                    }
                }
            }

            if (!changed)
            {
                break;
            }
        }

        for (const auto& equality : m_inequalities)
        {
            if (forest.sameComponent(equality.first, equality.second))
            {
                return false;
            }
        }
        
        return true;
    }
}