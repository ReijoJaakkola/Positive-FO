#include <string>
#include <vector>

namespace prover {
    class TermNetwork {
    private:
        std::vector<std::pair<char, int>> m_vocabulary;
        std::vector<std::string> m_terms;
        std::vector<std::vector<int>> m_edges;

        int isFunction(char symbol);
        int containsTerm(const std::string& term);

    public:
        TermNetwork();
        void addFunction(char symbol, int arity);
        int addTerm(const std::string& input);
        std::vector<int> children(int key);
        bool sameFunction(int key1, int key2);
        int size();

    };
}