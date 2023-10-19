/**
 * Defs.hpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#ifndef CETSP_DEFS_HPP
#define CETSP_DEFS_HPP

#include <vector>
#include <string>

typedef std::vector<std::vector<double>> Centers;
typedef std::vector<std::vector<int>> Neighbors;

const int INSTANCE_INDEX = 1;           // which instance file
const int ITERATION = 5000;             // max iteration
const double MAX_TIME = 36000;          // max running time
const int POPULATION_SIZE = 20;         // population size
const int DISTANCE_THRESHOLD = 5;       // min distance in population
const double FIT_BETA = 0.96;           // fitness function distance coef
const int NEIGHBOR_SIZE = 50;           // neighbors size of a target
const double EPSILON = 1e-4;            // approximation in geometry and local search
const double DELTA = 1e-3;              // approximation in accepting best solution
const double PI = 3.14159265358979323846;

const std::string INITIALIZATION = "KMEANS";    // RANDOM, KMEANS
const std::string SELECTION = "RANDOM";         // RANDOM, ROULETTE
const std::string CROSSOVER = "KSX";            // KSX, GAX, EAX
const std::string IMPROVEMENT = "BEST";         // FIRST, BEST
const std::string GREEDY_ALGO = "SQUEEZE";      // SQUEEZE, SPARSE
const std::string DISTANCE = "EDIT";

const std::string ENV = "LOCAL";                 // LOCAL, SERVER
const bool LOG = false;                          // log more details
const int SEED = 0;                              // random seed

// server
const std::string SERVER_DATA_DIR = "";
const std::string SERVER_RES_DIR = "";
const std::string SERVER_LKH_EXE = "";
const std::string SERVER_LKH_TMP_ROOT = "";

// local
const std::string LOCAL_DATA_DIR = "";              // directory of instances
const std::string LOCAL_RES_DIR = "";               // directory of results
const std::string LOCAL_LKH_EXE = "";               // path for LKH solver
const std::string LOCAL_LKH_TMP_ROOT = "";          // LKH tmp output directory

// instances
const std::vector<std::string> FILENAMES = {
    // varied overlap ratios instances
    "bonus1000",              // 0
    "bubbles1",               // 1
    "bubbles2",               // 2
    "bubbles3",               // 3
    "bubbles4",               // 4
    "bubbles5",               // 5
    "bubbles6",               // 6
    "bubbles7",               // 7
    "bubbles8",               // 8
    "bubbles9",               // 9
    "chaoSingleDep",          // 10
    "concentricCircles1",     // 11
    "concentricCircles2",     // 12
    "concentricCircles3",     // 13
    "concentricCircles4",     // 14
    "concentricCircles5",     // 15
    "rotatingDiamonds1",      // 16
    "rotatingDiamonds2",      // 17
    "rotatingDiamonds3",      // 18
    "rotatingDiamonds4",      // 19
    "rotatingDiamonds5",      // 20
    "team1_100",              // 21
    "team2_200",              // 22
    "team3_300",              // 23
    "team4_400",              // 24
    "team5_499",              // 25
    "team6_500",              // 26
    // instances with different overlap ratio 0.02
    "d493_or2",                   // 27
    "dsj1000_or2",                // 28
    "kroD100_or2",                // 29
    "lin318_or2",                 // 30
    "pcb442_or2",                 // 31
    "rat195_or2",                 // 32
    "rd400_or2",                  // 33
    // instances with different overlap ratio 0.1
    "d493_or10",                   // 34
    "dsj1000_or10",                // 35
    "kroD100_or10",                // 36
    "lin318_or10",                 // 37
    "pcb442_or10",                 // 38
    "rat195_or10",                 // 39
    "rd400_or10",                  // 40
    // instances with different overlap ratio 0.3
    "d493_or30",                   // 41
    "dsj1000_or30",                // 42
    "kroD100_or30",                // 43
    "lin318_or30",                 // 44
    "pcb442_or30",                 // 45
    "rat195_or30",                 // 46
    "rd400_or30",                  // 47
    // arbitrary radii instances
    "bonus1000rdmRad",        // 48
    "d493rdmRad",             // 49
    "dsj1000rdmRad",          // 50
    "kroD100rdmRad",          // 51
    "lin318rdmRad",           // 52
    "pcb442rdmRad",           // 53
    "rat195rdmRad",           // 54
    "rd400rdmRad",            // 55
    "team1_100rdmRad",        // 56
    "team2_200rdmRad",        // 57
    "team3_300rdmRad",        // 58
    "team4_400rdmRad",        // 59
    "team5_499rdmRad",        // 60
    "team6_500rdmRad",        // 61
    // real world instances
    "car_door_25",               // 62
    "car_door_30",               // 63
    "car_door_35",               // 64
    "car_door_40",               // 65
    "car_door_45",               // 66
    "car_door_50",               // 67
};

#endif //CETSP_DEFS_HPP
