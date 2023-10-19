/**
 * LKH.hpp
 * created on : Jan 03 2023
 * author : Z.LEI
 **/

#ifndef CETSP_LKH_HPP
#define CETSP_LKH_HPP

#include "Defs.hpp"
#include "Genetic/Node.hpp"
#include "Genetic/List.hpp"
#include "ListAdapter.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>

class LKH {
private:
    std::string lkh_exe;
    std::string root_dir;
    std::string params_file;
    std::string problem_file;
    std::string tour_file;
    std::string result_file;
    std::vector<std::vector<double>> positions;
    void write(List* solution);         // write config of LKH and TSP problem
    List* read();                       // read the solution
public:
    LKH();
    ~LKH();
    void setContext(std::string timestamp, int random_value);
    List* run(List* solution, bool adapted);
};
#endif //CETSP_LKH_HPP