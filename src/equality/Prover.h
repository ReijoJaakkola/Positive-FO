#include "TermNetwork.h"

namespace prover {
    class EqualityProver {
        private:
            TermNetwork m_network;
            std::vector<std::pair<int, int>> m_equalities = {};
            std::vector<std::pair<int, int>> m_inequalities = {};

        public:
            EqualityProver();
            void addFunction(char symbol, int arity);
            bool addEquality(const std::string& input1, const std::string& input2, bool equality);
            bool prove();

    };
}