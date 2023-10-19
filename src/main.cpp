#include "Utils/Parameters.hpp"
#include "Algo.hpp"

int main(int argc, char *argv[]) {
    std::cout << "Memetic Algo for CETSP" << std::endl << std::endl;

    auto params = new Parameters(argc, argv);
    params->print();

    Algo algo(params);
    algo.run();

    return 0;
}