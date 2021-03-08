#include <iostream>
#include "Prover.h"

int main(void)
{
    prover::EqualityProver prov = prover::EqualityProver();
    prov.addFunction(L'f', 1);
    prov.addEquality("x", "fffffx", true);
    prov.addEquality("x", "fffx", true);
    prov.addEquality("x", "fx", false);
    std::cout << prov.prove() << std::endl;
    return 0;
}