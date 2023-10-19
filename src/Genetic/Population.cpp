/**
 * Population.cpp
 * created on : March 03 2022
 * author : Z.LEI
 **/

#include "Genetic/Population.hpp"

Population::Population(Parameters *params): neighbor(params->neighbor_size), ls(params) {
    this->initialization = params->init;
    this->selection = params->select;
    this->crossover_type = params->crossover;
    this->population_size = params->population_size;
    this->fit_beta = params->fit_beta;
    this->dist_th = params->dist_th;
    this->best_solution = nullptr;
    this->crossover = nullptr;
}

Population::~Population() {
    for (int i = 0; i < population.size(); ++i) {
        delete population[i];
    }
    delete best_solution;
    delete crossover;
}

void Population::setContext(Centers &centers, Random *random, std::string timestamp) {
    this->random = random;
    this->centers = centers;
    neighbor.setContext(centers.size());
    ls.setContext(random, centers, &neighbor, timestamp);
    kmeans.setContext(random, centers);
    crossover = CrossoverFactory::createCrossover(crossover_type);
    crossover->setContext(random);
}

List* Population::randomSolution() {
    std::vector<int> ids(centers.size() - 1);
    std::iota(ids.begin(), ids.end(), 1);
    random->permutation(ids);
    List *solution = new List();
    Node* head = new Node(0, centers[0][0], centers[0][1]);
    solution->add(head);
    for (int i = 0; i < ids.size(); ++i) {
        int id = ids[i];
        double theta = random->randomDoubleDistr(0, 2 * PI);
        double r = random->randomDoubleDistr(0, 1);
        double x = centers[id][0] + r * centers[id][2] * cos(theta);
        double y = centers[id][1] + r * centers[id][2] * sin(theta);
        if (pow(x - centers[id][0], 2) + pow(y - centers[id][1], 2) > pow(centers[id][2], 2)){
            std::cout << "ERROR : init point out of circle" << std::endl;
        }
        Node* node = new Node(id, x, y);
        solution->add(node);
    }
    return solution;
}

List* Population::kmeansSolution() {
    std::vector<std::vector<int>> groups = kmeans.getGroups();
    // random.permutation(groups);
    List *solution = new List();
    for (int i = 0; i < groups.size(); ++i) {
        random->permutation(groups[i]);
        for (int j = 0; j < groups[i].size(); ++j) {
            int id = groups[i][j];
            double x = centers[id][0], y = centers[id][1];
            if (id != 0) {
                double theta = random->randomDoubleDistr(0, 2 * PI);
                double r = random->randomDoubleDistr(0, 1);
                x = centers[id][0] + r * centers[id][2] * cos(theta);
                y = centers[id][1] + r * centers[id][2] * sin(theta);
                if (pow(x - centers[id][0], 2) + pow(y - centers[id][1], 2) > pow(centers[id][2], 2)){
                    std::cout << "ERROR : init point out of circle" << std::endl;
                }
            }
            Node* node = new Node(id, x, y);
            solution->add(node);
        }
    }
    Node* p = solution->head();
    while (p->id != 0) {
        p = p->next;
    }
    solution->setHead(p);
    return solution;
}

List *Population::initSolution() {
    List* solution = nullptr;
    if (initialization == "RANDOM") {
        solution = randomSolution();
    } else if (initialization == "KMEANS") {
        solution = kmeansSolution();
    } else {
        std::cerr << "[ERROR] invalid initialization method" << std::endl;
    }
    solution = ls.initSolOpt(solution);
    return solution;
}

List *Population::initPopulation() {
    auto start = std::chrono::high_resolution_clock::now();

    if (initialization == "KMEANS") {
        auto start_kmeans = std::chrono::high_resolution_clock::now();
        kmeans.run();
        auto end_kmeans = std::chrono::high_resolution_clock::now();
        std::cout << "kmeans time : "<< std::chrono::duration <double> (end_kmeans - start_kmeans).count() << " s"  << std::endl;
    }

    List* best = nullptr;
    for (int i = 0; i < population_size; ++i) {
        List* solution = initSolution();
        insertSolution(solution);
        if (!best || solution->getValue() < best->getValue()) {
            best = solution;
        }
    }

    best_solution = new List(*best);

    std::sort(population.begin(), population.end(), [] (List* s1, List* s2) {
        return s1->getValue() < s2->getValue();
    });

    auto end = std::chrono::high_resolution_clock::now();
    if (LOG) {
        std::cout << initialization << " init time : "<< std::chrono::duration <double> (end - start).count() << " s"  << std::endl;
    }
    neighbor.updateNeighbors();
    return best_solution;
}

std::pair<List*, List*> Population::chooseParent() {
    int size = population.size();
    int i = -1, j = -1;
    if (selection == "RANDOM") {
        while (i == j) {
            i = random->randomInt(size);
            j = random->randomInt(size);
        }
    } else if (selection == "ROULETTE") {
        int sum_portion = (1 + size) * size / 2;
        int lucky;
        while (i == j) {
            lucky = random->randomInt(sum_portion) + 1;
            i = size - int(sqrt(2 * lucky));
            lucky = random->randomInt(sum_portion) + 1;
            j = size - int(sqrt(2 * lucky));
        }
        if (i > j) {
            i = i ^ j;
            j = i ^ j;
            i = i ^ j;
        }
    }
    if (LOG) {
        std::cout << "parents indices : " << i << " " << j << std::endl;
    }
    return {population[i], population[j]};
}

List *Population::nextPopulation(int patience) {
    std::pair<List*, List*> parents;
    double dist1 = 0, dist2 = 0;
    List* offspring = nullptr;
    int try_times = 5;
    while (dist1 == 0 || dist2 == 0) {
        if (try_times-- <= 0) {
            randomSwap(offspring);
        } else {
            parents = chooseParent();
            offspring = crossover->run(parents.first, parents.second);
        }
        dist1 = Distance::run(offspring, parents.first);
        dist2 = Distance::run(offspring, parents.second);
        if (LOG) {
            std::cout << "dists between offspring and parents :" << dist1 << " " << dist2 << std::endl;
        }
    }

    // mutation
    if (random->randomInt(1000) < patience) {
        randomSwap(offspring);
    }

    offspring = ls.VND(offspring);
    insertSolution(offspring);

    populationManagement();

    if (LOG) {
        std::cout << "standard population size : " << population_size << ", current population size : " << population.size() << std::endl;
        std::cout << "population distances : " << std::endl;
        for (auto &p : population) {
            std::cout << p->getDistance() << " ";
        }
        std::cout << std::endl;
        std::cout << "population costs : " << std::endl;
        for (auto &p : population) {
            std::cout << p->getValue() << " ";
        }
        std::cout << std::endl;
    }

    return best_solution;
}

bool Population::insertSolution(List *s) {
    double distance_threshold = dist_th;
    double min_dist = INT_MAX;
    std::vector<double> distances(population.size(), 0);
    for (int i = 0; i < population.size(); ++i) {
        double dist = Distance::run(s, population[i]);
        min_dist = std::min(min_dist, dist);
        distances[i] = std::min(population[i]->getDistance(), dist);
    }
    s->setDistance(min_dist);
    if ((min_dist > 0 && best_solution && s->getValue() < best_solution->getValue()) || min_dist > distance_threshold) {
        for (int i = 0; i < population.size(); ++i) {
            population[i]->setDistance(distances[i]);
        }
        population.emplace_back(s);
        neighbor.updateCentroids(s);
        return true;
    } else {
        return false;
    }
}

void Population::updateDistances() {
    std::vector<double> distances(population.size(), INT_MAX);
    for (int i = 0; i < population.size(); ++i) {
        for (int j = i + 1; j < population.size(); ++j) {
            double dist = Distance::run(population[i], population[j]);
            distances[i] = std::min(distances[i], dist);
            distances[j] = std::min(distances[j], dist);
        }
    }
    for (int i = 0; i < population.size(); ++i) {
        population[i]->setDistance(distances[i]);
    }
}

void Population::populationManagement() {
    std::unordered_map<List*, std::vector<double>> rank;

    // value rank
    std::sort(population.begin(), population.end(), [] (List* s1, List* s2) {
        return s1->getValue() < s2->getValue();
    });

    for (int i = 0; i < population.size(); ++i) {
        rank[population[i]].emplace_back(100.0 * i / (population.size() - 1));
    }

    // distance rank
    std::sort(population.begin(), population.end(), [] (List* s1, List* s2) {
        return s1->getDistance() > s2->getDistance();
    });

    for (int i = 0; i < population.size(); ++i) {
        rank[population[i]].emplace_back(100.0 * i / (population.size() - 1));
    }

    for (int i = 0; i < population.size(); ++i) {
        double alpha = 1, beta = fit_beta;
        double fitness = alpha * rank[population[i]][0] + beta * rank[population[i]][1];
        population[i]->setFitness(fitness);
    }

    std::sort(population.begin(), population.end(), [] (List* s1, List* s2) {
        return s1->getFitness() < s2->getFitness();
    });

    if (population.size() >= 1.5 * population_size) {
        population.resize(population_size);
        neighbor.updateNeighbors();
        updateDistances();
    }

    List* best = *std::min_element(population.begin(), population.end(), [] (List* s1, List* s2) {
        return s1->getValue() < s2->getValue();
    });

    if (best->getValue() < best_solution->getValue()) {
        delete best_solution;
        best_solution = new List(*best);
    }

}

void Population::randomSwap(List* s) {
    int steps = 5;
    while (steps-- > 0) {
        int i = random->randomInt(s->size()-1) + 1;
        int j = random->randomInt(s->size()-1) + 1;
        while (i == j && abs(i - j) == 1) {
            i = random->randomInt(s->size()-1) + 1;
            j = random->randomInt(s->size()-1) + 1;
        }
        Node* p1 = s->head();
        Node* p2 = s->head();
        while(i-- > 0) p1 = p1->next;
        while (j-- > 0) p2 = p2->next;
        Node::swap(p1, p2);
    }
}

