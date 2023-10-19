/**
 * Data.hpp
 * created on : Nov 30 2022
 * author : Z.LEI
 **/

#ifndef CETSP_DATA_HPP
#define CETSP_DATA_HPP

#include "Defs.hpp"
#include "Utils/Parameters.hpp"
#include "Genetic/List.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <filesystem>

class Data {
private:
    Centers centers;                            // targets (x, y, r), centers[0] is depot
    std::string data_dir;                       // dir to read instance data
    std::string res_dir;                        // dir to write results
    std::string filename;                       // instance filename
    int instance_index;                         // instance index
    std::string timestamp;                      // timestamp
    std::string result_filename;                // result filename
    void reduceSize();                          // reduce the size of centers
public:
    Data(Parameters *params);
    ~Data() = default;
    void read();                                                        // read data
    void write(List* solution, int iter, std::string running_time);     // write the best solution when updating
    Centers getData();                                                  // get centers
    std::string getResultFilename();                                    // get result filename
};

#endif //CETSP_DATA_HPP
