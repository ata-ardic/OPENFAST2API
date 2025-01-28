#include "OpenFAST.H"
#include <iostream> // For std::cout

using namespace fast;

int main() {
    std::cout << "Creating OpenFAST instance...\n";
    OpenFAST openfast;
    std::cout << "Initializing OpenFAST...\n";
    openfast.init();
    std::cout << "Initialization complete!\n";
    return 0;
}
