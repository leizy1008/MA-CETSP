/**
 * Parameters.cpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#include "Utils/cmdline.h"
#include "Utils/Parameters.hpp"

Parameters::Parameters(int argc, char **argv) {
    cmdline::parser parser;
    parser.add<int>("random", 'g', "random number for LKH", false, 0);
    parser.add<int>("instance", 'i', "instance index", false, INSTANCE_INDEX);
    parser.add<int>("seed", 's', "seed for random generator", false, SEED);
    parser.add<std::string>("init", '\0', "initialization", false, INITIALIZATION);
    parser.add<std::string>("select", '\0', "selection", false, SELECTION);
    parser.add<std::string>("crossover", '\0', "crossover", false, CROSSOVER);
    parser.add<std::string>("improvement", '\0', "improvement", false, IMPROVEMENT);
    parser.add<std::string>("greed", '\0', "greed", false, GREEDY_ALGO);
    parser.add<std::string>("distance", '\0', "distance", false, DISTANCE);
    // parameters
    parser.add<int>("pop_size", 'p', "population size", false, POPULATION_SIZE);
    parser.add<int>("iteration", 'r', "iteration", false, ITERATION);
    parser.add<double>("max_time", 't', "max running time", false, MAX_TIME);
    parser.add<double>("fit_beta", 'b', "coefficient for fitness function", false, FIT_BETA);
    parser.add<int>("dist_th", 'd', "distance threshold", false, DISTANCE_THRESHOLD);
    parser.add<int>("neighbor_size", 'n', "neighbor size", false, NEIGHBOR_SIZE);

    parser.parse_check(argc, argv);

    random_num = parser.get<int>("random");
    instance_index = parser.get<int>("instance");
    seed = parser.get<int>("seed");
    init = parser.get<std::string>("init");
    select = parser.get<std::string>("select");
    crossover = parser.get<std::string>("crossover");
    improvement = parser.get<std::string>("improvement");
    greed = parser.get<std::string>("greed");
    distance = parser.get<std::string>("distance");
    population_size = parser.get<int>("pop_size");
    iteration = parser.get<int>("iteration");
    patience = iteration / 10;
    max_time = parser.get<double>("max_time");
    fit_beta = parser.get<double>("fit_beta");
    dist_th = parser.get<int>("dist_th");
    neighbor_size = parser.get<int>("neighbor_size");
    timestamp = std::to_string(std::time(nullptr));
}

void Parameters::print() const {
    std::cout << "[PARAMS] instance_index: " << instance_index
              << " random_num: " << random_num
              << " seed: " << seed
              << " population_size: " << population_size
              << " iteration: " << iteration
              << " patience: " << patience
              << " max_time: " << max_time
              << " fit_beta: " << fit_beta
              << " dist_th: " << dist_th
              << " neighbor_size: " << neighbor_size
              << " timestamp: " << timestamp
              << std::endl;
}