/**
 * Algo.cpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#include "Algo.hpp"

Algo::Algo(Parameters *params): population(params), data(params) {
    this->params = params;
    this->random = new Random(params->seed);
    this->iteration = params->iteration;
    this->patience_threshold = params->patience;
    this->instance_index = params->instance_index;
    this->timestamp = params->timestamp;
}

Algo::~Algo(){
    delete random;
}

void Algo::run() {
    // read data;
    Centers centers = data.getData();
    // set context
    population.setContext(centers, random, timestamp);

    auto start_run = std::chrono::high_resolution_clock::now();

    int iter = 0;
    int best_iter = 0;
    int patience = 0;
    bool improved = false;
    std::chrono::duration<double> best_running_time;
    // init population
    List *best_solution = population.initPopulation();
    double best_solution_value = best_solution->getValue();

    // iteration
    while (iter++ < iteration) {
        std::cout << std::endl << "Iteration " << iter << " : " << std::endl;

        auto start_iter = std::chrono::high_resolution_clock::now();
        // next population
        best_solution = population.nextPopulation(patience);
        improved = best_solution->getValue() - best_solution_value < -DELTA ? true : false;
        best_solution_value = best_solution->getValue();

        auto end_iter = std::chrono::high_resolution_clock::now();

        if (improved) {
            best_iter = iter;
            patience = 0;
            best_running_time = end_iter - start_run;
            if (LOG) data.write(best_solution, iter, std::to_string(best_running_time.count()));
        } else {
            ++patience;
        }

        std::cout << "[LOG] iter: " << iter
                  << " best_iter: " << best_iter
                  << " best_value: " << best_solution->getValue()
                  << " iter_time: " << std::chrono::duration<double> (end_iter - start_iter).count()
                  << " total_time: " << std::chrono::duration<double> (end_iter - start_run).count()
                  << std::endl;

        if (patience >= patience_threshold) {
            std::cout << std::endl << "[STOP] best solution hasn't been improved since " << patience_threshold << " iterations" << std::endl;
            break;
        }

        if (std::chrono::duration<double> (end_iter - start_run).count() > params->max_time) {
            std::cout << std::endl << "[STOP] running time exceeds " << params->max_time << " seconds" << std::endl;
            break;
        }
    }

    auto end_run = std::chrono::high_resolution_clock::now();

    if (!LOG)  data.write(best_solution, best_iter, std::to_string(best_running_time.count()));

    std::cout << std::endl
            << "[SUMMARY] instance: " << FILENAMES[instance_index]
            << " best_value: " << best_solution->getValue()
            << " best_time: " << std::to_string(best_running_time.count())
            << " total_time: " << std::chrono::duration<double> (end_run - start_run).count()
            << " result_file: " << data.getResultFilename()
            << std::endl;
}
