#include <assert.h>
#include <queue>
#include "TermNetwork.h"

namespace prover {
    TermNetwork::TermNetwork()
    {}

    int TermNetwork::isFunction(char symbol)
    {
        for (const auto& function : m_vocabulary)
        {
            if (function.first == symbol) {
                return function.second;
            }
        }
        return -1;
    }

    int TermNetwork::containsTerm(const std::string& term)
    {
        for (size_t i = 0; i < m_terms.size(); ++i) {
            if (m_terms[i] == term) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    void TermNetwork::addFunction(char symbol, int arity)
    {
        m_vocabulary.push_back({ symbol, arity });
    }

    int TermNetwork::addTerm(const std::string& input)
    {
        // TODO: Functions or variables of length greater than one.
        std::queue<std::string> previousTerms;
        std::queue<int> previousIndexes;
        for (int i = static_cast<int>(input.size()) - 1; i >= 0; --i)
        {
            char symbol = input.at(i);
            int arity = isFunction(symbol);
            if (arity < 0) {
                std::string term(1, symbol);
                int position = containsTerm(term);
                if (position < 0) {
                    m_terms.push_back(term);
                    m_edges.push_back(std::vector<int>());
                    position = static_cast<int>(m_terms.size()) - 1;
                }
                previousTerms.push(term);
                previousIndexes.push(position);
            }
            else {
                std::string newTerm(1, symbol);
                int counter = arity;
                while (counter > 0) {
                    if (previousTerms.empty()) {
                        assert(0);
                        return -1;
                    }
                    newTerm = newTerm + previousTerms.back();
                    previousTerms.pop();
                    --counter;
                }

                int position = containsTerm(newTerm);
                if (position < 0) {
                    m_terms.push_back(newTerm);
                    m_edges.push_back(std::vector<int>());
                    position = static_cast<int>(m_terms.size()) - 1;

                    counter = arity;
                    while (counter > 0) {
                        if (previousIndexes.empty()) {
                            assert(0);
                            return -1;
                        }
                        m_edges[position].push_back(previousIndexes.back());
                        previousIndexes.pop();
                        --counter;
                    }
                }
                else {
                    counter = arity;
                    while (counter > 0) {
                        previousIndexes.pop();
                        --counter;
                    }
                }
                previousTerms.push(newTerm);
                previousIndexes.push(position);
            }
        }

        return previousIndexes.back();
    }

    std::vector<int> TermNetwork::children(int key)
    {
        if (0 > key || key >= m_edges.size()) {
            assert(0);
            return {};
        }
        return m_edges[key];
    }

    bool TermNetwork::sameFunction(int key1, int key2)
    {
        if (0 > key1 || 0 > key2 || key1 >= m_terms.size() || key2 >= m_terms.size()) {
            assert(0);
            return false;
        }

        std::string term1 = m_terms[key1];
        if (isFunction(term1.at(0)) < 0) {
            return false;
        }

        std::string term2 = m_terms[key2];
        if (isFunction(term2.at(0)) < 0) {
            return false;
        }

        return term1.at(0) == term2.at(0);
    }

    int TermNetwork::size()
    {
        return static_cast<int>(m_terms.size());
    }
}